make = make upper-cflags="$(cflags)"

cxx = g++ $(cflags) $(CFLAGS)

cflags := $(upper-cflags)

# cflags := $(cflags) -I..

# c++-cpp-output
# preprocess headers

.PHONY: all clean

all: parser.o intparser.o opparser.o valueparser.o exprparser.o

parser.o: parser.c++ parser.h++ ../buffer.h++
	$(cxx) -c $< -o $@

intparser.o: intparser.c++ intparser.h++ parser.h++ ../buffer.h++ ../whitespace.h++
	$(cxx) -c $< -o $@

stringparser.o: stringparser.c++ stringparser.h++ parser.h++ ../buffer.h++ ../whitespace.h++
	$(cxx) -c $< -o $@

opparser.o: opparser.c++ opparser.h++ parser.h++ ../buffer.h++ ../whitespace.h++
	$(cxx) -c $< -o $@

valueparserpart.o: valueparser.c++ valueparser.h++ intparser.h++ parser.h++ ../buffer.h++
	$(cxx) -c $< -o $@

valueparser.o: valueparserpart.o intparser.o
	ld -r $^ -o $@

exprparserpart.o: exprparser.c++ exprparser.h++ opparser.h++ parser.h++ ../buffer.h++
	$(cxx) -c $< -o $@

exprparser.o: exprparserpart.o valueparser.o opparser.o
	ld -r $^ -o $@

clean:
	rm -f *.o