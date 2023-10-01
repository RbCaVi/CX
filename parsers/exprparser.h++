#ifndef EXPRPARSER_H
#define EXPRPARSER_H

#include <list>

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

class Expr{
	std::list<ExprChild*> *children;
	std::string *op;
};

class ExprParser:public Parser{
	std::list<ValueParser*> *children;
	BinaryOpParser *op;
public:
	Expr *e;
	
	ExprParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif
