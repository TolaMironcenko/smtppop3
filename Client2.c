#include <openssl/ssl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "erfunk.h"

#include <pthread.h>

#define DEFLAUT_IP "217.69.139.74"
#define BUF_SIZE 4096

int SSL_library_int();
//const SSL_METHOD *SSLv23_client_method();
//int SSL_set_fd(SSL *ssl, int fd);
//SSL *SSL_new(SSL_CTX *ctx);

struct sockaddr_in serv_addr, client_addr;

_Bool isExit = 0;
_Bool GetMes = 0;

_Bool break_connect(char* buf)
{
	for(int i=0; i<strlen(buf); i++){
		if((buf[0] == 'Q') & (buf[1] == 'U') 
		   & (buf[2] == 'I') & (buf[3] == 'T')){isExit = 1;return 1;}
	}
	return 0;	
}

_Bool get_mess(char* buf)
{
	for(int i=0; i<strlen(buf); i++){
		if((buf[0] == 'T') & (buf[1] == 'O') 
		   & (buf[2] == 'P')){GetMes = 1;return 1;}
	}
	return 0;	
}


int send_message(void *argv)
{
	while (1)
	{
		char buf[BUF_SIZE];
		SSL *ssl = (SSL*) argv;	
		fgets(buf,sizeof(buf), stdin);
		get_mess(buf);	
		SSL_write(ssl,buf, strlen(buf));
		if(break_connect(buf)){break;}
		//get_mess(buf);	
	}
	return 0;
}


int main(){

	system("clear");
	pthread_t thread;
	char mess[4096];
	//int k=0;
	bzero(mess, sizeof(mess));
	
	SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_client_method());
	
	int client = socket(AF_INET, SOCK_STREAM,0);
	SSL *ssl = SSL_new(ssl_ctx);
	
	serv_addr.sin_addr.s_addr = inet_addr(DEFLAUT_IP); // IP к кому подключаемся
	serv_addr.sin_family = AF_INET; // По какому протаколу подключаемся 
	serv_addr.sin_port = htons(995); // Порт для подключения 
	
	
	SSL_set_fd(ssl, client);
	
	printf("Clien socket created. \n");
	
	printf("Wait for the connect...\n");
	socklen_t size = sizeof(serv_addr);
	Connect(client, (struct sockaddr *)&serv_addr, size);
	SSL_connect(ssl);
	printf("Connect SSL: sucsses. \n");
	
	char buf[BUF_SIZE];
	memset(buf, '\0', sizeof(buf));
	SSL_read(ssl,buf, sizeof(buf));
	
	strcpy(buf, "USER tolya.mironchenko@bk.ru\n");  // имя почты введи сюда 
	SSL_write(ssl,buf, strlen(buf));
	
	memset(buf, '\0', sizeof(buf));
	SSL_read(ssl,buf, sizeof(buf));
	
	strcpy(buf, "PASS w1mzAJELTgxiSE0Nm7rw\n"); // введи пароль сюда
	SSL_write(ssl,buf, strlen(buf));
	
	memset(buf, '\0', sizeof(buf));
	SSL_read(ssl,buf, sizeof(buf));
	printf("%s", buf);
	
	pthread_create(&thread, NULL, (void*)send_message, (void*)ssl);
	
	
	while(1)
	{
		bzero(buf, sizeof(buf));
		SSL_read(ssl,buf, sizeof(buf));
		printf("%s\n",buf);
		if(isExit){break;}
	}
	
	printf("\nGoodBye...\n");
	close(client);
	
	return 0;
}	

