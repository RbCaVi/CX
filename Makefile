.PHONY: all clean

cflags:=-std=c++20

all: p2

parsers/%: parsers/Makefile
	make -C parsers $*

whitespace.o: whitespace.c++ whitespace.h++
	g++ $(cflags) $(CFLAGS) -c whitespace.c++ -o whitespace.o

buffer.o: buffer.c++ buffer.h++
	g++ $(cflags) $(CFLAGS) -c buffer.c++ -o buffer.o

file.o: file.c++ file.h++ buffer.h++
	g++ $(cflags) $(CFLAGS) -c file.c++ -o file.o

p2.o: p2.c++ file.h++ buffer.h++ whitespace.h++
	g++ $(cflags) $(CFLAGS) -c p2.c++ -o p2.o

p2: p2.o parsers/intparser.o parsers/parser.o buffer.o whitespace.o
	g++ $(cflags) $(CFLAGS) $^ -o $@

clean:
	rm -f p2
	rm -f *.o
	make -C parsers clean