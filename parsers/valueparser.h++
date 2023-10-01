#ifndef VALUEPARSER_H
#define VALUEPARSER_H

#include <string>

#include "parser.h++"
#include "intparser.h++"

enum class ValueType{
	START,
	INT,
	END
};

union Value {
	unsigned int i;
};

class ValueParser:public Parser{
	union {
		IntParser *i;
	} parser;
	void nextParser();
	void setValue();
public:
	ValueType type;
	Value *value;
	
	ValueParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif