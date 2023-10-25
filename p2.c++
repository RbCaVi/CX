#include <iostream>

#include "buffer.h++"
#include "whitespace.h++"
#include "parsers/intparser.h++"
#include "parsers/stringparser.h++"
#include "parsers/variantparser.h++"

int main(int,char**){
	Buffer *s=new Buffer("1");
	VariantParser<Parser<bigint>,Parser<std::string>> *p=new VariantParser<Parser<bigint>,Parser<std::string>>(new IntParser(),new StringParser(new std::string(".,")));
	auto [r,state]=p->runnew(s,0);
	VariantParser<Parser<bigint>,Parser<std::string>>::Value *value=p->getValue(state);
	std::cout << "r " << r << std::endl;
	//std::cout << "r2 " << r2 << std::endl;
	std::cout << "p->start " << state->start << std::endl;
	std::cout << "p->end " << state->end << std::endl;
	//std::cout << "p->value " << *(state->value) << std::endl;
	//std::cout << "value->size() " << value->size() << std::endl;
	//std::cout << "value[0] " << (*value)[0] << std::endl;
	//std::cout << "value[1] " << (*value)[1] << std::endl;
	//std::cout << "value[2] " << (*value)[2] << std::endl;
	std::cout << "std::get_if<0> " << std::get_if<0>(value) << std::endl;
	if(std::get_if<0>(value)!=NULL){
		std::cout << "*std::get_if<0> " << *std::get_if<0>(value) << std::endl;
		std::cout << "**std::get_if<0> " << **std::get_if<0>(value) << std::endl;
	}
	std::cout << "std::get_if<1> " << std::get_if<1>(value) << std::endl;
	if(std::get_if<1>(value)!=NULL){
		std::cout << "*std::get_if<1> " << *std::get_if<1>(value) << std::endl;
		std::cout << "**std::get_if<1> " << **std::get_if<1>(value) << std::endl;
	}
	
}