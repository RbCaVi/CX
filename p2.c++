#include <iostream>

#include "buffer.h++"
#include "whitespace.h++"
#include "parsers/intparser.h++"
#include "parsers/tupleparser.h++"

int main(int,char**){
	Buffer *s=new Buffer("1 2");
	printf("%i\n",skipWhitespace(s,0));
	TupleParser<Parser<bigint>,Parser<bigint>> *p=new TupleParser<Parser<bigint>,Parser<bigint>>(new IntParser(),new IntParser());
	auto [r,state]=p->runnew(s,0);
	TupleParser<Parser<bigint>,Parser<bigint>>::Value *value=p->getValue(state);
	std::cout << "r " << r << std::endl;
	//std::cout << "r2 " << r2 << std::endl;
	std::cout << "p->start " << state->start << std::endl;
	std::cout << "p->end " << state->end << std::endl;
	//std::cout << "p->value " << *(state->value) << std::endl;
	//std::cout << "value->size() " << value->size() << std::endl;
	//std::cout << "value[0] " << (*value)[0] << std::endl;
	//std::cout << "value[1] " << (*value)[1] << std::endl;
	//std::cout << "value[2] " << (*value)[2] << std::endl;
	std::cout << "std::get<0> " << std::get<0>(*value) << std::endl;
	std::cout << "std::get<1> " << std::get<1>(*value) << std::endl;
	
}