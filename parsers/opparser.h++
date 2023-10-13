#ifndef OPPARSER_H
#define OPPARSER_H

#include <string>

#include "parser.h++"

struct BinaryOp{
	std::string *op;
	unsigned int precedence;
};

class BinaryOpParser:public Parser<BinaryOp>{
	int index;
public:
	
	BinaryOpParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};

struct UnaryOp{
	std::string *op;
	//unsigned int precedence;
};

class UnaryOpParser:public Parser<UnaryOp>{
	int index;
public:
	
	UnaryOpParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif