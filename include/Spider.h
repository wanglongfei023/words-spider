#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <regex.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/mman.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>

//http 类型为true    https 类型为false
#define TRUE 1
#define	FALSE 0
#define	WEBPORT 80
#define	HTTPS	443

#define START 0
#define MAX_URL 2238
#define LEN_URL 128

#define INTERVAL 1


typedef struct
{
	SSL * socket;
	SSL_CTX * ctx;
}ssl_t;

typedef struct 
{
	char url[2048];
	char domain[256];
	char name[1024];
	char ip[16];
	int types;
	int port;
	int status;
}url_t;


url_t * Spider_Analytic_url(char * url);
ssl_t * Spider_Openssl_Create(int);
int Spider_Connect_server(url_t * u);
int Spider_Request(url_t * ,int  ,ssl_t *);
int Spider_Response(int ,ssl_t *);
char * Spider_Create_cache(const char * filename);
int Spider_Analytic_html(char *);
int Spider_Download(int filefd,char* title,char* description);
