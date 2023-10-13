#include <iostream>

#include "buffer.h++"
#include "whitespace.h++"
#include "parsers/exprparser.h++"

int main(int,char**){
	Buffer *s=new Buffer("  0x456abc +45");
	printf("%i\n",skipWhitespace(s,0));
	ExprParser *p=new ExprParser(s);
	bool r=p->run(0);
 	ValueParser *p2=new ValueParser(s);
	bool r2=p2->run(11);
	std::cout << "r " << r << std::endl;
	std::cout << "r2 " << r2 << std::endl;
	std::cout << "p->start " << p->start << std::endl;
	std::cout << "p->end " << p->end << std::endl;
	std::cout << "*(p->value->op) " << *(p->value->op) << std::endl;
	std::cout << "*(p->value->op) " << *(p->value->op) << std::endl;
}