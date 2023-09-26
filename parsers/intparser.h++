#ifndef INTPARSER_H
#define INTPARSER_H

#include "parser.h++"

class IntParser:public Parser{
public:
	unsigned long long value;
	
	IntParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif