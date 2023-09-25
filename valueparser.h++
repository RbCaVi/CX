#ifndef VALUEPARSER_H
#define VALUEPARSER_H

#include <string>

#include "parser.h++"
#include "intparser.h++"
#include "buffer.h++"

enum class ValueType{
	START,
	INT,
	END
};

class ValueParser:public Parser{
	union {
		IntParser *i;
	} parser;
	void nextParser();
	void setValue();
public:
	ValueType type;
	union {
		unsigned int i;
	} *value;
	
	ValueParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif