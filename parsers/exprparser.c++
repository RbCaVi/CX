#include "exprparser.h++"

ExprParser::ExprParser(Buffer *source):Parser(source){}

bool ExprParser::run(size_t start){
	this->start=start;
	// parse two values and a binary op
	end=this->start;
	return true;
}

bool ExprParser::backtrack(){
	return false;
};
