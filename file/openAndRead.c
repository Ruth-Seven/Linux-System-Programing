#include<fcntl.h>
#include<stdio.h>

int main(int argv, char** args){
	const char* file = args[1];

	int fd = open(file, O_RDONLY);
	if(fd < 0){
		printf("Open Error\n");
		return 1;
	}
	const char buf[10];
	
	int size = -1;
	int block_size = 10;
	while(size){		
		size = read(fd, buf, block_size);
		if(size <= 0){
			printf("Read over\n" );
			break;
		}
		printf("Read More: \t(|%s|)\n", buf);
	}
	

	return 0;
}
