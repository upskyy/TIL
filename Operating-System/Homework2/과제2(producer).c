#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>

void main() {
	const int SIZE = 4096;  //Constant
	const char *name = "shared_memory";
	const char *message0 = "\nHello\n";
	const char *message1 = "My name is sangchun.\nThis is shared memory.\n";
	const char *message2 = "Good bye!\n\n";

	int shm_fd;
	void *ptr;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	sprintf(ptr, "%s", message0);
	ptr += strlen(message0);
	sprintf(ptr, "%s", message1);
	ptr += strlen(message1);
	sprintf(ptr, "%s", message2);
	ptr += strlen(message2);
	
}