#ifndef OPPARSER_H
#define OPPARSER_H

#include <string>

#include "parserstate.h++"

enum Precedence{
	//UNARY=0,
	AND=1,
	OR=2,
	COMP=3,
	BITAND=4,
	BITOR=5,
	POWER=6,
	ADD=7,
	MULT=8,
};

struct BinaryOp{
	std::string *op;
	unsigned int precedence;
};

class BinaryOpParser:public Parser<BinaryOp>{
	int index;
public:
	
	BinaryOpParser(Buffer *source);
	bool run(ParserState<BinaryOp> *state);
};

struct UnaryOp{
	std::string *op;
	//unsigned int precedence;
};

class UnaryOpParser:public Parser<UnaryOp>{
	int index;
public:
	
	UnaryOpParser(Buffer *source);
	bool run(ParserState<UnaryOp> *state);
};
#endif