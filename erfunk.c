#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define EXIT_CODE '#'
#define BUF_SIZE 256

int Socket(int domain, int type, int protocol){
	int res = socket(domain, type, protocol);
	if(res == -1){
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	else{printf("SERVER:Criete socket succses.\n");}
	return res;
}	

void Bind(int sockfd, const struct sockaddr *addr, int addrlen){
	int res = bind(sockfd, addr, addrlen);
	if( res == -1){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}	
	else{printf("SERVER: Bind seccsesful.\n");}
} 

		
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
	printf("SERVER:Srart accept...");
	int res = accept(sockfd, addr, addrlen);
	if (res < 0){
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
	else{printf("sucsses;\n\n");}
	return res;
}

_Bool Break_Connect(char* mess){
	for(int i = 0; i < strlen(mess); i++ ){
		if(mess[i] == EXIT_CODE){return 1;}
	}
	return 0;
}


void WriteTo(int fd, char *buf, char *name){

	fprintf(stdout, "%s:\n",name);
	fgets(buf, BUF_SIZE, stdin);
	send(fd, buf, BUF_SIZE,0);
	
}


void ReadFrom(int fd, char *buf, char *name){

	read(fd, buf, BUF_SIZE);
	fprintf(stdout, "%s:%s\n",name,buf);
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
	int res = connect(sockfd, addr, addrlen);
	if(res == -1){
		perror("connect failed");
		exit(EXIT_FAILURE);
		}
	else perror("Connect");	
	} 
/*int ReadFromClient(int fd, char *buf){
	int read_messenge;
	
	read_messenge = read(fd, buf, BUF_SIZE);
	if(read_messenge<0){
		perror("Read:");
		return -1;
		} 
	else if (read_messenge == 0){return -1;}	
	else{fprintf(stdout, "CLIENT:%s\n",buf);}
}

int WriteToServer(int fd, char *buf){

	int write_messenge;
	unsigned char *s; 
	
	fprintf(stdout, "CLIENT:");
	buf[strlen(buf)-1] = 0;

	write_messenge = write(fd, buf, strlen(buf) + 1);
	if(write_messenge<0){perror("Write"); return -1;}
	if(strstr(buf, "stop")){return -1;}

	return 0;
}




void Listen(int sockfd, int backlog){
	int res = listen(sockfd, backlog);
	if(res == -1){
		perror("listen faled");
		exit(EXIT_FAILURE);
	}
	else printf("SERVER:listening clients...");
}		




void Inet_pton(int af, const char *src, void *dst){
	int res = inet_pton( af, src, dst);
	if(res == 0 ){
		printf("inet pton faled: scr dose not contain a character");
		exit(EXIT_FAILURE);
	}	
	if(res == -1){
		perror("inet_pton failed");
		exit(EXIT_FAILURE);
	}
		
}

							*/
	
		
		
		
		
		
		
		
		
		



