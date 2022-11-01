#include <openssl/ssl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "base64.h"
#include "erfunk.h"
#include <pthread.h>

#define DEFLAUT_IP "217.69.139.160"
#define BUF_SIZE 1024

int SSL_library_int();
//const SSL_METHOD *SSLv23_client_method();
//int SSL_set_fd(SSL *ssl, int fd);
//SSL *SSL_new(SSL_CTX *ctx);

struct sockaddr_in serv_addr, client_addr;

_Bool isExit = 0;

_Bool break_connect(char* buf)
{
	for(int i=0; i<strlen(buf); i++){
		if((buf[0] == 'Q') & (buf[1] == 'U') 
		   & (buf[2] == 'I') & (buf[3] == 'T')){isExit = 1;return 1;}
	}
	return 0;	
}

int send_message(void *argv)
{
	while (1)
	{
		char buf[BUF_SIZE];
		SSL *ssl = (SSL*) argv;
		memset(buf, '\0', sizeof(buf));	
		fgets(buf,sizeof(buf), stdin);
		//sscanf(stdin,"%s", buf, sizeof(buf));
		SSL_write(ssl,buf, strlen(buf));
		if(break_connect(buf)){break;}	
	}
	return 0;
}




int main(){

	system("clear");
	pthread_t thread;
	
	SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_client_method());
	
	int client = socket(AF_INET, SOCK_STREAM,0);
	SSL *ssl = SSL_new(ssl_ctx);
	
	serv_addr.sin_addr.s_addr = inet_addr(DEFLAUT_IP); // IP к кому подключаемся
	serv_addr.sin_family = AF_INET; // По какому протаколу подключаемся 
	serv_addr.sin_port = htons(465); // Порт для подключения 
	
	
	SSL_set_fd(ssl, client);
	
	printf("Clien socket created. \n");
	
	printf("Wait for the connect...\n");
	socklen_t size = sizeof(serv_addr);
	Connect(client, (struct sockaddr *)&serv_addr, size);
	SSL_connect(ssl);
	printf("Connect SSL: sucsses. \n");
	
	char buf[BUF_SIZE];
	char mail[BUF_SIZE];
	char buf64[BUF_SIZE];
	bzero(buf64, sizeof(buf64));
	memset(buf, '\0', sizeof(buf));
	memset(mail, '\0', sizeof(mail));
	SSL_read(ssl,buf, sizeof(buf));
	printf("%s",buf);
	
	strcpy(buf, "EHLO mail.ru\n");
	SSL_write(ssl,buf, strlen(buf));
	
	memset(buf, '\0', sizeof(buf));
	SSL_read(ssl,buf, sizeof(buf));
	
	strcpy(buf, "AUTH LOGIN\n");
	SSL_write(ssl,buf, strlen(buf));
	
	memset(buf, '\0', sizeof(buf));
	SSL_read(ssl,buf, sizeof(buf));
	
	printf("Enter email: ");
	scanf("%s",buf);
	strcpy(mail, buf);
	Base64encode(buf64, mail, strlen(buf));
	strcat(buf64, "\n");
	SSL_write(ssl,buf64, strlen(buf64));
	memset(buf64, '\0', sizeof(buf64));
	
	memset(buf, '\0', sizeof(buf));
	SSL_read(ssl,buf, sizeof(buf));
	
	printf("Enter password: ");
	scanf("%s",buf);
	Base64encode(buf64, buf, strlen(buf));
	strcat(buf64, "\n");
	SSL_write(ssl,buf64, strlen(buf64));
	
	memset(buf, '\0', sizeof(buf));
	SSL_read(ssl,buf, sizeof(buf));
	printf("%s\n\n",buf);
	
	/*memset(buf, '\0', sizeof(buf));
	strcpy(buf, "MAIL FROM: ");
	strcat(buf, mail);
	//strcat(buf, "\n");
	printf("%s\n\n",buf);
	SSL_write(ssl,buf, strlen(buf));
	
	memset(buf, '\0', sizeof(buf));
	SSL_read(ssl,buf, sizeof(buf));*/
	
	//system("clear");
	
	pthread_create(&thread, NULL, (void*)send_message, (void*)ssl);
	
	
	while(1){
		
		bzero(buf, sizeof(buf));
		SSL_read(ssl,buf, sizeof(buf));
		printf("%s\n",buf);
		if(isExit){break;}
	}
	
	printf("\nGoodBye...\n");
	close(client);
	
	return 0;
}	

