#ifndef COMMASEPPARSER_H
#define COMMASEPPARSER_H

#include <vector>

#include "parser.h++"
#include "stringparser.h++"

template<class T>
class CommaSepParser:public Parser<std::vector<ParserState<T*>>>{
public:
	Parser<T> parser;
	StringParser cparser;
	CommaSepParser(Parser<T> parser);
	bool run(ParserState<std::vector<ParserState<T*>>> *state);
};
#endif
