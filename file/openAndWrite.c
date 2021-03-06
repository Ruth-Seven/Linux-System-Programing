#include<fcntl.h>
#include<stdio.h>
#include<string.h>
static inline 
int max(int a, int b){
	return a > b ? a : b;
}

int main(int argv, char** args){
	const char* file = args[1];
	const char* input = args[2];

	int fd = open(file, O_WRONLY | O_APPEND);
	if(fd < 0){
		printf("Open Error\n");
		return 1;
	}
	const char buf[10];
	
	int size = strlen(input);
	int block_size = 10;
    int pos = 0;	
	while(pos < size){
		int write_size = block_size - max(0, pos + block_size - size);
		memcpy(buf, input + pos, write_size);	
		pos += write_size ;
		int res_size = write(fd, buf, write_size);
		if(res_size <= 0){
			printf("Write over\n" );
			break;
		}
		printf("Write More: \t(|%s|)\n", buf);
	}
	
	close(fd);
	return 0;
}
