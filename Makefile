
SHELL   	= /bin/bash
CC      	= g++
CPPFLAGS	= -fPIC -pedantic -Wall -Wextra -march=native -ggdb3 -O3
TARGET 		= krater
SOURCES		= $(wildcard src/*.cpp)
HEADERS		= $(wildcard src/*.h)
OBJECTS 	= $(SOURCES:.c=.o)


all: $(TARGET)

$(TARGET):$(SOURCES)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $@