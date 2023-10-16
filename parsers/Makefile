make = make upper-cflags="$(cflags)"

cxx = g++ $(cflags) $(CFLAGS)

cflags := $(upper-cflags)

# cflags := $(cflags) -I..

# c++-cpp-output
# preprocess headers

.PHONY: all clean

all: intparserstate.o opparser.o valueparser.o exprparser.o

intparserstate.o: intparserstate.c++ intparserstate.h++ parserstate.h++ ../buffer.h++ ../whitespace.h++
	$(cxx) -c $< -o $@

opparser.o: opparser.c++ opparser.h++ parserstate.h++ ../buffer.h++ ../whitespace.h++
	$(cxx) -c $< -o $@

valueparserpart.o: valueparser.c++ valueparser.h++ intparserstate.h++ parserstate.h++ ../buffer.h++
	$(cxx) -c $< -o $@

valueparser.o: valueparserpart.o intparserstate.o
	ld -r $^ -o $@

exprparserpart.o: exprparser.c++ exprparser.h++ opparser.h++ parserstate.h++ ../buffer.h++
	$(cxx) -c $< -o $@

exprparser.o: exprparserpart.o valueparser.o opparser.o
	ld -r $^ -o $@

clean:
	rm -f *.o