
SHELL   	= /bin/bash
CC      	= g++
CPPFLAGS	= -pedantic -Wall -Wextra -march=native -O3
PARAFLAGS	= -fopenmp
TARGET 		= krater
SOURCES		= $(wildcard src/*.cpp)
HEADERS		= $(wildcard src/*.h)
OBJECTS 	= $(SOURCES:.c=.o)


all:
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $(TARGET)

para:
	$(CC) $(CPPFLAGS) $(PARAFLAGS) $(OBJECTS) -o $(TARGET) -D PARA