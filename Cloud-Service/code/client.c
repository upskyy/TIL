#include "client.h"

typedef int boolean;
typedef struct User{
	char user_id[USER_ID_LENGTH];
	char filename[FILENAME_LENGTH];
	int service;
}User;
typedef struct Login{
	char user_id[USER_ID_LENGTH];
	char user_password[USER_PASSWORD_LENGTH];
}Login;

void cloud_service(int sockfd);
void set_filename(int sockfd, User *user);
void Upload(int sockfd, User *user);
char *client_path(char *id,char *filename);
void Download(int sockfd, User *user);
void array_clean(char *buf,int size);
void buffer_clean();
void make_directory(char user_id[]);
void client_ui(int sockfd, User *user);
void send_login(int sockfd, Login* login);
void receive_login(int sockfd, Login* login);
boolean client_login(int sockfd,User *user);
void client_sign_up(int sockfd);


int main(int argc, char **argv){
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2){
		puts("ERROR !");
		return ERROR;
	}

	/*  소켓 생성  */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	inet_aton(argv[1], (struct in_addr*) &servaddr.sin_addr.s_addr);
	/*  Connect  */
	 if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) == ERROR) 
   	{
        printf("Can not connect !\n");
        return ERROR;
   	}

	puts("connect completed !\n");
	cloud_service(sockfd);
	close(sockfd);
	puts("program exit....");
	
	return SUCCESS;
}




void cloud_service(int sockfd){

	User user;
	client_ui(sockfd, &user); // 회원가입과 로그인 하는 함수
	boolean first = TRUE;
	
	while(TRUE){
	system("clear");

	while(TRUE){
	puts("***** Please select an option *****");
	puts("1. Upload");
	puts("2. Download");
	puts("3. Exit");
	printf("INPUT : ");
	scanf("%d",&user.service);
	if(user.service < MENU_SELECT_MIN || user.service > MENU_SELECT_MAX){
	puts("please input your number again !\n");
	continue;
	}
	else{
	break;}
	}

	write(sockfd, &user,sizeof(User)); // 선택한 서비스를 알려주기 위해 서버에 전송

	/*  처음에만 유저 ID를 파일 이름으로 하여 디렉토리 생성 */
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
	/* Exit */
	else if(user.service == PROGRAM_EXIT){
		return;
	}
}

}
/* 파일 이름 입력 받는 함수 */
void set_filename(int sockfd, User *user){
int n;
do{
printf("Input filename : ");
n = scanf("%s",user->filename);

}while((n == -1) || (n >= FILENAME_LENGTH));
return;
}


/*  Upload 하는 함수  */
void Upload(int sockfd, User *user){
FILE *fd;
char buffer[BUFFER_SIZE];

set_filename(sockfd,user);

write(sockfd,user,sizeof(User));  //filename send

fd= fopen(user->filename,"rb");
if(fd == NULL){
puts("ERROR !");
return;
}

puts("Uploading the file ... ");
/* 파일 업로드 하는 과정 */
while(fread(buffer,1, BUFFER_SIZE,fd) > 0){
write(sockfd,buffer,BUFFER_SIZE);
array_clean(buffer,BUFFER_SIZE);
}

puts("Uploading is completed ! ");

write(sockfd, END_SIGNAL, sizeof(END_SIGNAL));

buffer_clean();
fclose(fd);
return;
}



/* 버퍼 비워주는 함수 */
void buffer_clean(){
while(getchar() != '\n');
return;
}

void array_clean(char *buf,int size){
for(int i = 0; i< size;i++){
buf[i] = NULL;
}
}

/* 클라이언트 측에서 파일 경로 설정해주는 함수 */
char *client_path(char *id,char *filename){
	char *fd = (char *)malloc(sizeof(char) * BUFFER_SIZE);

	strcpy(fd,STORE_PATH);
	strcat(fd,id);
	strcat(fd,"/");
	strcat(fd,filename);

	return fd;
}

/* Download 하는 함수 */
void Download(int sockfd, User *user){
char buffer[BUFFER_SIZE];
unsigned int n;
char *fd;
FILE *download;

set_filename(sockfd,user);

write(sockfd,user,sizeof(User));  /* filename send */
fd = client_path(user->user_id,user->filename);
download = fopen(fd,"wb+");

if(download == NULL){
printf("file open error !\n");
return;
}

again :
while((n = read(sockfd,buffer,BUFFER_SIZE)) > 0){
if(!strcmp(buffer,END_SIGNAL)){
printf("Downloading is completed !\n");
fflush(stdout);
break;
}
fwrite(buffer, 1, BUFFER_SIZE, download);
array_clean(buffer, BUFFER_SIZE);
}

if((n < 0) && (errno == EINTR)){
goto again;
}
else if(n < 0){
printf("file receive error !\n");
}


free(fd);
fclose(download);
return;
}


/* 디렉토리 만들어주는 함수 */
void make_directory(char user_id[]){
char path[PATH_LENGTH] = STORE_PATH;
strcat(path, user_id);
if(mkdir(path, MKDIR_MODE) == ERROR && errno == EEXIST){
return;
}
return;
}

/* 로그인과 회원가입을 진행하는 함수 */
void client_ui(int sockfd, User *user){
	int num;
	while(TRUE){
	/* 1,2,3 이외에 숫자를 입력하면 다시 입력하도록 하는 반복문 */
	while(TRUE){
	puts("***** Please select an option *****");
	puts("1. Login");
	puts("2. Sign up");
	puts("3. Exit");
	printf("INPUT : ");
	scanf("%d",&num);
	if(num < MENU_SELECT_MIN || num >MENU_SELECT_MAX){
	puts("please input your number again !\n");
	continue;
	}
	else{
	break;}
	}

	write(sockfd,&num, sizeof(num));  // 선택한 번호 서버에게 전송
	/* Login */
	if(num == LOGIN){
		if(client_login(sockfd,user)){
		puts("Login Success !\n");
		return;
		}else{
		puts("Login Fail !\n");
		continue;
		}
	}
	/* Sign up */
	else if(num == SIGN_UP){
	client_sign_up(sockfd);
	puts("Sign up is successful !\n");
	}
	/* Exit */
	else if(num == PROGRAM_EXIT){
	puts("program exit... ");
	exit(SUCCESS);
	}
	else {
	puts("error !");
	exit(FAIL);
	}
   }
}


/* 로그인 정보 보내고 받는 함수 */
/* 자주 사용해서 함수로 만들어 놓았다 */
void send_login(int sockfd, Login* login){
return write(sockfd, login, sizeof(Login));
}
void receive_login(int sockfd, Login* login){
return read(sockfd, login, sizeof(Login));
}


/* 클라이언트 로그인 하는 함수 */
boolean client_login(int sockfd, User *user){
	Login login;
	char flag[FLAG_SIZE];
	
	printf("ID : ");
	scanf("%s", login.user_id);
	printf("PASSWORD : ");
	scanf("%s", login.user_password);
	
	strcpy(user->user_id,login.user_id);  // 디렉토리 생성할 때 유저 ID가 필요해서 user 구조체에 복사해놓는다.

	send_login(sockfd, &login);
	read(sockfd, flag,sizeof(flag));

	if(!strcmp(flag,"success")){
	return TRUE;
	}else if(!strcmp(flag,"fail")){
	return FALSE;
	}else{
	printf("%s\n",flag);
	printf("Error !\n");
	return ERROR;
	}
}

/* 클라이언트 회원가입 하는 함수 */
void client_sign_up(int sockfd){
	Login login;
	printf("ID : ");
	scanf("%s", login.user_id);
	printf("PASSWORD : ");
	scanf("%s", login.user_password);

	send_login(sockfd, &login);

	return; 
}




