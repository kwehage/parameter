CC=clang++
CFLAGS=-I.

all: main.cc parameter.h
	$(CC) main.cc -o parameter_test -std=c++17

