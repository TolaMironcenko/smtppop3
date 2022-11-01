#ifndef ERFUNK_H
#define ERFUNK_H

#include <sys/types.h>
#include <sys/socket.h>

int Socket(int domain, int type, int protocol);
			
void Bind(int sockfd, const struct sockaddr *addr, int addrlen);
	
//void Listen(int sockfd, int backlog);
			
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

void Connect(int sockfd, const struct sockaddr *addr, int addrlen);

///void Inet_pton(int af, const char *src, void *dst);

_Bool Break_Connect(char *mess);

void WriteTo(int fd, char *buf, char *name);

void ReadFrom(int fd, char *buf, char *name);

int Base64decode_len(const char *bufcoded);
int Base64decode(char *bufplain, const char *bufcoded);
int Base64encode(char *encoded, const char *string, int len);

#endif	
