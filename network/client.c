
/*
 * A simple socket code sample.
 * The file is wriete for a client
 * */


#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<linux/in.h>
#include<unistd.h>

#define PORT 8888

void process_conn_client(int s){
	printf("Clinet: connection\n");
	ssize_t size = 0;
	char buffer[1024];
	while(1){
		printf("Input messsage to server:", buffer); // 缓冲区溢出？
		scanf("%s", buffer);
		write(s, buffer, strlen(buffer) + 1); // 发送数据
		while((size = read(s, buffer, 1024)) == 0){ // 接受响应
			usleep(1);
		}
	}	   
}

int server(const char* ip){
	int sc;
	struct sockaddr_in server_addr;

	sc = sokcet(AF_INET, SOCK_STREAM, 0);
	if(sc < 0){
		printf("socket error\n");
		return -1;
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 本地地址？
	server_addr.sin_port = htons(PORT);

	// IP 转为整形
	inet_pton(AF_INET, ip,  &server_addr.sin_addr);

	connect(sc, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));

	process_conn_client(sc);
	
	close(sc);
	return 0;
}

int main(int argv, char **args){
	return server(args[1]);
}
