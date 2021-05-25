# VPATH=$(find /usr/include/* -name "sys"):.
# VPATH=$(find /usr/include/* -name "sys"):.
TCP_SERVER_CLINTE=tcp_process.o tcp_client.o

all: server client

client:${TCP_SERVER_CLIENT} client.o 
	gcc -o  client ${TCP_SERVER_CLIENT} 

server: ${TCP_SERVER_CLIENT} server.o 
	gcc -o  client ${TCP_SERVER_CLIENT} 

clean: 
	- rm -f client server *.o
	- rm -f a.out 
