
/*
i * Test for lseek function and empty file.
 *  gcc openAndMmap.c && ./a.out test.txt "the mmap function is important" && cat test.txt && echo "\n" && od test.txt -c
 * */

#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<unistd.h>

#define FILELENGHT 1024
static inline 
int max(int a, int b){
	return a > b ? a : b;
}

int main(int argv, char** args){
	const char* file = args[1];
	const char* input = args[2];

	int size = strlen(input);
	printf("input size: %d\n", size);

	int fd = open(file, O_RDWR);
	if(fd < 0){
		printf("Open Error\n");
		return 1;
	}
		
	// resize the file
	int off = lseek(fd,  FILELENGHT , SEEK_SET);
	printf("lseek off: %d\n", off);	
	int res_size = write(fd, "88", 2);
	// or use ftruncate
	// ftruncate(fd, FILELENGHT);

	char* ptr =(char*) mmap(NULL, FILELENGHT, PROT_READ | PROT_WRITE, MAP_SHARED, \
					fd, 0 * sysconf(_SC_PAGE_SIZE)); // offset must be configure
	// BUS ERROR ocourrs because  the writed space overlaps maped space.
	if( MAP_FAILED == ptr){
		printf("Mmap failure!\n");
		close(fd);
		return -1;
	}
	strcpy(ptr + 500, input);
	munmap(ptr, FILELENGHT);
	close(fd);
	return 0;
}
