CC = gcc
LIB = wiringPi

#.PHONY: default compile build run
default: compile
compile: main.c
	$(CC) main.c -l$(LIB) -o v4
run:
	sudo ./v4 start
