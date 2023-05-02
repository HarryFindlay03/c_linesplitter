CC = gcc

splitter: splitter.o
	gcc -ansi -o splitter splitter.o
