.PHONY: all clean

make = make upper-cflags="$(cflags)"

cxx = g++ $(cflags) $(CFLAGS)

cflags := -std=c++20 -ggdb -g -Og -gdwarf-4

all: p2

parsers/%: parsers/Makefile
	$(make) -C parsers $*

whitespace.o: whitespace.c++ whitespace.h++
	$(cxx) -c $< -o $@

buffer.o: buffer.c++ buffer.h++
	$(cxx) -c $< -o $@

file.o: file.c++ file.h++ buffer.h++
	$(cxx) -c $< -o $@

p2.o: p2.c++ parsers/exprparser.h++ parsers/valueparser.h++ parsers/intparser.h++ parsers/opparser.h++ parsers/parser.h++ file.h++ buffer.h++ whitespace.h++
	$(cxx) -c $< -o $@

p2: p2.o parsers/exprparser.o parsers/parser.o buffer.o whitespace.o
	$(cxx) $^ -o $@

clean:
	rm -f p2
	rm -f *.o
	$(make) -C parsers clean