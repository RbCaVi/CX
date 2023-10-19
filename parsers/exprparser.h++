#ifndef EXPRPARSER_H
#define EXPRPARSER_H

#include <vector>
#include <tuple>

#include "parser.h++"
#include "valueparser.h++"
#include "opparser.h++"

enum class ExprType{
	VALUE,EXPR
};

class Expr;

struct ExprChild{
	ExprType type;
	union {
		Expr *expr;
		Value *value;
	};
};

struct Expr{
	std::vector<ExprChild*> *children;
	std::string *op;
};

class ExprParser:public Parser<Expr>{
private:
	ValueParser *v;
	BinaryOpParser *op;
public:
	ExprParser();
	bool run(ParserState<Expr> *state);
};

#endif