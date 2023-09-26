# cflags := $(cflags) -I..

# c++-cpp-output
# preprocess headers

.PHONY: all clean

all: parser.o intparser.o opparser.o valueparser.o

parser.o: parser.c++ parser.h++ ../buffer.h++
	g++ $(cflags) $(CFLAGS) -c parser.c++ -o parser.o

intparser.o: intparser.c++ intparser.h++ parser.h++ ../buffer.h++ ../whitespace.h++
	g++ $(cflags) $(CFLAGS) -c intparser.c++ -o intparser.o

opparser.o: opparser.c++ opparser.h++ parser.h++ ../buffer.h++ ../whitespace.h++
	g++ $(cflags) $(CFLAGS) -c opparser.c++ -o opparser.o

valueparser.o: valueparser.c++ valueparser.h++ intparser.h++ parser.h++ ../buffer.h++
	g++ $(cflags) $(CFLAGS) -c valueparser.c++ -o opparser.o

clean:
	rm -f *.o