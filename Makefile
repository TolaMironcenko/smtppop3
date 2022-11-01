all:
	gcc -Wall -o client Client.c erfunk.c base64.c -L /lib/x86_64-linux-gnu -lssl -lpthread
	gcc -Wall -o client2 Client2.c erfunk.c base64.c -L /lib/x86_64-linux-gnu -lssl -lpthread
