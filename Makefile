
SHELL   	= /bin/bash
CC      	= g++
CPPFLAGS	= -fPIC -pedantic -Wall -Wextra -march=native -ggdb3 -O3
PARAFLAGS	= -fopenmp
TARGET 		= krater
SOURCES		= $(wildcard src/*.cpp)
HEADERS		= $(wildcard src/*.h)
OBJECTS 	= $(SOURCES:.c=.o)


all:
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $(TARGET)

para:
	$(CC) $(CPPFLAGS) $(PARAFLAGS) $(OBJECTS) -o $(TARGET) -D PARA