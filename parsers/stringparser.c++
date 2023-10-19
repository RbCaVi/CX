#include "stringparser.h++"

#include "../whitespace.h++"

bool StringParser::run(ParserState<std::string> *state){
	size_t starti=skipWhitespace(state->source,state->start);
	bool matched=true;
	for(i=0;i<s->size();i++){
		if(s[i]!=(*source)[starti+i]){
			matched=false;
			break;
		}
	}
	return matched;
}

