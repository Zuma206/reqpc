CC ?= clang

.PHONY: all
all: reqpc.o server.bin

reqpc.o: lib/request.c
	$(CC) -c $^ -o $@

server.bin: src/main.c reqpc.o
	$(CC) $^ -o $@ -I lib