#include "stringparser.h++"

#include "../whitespace.h++"

StringParser::StringParser(const std::string &s):s(s){}

bool StringParser::run(ParserState<std::string> &state){
	size_t starti=skipWhitespace(state.source,state.start);
	bool matched=true;
	size_t i;
	for(i=0;i<s.size();i++){
		if(s[i]!=(*state.source)[starti+i]){
			matched=false;
			break;
		}
	}
	state.end=i+starti;
	return matched;
}

std::monostate StringParser::getValue(ParserState<std::string> &state){
	return {};
}