all:
	gcc -Wall -o client Client.c erfunk.c base64.c -lssl -lpthread
	gcc -Wall -o client2 Client2.c erfunk.c base64.c -lssl -lpthread
