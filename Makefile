.PHONY: all

cflags:=-std=c++20

all: p2

whitespace.o: whitespace.c++ whitespace.h++
	g++ $(cflags) $(CFLAGS) -c whitespace.c++ -o whitespace.o

buffer.o: buffer.c++ buffer.h++
	g++ $(cflags) $(CFLAGS) -c buffer.c++ -o buffer.o

file.o: file.c++ file.h++ buffer.h++
	g++ $(cflags) $(CFLAGS) -c file.c++ -o file.o

parser.o: parser.c++ parser.h++ buffer.h++
	g++ $(cflags) $(CFLAGS) -c parser.c++ -o parser.o

intparser.o: intparser.c++ intparser.h++ parser.h++ buffer.h++ whitespace.h++
	g++ $(cflags) $(CFLAGS) -c intparser.c++ -o intparser.o

opparser.o: opparser.c++ opparser.h++ parser.h++ buffer.h++ whitespace.h++
	g++ $(cflags) $(CFLAGS) -c opparser.c++ -o opparser.o

p2.o: p2.c++ file.h++ buffer.h++ whitespace.h++
	g++ $(cflags) $(CFLAGS) -c p2.c++ -o p2.o

p2: p2.o intparser.o parser.o buffer.o whitespace.o
	g++ $(cflags) $(CFLAGS) p2.o intparser.o parser.o buffer.o whitespace.o -o p2