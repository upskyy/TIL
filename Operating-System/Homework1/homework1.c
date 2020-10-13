#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#define ERROR -1
#define FINISH 0
void main() {
	pid_t pid;
	pid = fork();
	if (!pid) {	/*  child process  */
		printf("child process : %d\n", getpid());
		exit(FINISH);
	}
	else if (pid < 0) {	/*  error  */
		printf("Fork failed\n");
		return ERROR;
	}
	else {	/*  parent process  */
		printf("parent process : %d\n", getpid());
		printf("parent process remains 30 seconds...\n");
		sleep(30);
	}
}