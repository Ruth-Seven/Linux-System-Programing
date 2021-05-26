# VPATH=$(find /usr/include/* -name "sys"):.
# VPATH=$(find /usr/include/* -name "sys"):.
TCP_SERVER_CLIENT=tcp_process.o
VPATH=..:.
all: server client

client:$(TCP_SERVER_CLIENT) client.o 
	gcc -o  $@ $^

server: $(TCP_SERVER_CLIENT) server.o 
	gcc -o  $@ $^

clean: 
	- rm -f client server *.o
	- rm -f a.out 
