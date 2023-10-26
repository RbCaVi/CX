#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include "parser.h++"

#include <string>
#include <variant> // for std::monostate

class StringParser:public Parser<std::monostate>{
public:
	const std::string &s;
	StringParser(const std::string &s);
	bool run(ParserState<std::monostate> &state) override;
	std::monostate getValue(ParserState<std::monostate> &state) override;
};

#endif