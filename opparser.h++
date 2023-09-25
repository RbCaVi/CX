#ifndef OPPARSER_H
#define OPPARSER_H

#include <string>

#include "parser.h++"
#include "buffer.h++"

class OpParser:public Parser{
	int index;
public:
	std::string *op;
	unsigned int precedence;
	
	OpParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif