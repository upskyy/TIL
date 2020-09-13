#include "server.h"


typedef int boolean;

typedef struct User{
	char user_id[USER_ID_LENGTH];
	char filename[FILENAME_LENGTH];
	int  service;
}User;
typedef struct Login{
	char user_id[USER_ID_LENGTH];
	char user_password[USER_PASSWORD_LENGTH];
}Login;

void child_handler(int signo);
void cloud_service(int sockfd);
void Upload(int sockfd, User *user);
void Download(int sockfd, User *user);
char *server_path(char *id,char *filename);
void buffer_clean();
void array_clean(char *buf, int size);
void make_directory(char user_id[]);
void server_ui(int sockfd);
boolean server_login(int sockfd);
boolean server_sign_up(int sockfd);

int main(int argc, char **argv){
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr, peerSocket;

	/*  소켓 생성  */
	listenfd= socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	/*   Bind   */
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	/*  Listen  */
	listen(listenfd, LISTEN_QUEUE_SIZE);
	puts("Waiting the clients... ");
	signal(SIGCHLD, child_handler); //좀비 프로세스 제거

	while(TRUE){
		clilen = sizeof(cliaddr);
		/*  Accept  */
		if((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
			if(errno == EINTR)
				continue;
			else
				puts("accept error");
		}

		getpeername(connfd, (struct sockaddr*)&peerSocket, &clilen);
		char peerName[sizeof(peerSocket.sin_addr) + 1] = { 0 };
                strcpy(peerName,inet_ntoa(peerSocket.sin_addr));
		/* 접속이 안되었을 때는 출력 x  */
 		if(strcmp(peerName,"0.0.0.0") != 0){
                printf("Client IP : %s\n", peerName);
        	}

		/*  클라이언트가 접속 할 때마다 fork() 함수를 통해 자식 프로세스 생성  */
		if((childpid = fork()) ==0){  /* 자식 프로세스 */
			close(listenfd);
			printf("process %d : allocated !!!!!!\n\n",(int)getpid());
			cloud_service(connfd);
			close(connfd);
			exit(SUCCESS);
		}
		close(connfd);  /* 부모 프로세스 */
	}
}


void cloud_service(int sockfd){
	User user;
	boolean first = TRUE;

	server_ui(sockfd);  /* 회원가입과 로그인 진행하는 UI */

	while(TRUE){
		read(sockfd, &user, sizeof(User)); 
		/*  처음에만 유저 ID를 파일 이름으로 하여 디렉토리 생성   */
		if(first){
			make_directory(user.user_id);
			first = FALSE;
		}
		/*  Upload  */
		if(user.service == UPLOAD){	
			Upload(sockfd, &user);	
		}
		/*  Download  */
		else if(user.service == DOWNLOAD){
			Download(sockfd, &user);
		}
		/*  Exit  */
		else if(user.service == PROGRAM_EXIT ){
		return;
		}
	}
}


/*  Upload 하는 함수  */

void Upload(int sockfd, User *user){
char buffer[BUFFER_SIZE];
int pid = (int)getpid();
size_t n;
char *fd;
FILE *upload;

array_clean(buffer,BUFFER_SIZE);
printf("%s : Uploading the file ... \n\n",user->user_id);


read(sockfd,user,sizeof(User));
fd = server_path(user->user_id,user->filename);
upload = fopen(fd,"wb+");

if(upload == NULL){
printf("%s : file open error !\n\n",user->user_id);
return;
}
again :
while((n = read(sockfd,buffer,BUFFER_SIZE)) > 0){
if(!strcmp(buffer,END_SIGNAL)){
printf("ID : %s \n",user->user_id);
printf("File name : %s\n",user->filename);
printf("Uploading is completed !\n\n");
fflush(stdout);  // 버퍼 비우기
break;
}
fwrite(buffer,1, BUFFER_SIZE, upload);
array_clean(buffer, BUFFER_SIZE);
}

if((n < 0) && (errno == EINTR)){
goto again;
}
else if(n < 0){
printf("%s : file receive error !\n\n",user->user_id);
}

free(fd);
fclose(upload);

return;
}

/* 서버측에서 파일 경로 설정 해주는 함수 */

char *server_path(char *id,char *filename){
	char *fd = (char *)malloc(sizeof(char) * BUFFER_SIZE);

	strcpy(fd,STORE_PATH);
	strcat(fd,id);
	strcat(fd,"/");
	strcat(fd,filename);

	return fd;
}

/*  버퍼 비우는 함수  */
void buffer_clean(){
while(getchar() != '\n');
return;
}

void array_clean(char *buf, int size){
for(int i=0; i<size; i++){
	buf[i] = NULL;
}
}

/*  Download 하는 함수  */
void Download(int sockfd, User *user){
char buffer[BUFFER_SIZE];
FILE *fd;

printf("%s : Downloading the file ... \n\n",user->user_id);
read(sockfd,user,sizeof(User)); /* receive user filename */

fd= fopen(user->filename,"rb");

if(fd == NULL){
printf("%s : ERROR !\n",user->user_id);
return;
}
/*  파일 전송하는 과정  */
while(fread(buffer,1, BUFFER_SIZE, fd) > 0){
write(sockfd,buffer,BUFFER_SIZE);
array_clean(buffer,BUFFER_SIZE);
}

printf("ID : %s \n",user->user_id);
printf("File name : %s\n",user->filename);
printf("Downloading is completed !\n\n");
fflush(stdout);

write(sockfd,END_SIGNAL,sizeof(END_SIGNAL));

fclose(fd);
return;
}


/*  디렉토리 만들어 주는 함수  */
void make_directory(char user_id[]){
char path[PATH_LENGTH] = STORE_PATH;
strcat(path, user_id);
if(mkdir(path,MKDIR_MODE) == ERROR && errno == EEXIST){
printf("%s : Directory already existed !\n\n",user_id);
return;
}
printf("%s : Directory is created !\n\n",user_id);
return;
}



/* 회원가입과 로그인 하는 UI 함수 */

void server_ui(int sockfd){
	int num;
	int pid = (int)getpid();
	while(TRUE){
	read(sockfd, &num, sizeof(num));
	/* Login */
	if(num == LOGIN){
	if(server_login(sockfd)){
		printf("process %d : login success !\n\n",pid);
		return;	
		}else{
		printf("process %d : login fail !\n\n",pid);
		continue;
		}
	}
	/* Sign up */
	else if(num == SIGN_UP){
	if(server_sign_up(sockfd)){
	printf("process %d : sign up is successful !\n\n",pid);
	continue;
	}else{
		printf("process %d : sign up is failed !\n\n",pid);
		continue;
	}
	}
	/* Exit */
	else if(num == PROGRAM_EXIT){
	printf("process %d : exit....\n\n",pid);
	exit(SUCCESS);
	}
	else{
	printf("process %d : error !\n\n",pid);
	exit(FAIL);
	}
  }
}

/* 서버측 로그인 하는 함수 */
boolean server_login(int sockfd){
Login login;
FILE* fp;
char buffer[LOGIN_SIZE];
char *id;
char *pw;
char flag[FLAG_SIZE];
receive_login(sockfd, &login);

fp = fopen(MEMBER_INFORMATION,"r");  //텍스트 파일을 읽어서 ID, PW  맞는지 확인
if(fp == NULL){
puts("It cannot read login information !");
return ERROR;
}

while(TRUE){
fgets(buffer, LOGIN_SIZE, fp); // 텍스트 파일에서 한 줄 읽어오기
if(feof(fp)){ // 파일의 끝이라면 break로 반복문 탈출
break;
}
id = strtok(buffer,"/");
pw = strtok(NULL, "\n");
/* ID와 PW를 확인 후 맞으면 success 전송 */
if(!strcmp(id,login.user_id) && !strcmp(pw,login.user_password)){
write(sockfd,"success", FLAG_SIZE);
return TRUE;
}
}
/* 그렇지 않으면 fail 전송 */
write(sockfd,"fail",FLAG_SIZE);
return FALSE;
}



/* 회원가입 하는 함수 */
boolean server_sign_up(int sockfd){
Login login;
int fd;
receive_login(sockfd, &login);
fd = open(MEMBER_INFORMATION, O_WRONLY | O_CREAT | O_APPEND, SET_ACCESS);
if(fd == ERROR){
close(fd);
return ERROR;
}

write(fd,login.user_id,strlen(login.user_id));
write(fd, "/", 1);
write(fd,login.user_password,strlen(login.user_password));
write(fd, "\n", 1);
close(fd);
return TRUE;
}


/* 로그인 정보 보내고 받는 함수 */
/* 자주 사용해서 함수로 만들어 놓았다 */

void send_login(int sockfd, Login *login){
	return write(sockfd, login, sizeof(Login));
}
void receive_login(int sockfd, Login *login){
	return read(sockfd, login, sizeof(Login));
}


/*  종료된 자식프로세스 처리해주는 함수  */
void child_handler(int signo){
	pid_t pid;
	int stat;

	while((pid = waitpid(-1,&stat,WNOHANG)) > 0){
		printf("process %d : terminated !!!!!!\n", (int)pid);
     	return;
		}
}


