#ifndef VALUEPARSER_H
#define VALUEPARSER_H

#include <string>

#include "parserstate.h++"
#include "intparserstate.h++"

enum class ValueType{
	INT,END
};

struct Value{
	ValueType type;
	union {
		IntParser::State *i;
	};
};

class ValueParser:public Parser<Value>{
private:
	IntParser *i;
public:
	ValueParser();
	bool run(ParserState<Value> *state);
};
#endif