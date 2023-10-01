#ifndef EXPRPARSER_H
#define EXPRPARSER_H

#include <list>

#include "parser.h++"
#include "valueparser.h++"

enum class ExprType{
	VALUE,EXPR
};

class Expr{
	ExprType type;
	union {
		struct {
			std::list<Expr*> *children;
			std::string *op;
		} *expr;
		Value *value;
	};
};

class ExprParser:public Parser{
public:
	Expr *e;
	
	ExprParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif
