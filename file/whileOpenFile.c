#include<fcntl.h>
#include<stdio.h>

void main(){
	int open_time = 0;
	const char* file = "test.txt";
	while(1){
		int fd = open(file, O_RDONLY);
		if(fd > 0){
			printf("Times:%d %s\n", ++open_time, file);
		}
		else{
		   printf("Open Error\n");
		   break;
		}
			
	}

	return;
}
