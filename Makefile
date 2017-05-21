CC=gcc
CFLAGS=-Wall -g -O3
DST_FOLDER=./dist
SRC_FOLDER=./src

all: build-all

build-all: ${SRC_FOLDER}/hello.o ${SRC_FOLDER}/par.o ${SRC_FOLDER}/parimpar.o
	@echo "All programs built."

${SRC_FOLDER}/hello.o: ${SRC_FOLDER}/hello.c
	${CC} ${CFLAGS} -o ${DST_FOLDER}/hello ${SRC_FOLDER}/hello.c

${SRC_FOLDER}/par.o: ${SRC_FOLDER}/par.c
	${CC} ${CFLAGS} -o ${DST_FOLDER}/par ${SRC_FOLDER}/par.c

${SRC_FOLDER}/parimpar.o: ${SRC_FOLDER}/parimpar.c
	${CC} ${CFLAGS} -o ${DST_FOLDER}/parimpar ${SRC_FOLDER}/parimpar.c

clean:
	cp ${DST_FOLDER}/.gitignore .tempgitignore
	rm -rf ${DST_FOLDER}/*
	cp .tempgitignore ${DST_FOLDER}/.gitignore
	rm .tempgitignore
