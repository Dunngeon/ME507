# Makefile for the really simple basic ME507 C++ example.
# OK, it's not really that simple, because it's an example
# that tries to teach how C++ classes work, and those are
# pretty complicated. It's simpler than a full-scale AVR
# project which uses a real time operating system, though.

# This is the name of the C/C++ compiler to use
CC = g++

# These flags tells the compiler to issue lots of warnings if
# it finds anything that seems inappropriate, and to use the
# '99 standard for C++, which is a reasonably modern version
CFLAGS = -Wall -std=c99

# As the first target in this Makefile, this one specifies 
# what happens when you just type 'make.' It compiles the
# C++ source file and links it to make an executable program
all: main.o Spline.o
	$(CC) -o main main.o Spline.o

# This unfamous clean command removes the compiled stuff, 
# which includes the executable, object file, and backup
# files created by the Kate editor
clean:
	rm -f main main.o *~
