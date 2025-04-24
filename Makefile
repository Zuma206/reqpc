CC ?= clang
AR ?= ar

MK_FOLDER ?= mkdir $@
MK_OBJECT ?= $(CC) -o $@ -c
MK_ARCHIVE ?= $(AR) cr $@
MK_EXECUTABLE ?= $(CC) -o $@

build/test-server: build build/libreqpc.a src/main.c
	$(MK_EXECUTABLE) src/main.c -I lib -L build -l reqpc -g

build/libreqpc.a: build build/reqpc-request.o build/reqpc-buffer.o
	$(MK_ARCHIVE) build/reqpc-request.o build/reqpc-buffer.o

build/reqpc-request.o: build lib/request.c
	$(MK_OBJECT) lib/request.c

build/reqpc-buffer.o: build lib/buffer.c
	$(MK_OBJECT) lib/buffer.c

build:
	$(MK_FOLDER)