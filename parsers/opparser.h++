#ifndef OPPARSER_H
#define OPPARSER_H

#include <string>

#include "parser.h++"

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
public:
	bool run(ParserState<BinaryOp> *state) override;
};

struct UnaryOp{
	std::string *op;
	//unsigned int precedence;
};

class UnaryOpParser:public Parser<UnaryOp>{
public:
	bool run(ParserState<UnaryOp> *state) override;
};
#endif