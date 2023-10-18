#include <iostream>

#include "buffer.h++"
#include "whitespace.h++"
#include "parsers/exprparserstate.h++"

int main(int,char**){
	Buffer *s=new Buffer("  0x456abc +45");
	printf("%i\n",skipWhitespace(s,0));
	ExprParser *p=new ExprParser();
	bool r;
	ExprParser::State *state;
	std::tie(r,state)=p->runnew(s,0);
	std::cout << "r " << r << std::endl;
	//std::cout << "r2 " << r2 << std::endl;
	std::cout << "p->start " << state->start << std::endl;
	std::cout << "p->end " << state->end << std::endl;
	//std::cout << "p->value " << *(state->value) << std::endl;
	std::cout << "*(p->value->op) " << *(state->value->op) << std::endl;
	std::cout << "*(p->value->op) " << *(state->value->op) << std::endl;
}