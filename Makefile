CC=gcc
CFLAGS=-Wall -g
DST_FOLDER=./dist

all: hello.o par.o parimpar.o
	
hello.o: hello.c
	${CC} ${CFLAGS} -o ${DST_FOLDER}/hello hello.c

par.o: par.c
	${CC} ${CFLAGS} -o ${DST_FOLDER}/par par.c

parimpar.o: parimpar.c
	${CC} ${CFLAGS} -o ${DST_FOLDER}/parimpar parimpar.c
