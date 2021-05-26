

/*
 * A simple socket code sample.
 * The file is wriete for server adn clinet process. 
 * */


#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<linux/in.h>
#include<unistd.h>

#define DELAY_PERIOD 5 * 10e6
#define BUFFERLEN 1024
void process_conn_client(int s){
	printf("Clinet: connection\n");
	ssize_t size = 0;
	char buffer[BUFFERLEN];
	while(1){
		printf("Input messsage to server:"); // 缓冲区溢出？
		fgets(buffer, BUFFERLEN, stdin);
		if(buffer[0] == 'x'){
			printf("Client wants to break connects.\n");
			break;
		}
		write(s, buffer, strlen(buffer) + 1); // 发送数据
		while((size = read(s, buffer, BUFFERLEN)) == 0); // 接受响应
		printf("Received mgs:%s\n", buffer);
	}	   
	
	usleep(DELAY_PERIOD);
	printf("Client: Finished!\n");
}



void process_conn_server(int s){
	printf("Server: connection\n");
	ssize_t size = 0;
	char read_buf[BUFFERLEN], write_buf[BUFFERLEN];
	while(1){
		size = read(s, read_buf, BUFFERLEN);
		if(size <= 0){ // 阻塞IO下，size小于等于0则意味着出错
			usleep(DELAY_PERIOD);
			continue;
		}
		printf("Msg from client: %s\n", read_buf);
		sprintf(write_buf, "%ld bytes  altogether; Messsage: %s", size, read_buf);
		write(s, write_buf, strlen(write_buf) + 1); 
	}	   
	printf("Server: Finished!\n");
}

