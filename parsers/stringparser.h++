#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include "parser.h++"

#include <string>

class StringParser:public Parser<std::string>{
	std::string &s;
	StringParser(std::string s);
	bool run(ParserState<std::string> *state);
};

#endif