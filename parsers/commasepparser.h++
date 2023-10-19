#ifndef COMMASEPPARSER_H
#define COMMASEPPARSER_H

#include <vector>

#include "parser.h++"
#include "stringparser.h++"

template<class T>
class CommaSepParser:public Parser<std::vector<ParserState<T*>>,std::vector<T>>{
public:
	Parser<T> parser;
	StringParser cparser;
	CommaSepParser(Parser<T> parser);
	bool run(ParserState<std::vector<ParserState<T*>>> *state) override;
	Parser<T>::Value getValue(ParserState<std::vector<ParserState<T*>>> *state) override;
};
#endif
