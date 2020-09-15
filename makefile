# Author: Student
# Compiler flags:
CC = g++
DEBUG = -g
CFLAGS = $(DEBUG) -c -Wall -std=c++11
LDLIBS =

#CHANGE: What to name the executable
TARGET = main

#CHANGE: Source code files
SOURCES = node.cpp filesystem.cpp terminal.cpp main.cpp \

OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDLIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ 

.PHONY : all $(TARGET)

# Must call 'make clean' for cleaning to occur
clean: 
	rm -f $(OBJECTS)

clobber: clean
	rm -f $(TARGET) 

