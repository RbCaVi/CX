#ifndef PARSER_H
#define PARSER_H

#include "../buffer.h++"

template<class T>
class Parser{
public:
	size_t start,end;
	Buffer *source;

	T *value;

	Parser(Buffer *source);

	virtual bool run(size_t start)=0;
	virtual bool backtrack()=0;

//	virtual NextIterator<std::string> *getLines()=0;
};
#endif