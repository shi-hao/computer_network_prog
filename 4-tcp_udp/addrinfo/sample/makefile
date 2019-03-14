cc:=gcc
target:=al
debug:=-g -O0
all:server client

server:server.c
	$(cc) $(debug) -o $@  $<
client:client.c
	$(cc) $(debug) -o $@  $<

clean:
	rm server client
