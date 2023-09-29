#ifndef OPPARSER_H
#define OPPARSER_H

#include <string>

#include "parser.h++"

class BinaryOpParser:public Parser{
	int index;
public:
	std::string *op;
	unsigned int precedence;
	
	BinaryOpParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};

class UnaryOpParser:public Parser{
	int index;
public:
	std::string *op;
	//unsigned int precedence;
	
	UnaryOpParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif