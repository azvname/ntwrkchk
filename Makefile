CC = gcc
LIB = wiringPi

#.PHONY: default compile build run
default: compile
compile: main.c
	$(CC) -O0 main.c -l$(LIB) -o v4
start:
	sudo ./v4 start
stop:
	sudo ./v4 stop
