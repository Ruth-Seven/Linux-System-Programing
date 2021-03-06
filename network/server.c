
/*
 * A simple socket code sample.
 * The file is wriete for a server.
 * */


#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<linux/in.h>
#include<stdlib.h>
#include<signal.h>
#define BACKLOG 20
#define PORT 8888

void process_conn_server(int); 

static int ss = 0;

int server(){
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	ss = socket(AF_INET, SOCK_STREAM, 0);
	if(ss < 0){
		printf("socket error\n");
		return -1;
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 本地地址？
	server_addr.sin_port = htons(PORT);
	
	int err = bind(ss, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(err < 0){
		printf("bind error\n");
		return -1;
	}
	
	err = listen(ss, BACKLOG);
	if(err < 0){
		printf("listen error\n");
		return -1;
	}

	// solve connections
	while(1){
		int addrlen = sizeof(struct sockaddr);
		int sc = accept(ss, (struct sockaddr*)&client_addr,  &addrlen); // ?&addrlen
		if(sc < 0){
			usleep(1);
			continue;
		}
		// 开启一个进程进行响应i
		int pid = fork();
		if(pid == 0){
			close(ss);// 子进程关闭对服务器侦听
			process_conn_server(sc);
		}else{
			close(sc);
		}
	
	}

	
	return 0;
}

void handler_sig_int_server(int signal){
	if(signal == 2){
		printf("Abnormal Exit! Sigle: %d\n Close the listen file handler\n", signal);
		close(ss);	
	}
	exit(1);
}

int main(int argc, char** args){
	signal(SIGINT, handler_sig_int_server);
	return server();
}
