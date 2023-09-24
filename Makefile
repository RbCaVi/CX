.PHONY: all

cflags:=-std=c++20

all: p2

p2: p2.c++
	g++ $(cflags) $(CFLAGS) p2.c++ -o p2