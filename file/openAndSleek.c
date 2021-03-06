
/*
 * Test for lseek function and empty file.
 * */

#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
static inline 
int max(int a, int b){
	return a > b ? a : b;
}

int main(int argv, char** args){
	const char* file = args[1];
	const char* input = args[2];

	int size = strlen(input);
	int fd = open(file, O_WRONLY);
	if(fd < 0){
		printf("Open Error\n");
		return 1;
	}
	
	int off = lseek(fd, 256, SEEK_SET);
	printf("lseek off: %d\n", off);
	int res_size = write(fd, input, size);
	printf("res_size:%d\n", res_size);
	close(fd);
	return 0;
}
