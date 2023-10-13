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

struct Value{
	ValueType type;
	union {
		long long unsigned int i;
	};
};

class ValueParser:public Parser<Value>{
	union {
		IntParser *i;
	} parser;
	void nextParser();
	void setValue();
public:
	
	ValueParser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif