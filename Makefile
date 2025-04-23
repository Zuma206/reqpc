CC ?= clang

server.bin: src/main.c
	$(CC) $^ -o $@