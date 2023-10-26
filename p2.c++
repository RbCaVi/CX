#include <iostream>
#include <type_traits>

#include "buffer.h++"
#include "whitespace.h++"
#include "parsers/intparser.h++"
#include "parsers/commasepparser.h++"

int main(int,char**){
	Buffer *s=new Buffer("1,3 ,5, 5");
	CommaSepParser<bigint> *p=new CommaSepParser(new IntParser());
	std::cout << p->cparser->s << " cssx" << std::endl;
	auto *st=new CommaSepParser<bigint>::State(s,0);
	auto r=p->run(*st);
	auto state=*st;
	//auto [r,state]=p->runnew(s,0);
	CommaSepParser<bigint>::Value value=p->getValue(state);
	std::cout << "r " << r << std::endl;
	//std::cout << "r2 " << r2 << std::endl;
	std::cout << "p->start " << state.start << std::endl;
	std::cout << "p->end " << state.end << std::endl;
	//std::cout << "p->value " << *(state.value) << std::endl;
	std::cout << "value->size() " << value.size() << std::endl;
}