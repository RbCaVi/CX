# cflags := $(cflags) -I..

# c++-cpp-output
# preprocess headers

.PHONY: all clean

all: parser.o intparser.o opparser.o valueparser.o

parser.o: parser.c++ parser.h++ ../buffer.h++
	g++ $(cflags) $(CFLAGS) -c $< -o $@

intparser.o: intparser.c++ intparser.h++ parser.h++ ../buffer.h++ ../whitespace.h++
	g++ $(cflags) $(CFLAGS) -c $< -o $@

opparser.o: opparser.c++ opparser.h++ parser.h++ ../buffer.h++ ../whitespace.h++
	g++ $(cflags) $(CFLAGS) -c $< -o $@

valueparserpart.o: valueparser.c++ valueparser.h++ intparser.h++ parser.h++ ../buffer.h++
	g++ $(cflags) $(CFLAGS) -c $< -o $@

valueparser.o: valueparserpart.o intparser.o
	ld -r $^ -o $@

clean:
	rm -f *.o