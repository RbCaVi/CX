#ifndef INTPARSER_H
#define INTPARSER_H

#include "parser.h++"

typedef long long unsigned int bigint;

class IntParser:public Parser<bigint>{
	bool run(ParserState<bigint> *state) override;
};

#endif