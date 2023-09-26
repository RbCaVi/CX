#!/bin/sh

#define parameters which are passed in.
type=$1
typelower=$(echo $type|tr '[:upper:]' '[:lower:]')
typeupper=$(echo $type|tr '[:lower:]' '[:upper:]')
typecamel=$(echo $typeupper|head -c 1;echo $type|tail -c +2)

cat > ${typelower}parser.h++ << EOF
#ifndef ${typeupper}PARSER_H
#define ${typeupper}PARSER_H

#include "parser.h++"

class ${typecamel}Parser:public Parser{
public:
	
	${typecamel}Parser(Buffer *source);
	bool run(size_t start);
	bool backtrack();
};
#endif
EOF

cat > ${typelower}parser.c++ << EOF
#include "${typelower}parser.h++"

${typecamel}Parser::${typecamel}Parser(Buffer *source):Parser(source){}

bool ${typecamel}Parser::run(size_t start){
	this->start=start;
	end=this->start;
	return true;
}

bool ${typecamel}Parser::backtrack(){
	return false;
};
EOF