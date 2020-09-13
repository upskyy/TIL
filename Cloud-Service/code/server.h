#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>


#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAIL 0
#define ERROR -1
#define USER_ID_LENGTH 20
#define FILENAME_LENGTH 20
#define UPLOAD 1
#define DOWNLOAD 2
#define LOGIN 1
#define SIGN_UP 2
#define PROGRAM_EXIT 3
#define USER_ID_LENGTH 20
#define USER_PASSWORD_LENGTH 20
#define FLAG_SIZE 20
#define MEMBER_INFORMATION "login_information.txt"
#define BUFFER_SIZE 4096
#define SET_ACCESS 00700
# define LISTEN_QUEUE_SIZE 5
#define PORT 20165
#define LOGIN_SIZE 40
#define END_SIGNAL "end"

#define STORE_PATH "/home/hasangchun/cloud/UPLOAD/"
#define PATH_LENGTH 64
#define MKDIR_MODE 0766


