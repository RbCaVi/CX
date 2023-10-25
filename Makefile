.PHONY: all test clean FORCE

make = make upper-cflags="$(cflags)"

cxx = g++ $(cflags) $(CFLAGS)

cflags := -std=c++20 -ggdb -g -Og -gdwarf-4

all: p2

parsers/%: parsers/Makefile FORCE
	$(make) -C parsers $*

whitespace.o: whitespace.c++ whitespace.h++
	$(cxx) -c $< -o $@

buffer.o: buffer.c++ buffer.h++
	$(cxx) -c $< -o $@

file.o: file.c++ file.h++ buffer.h++
	$(cxx) -c $< -o $@

p2.o: p2.c++ parsers/intparser.h++ parsers/stringparser.h++ parsers/variantparser.h++ parsers/parser.h++ file.h++ buffer.h++ whitespace.h++
	$(cxx) -c $< -o $@

p2: p2.o parsers/intparser.o parsers/stringparser.o parsers/parser.o buffer.o whitespace.o
	$(cxx) $^ -o $@

test: parsers/all
	cd tests&&CFLAGS="$(cflags) $(CFLAGS)" bash test.sh tests.json

clean:
	rm -f p2
	rm -f *.o
	$(make) -C parsers clean

FORCE: