#ifndef COMMASEPPARSER_H
#define COMMASEPPARSER_H

#include <vector>

#include "parser.h++"
#include "stringparser.h++"

template<class T,class V=T>
class CommaSepParser:public Parser<std::vector<ParserState<T>*>,std::vector<V>>{
public:
	Parser<T,V> *parser;
	StringParser *cparser;
	CommaSepParser(Parser<T,V> *parser);
	bool run(ParserState<std::vector<ParserState<T>*>> *state) override;
	std::vector<V> *getValue(ParserState<std::vector<ParserState<T>*>> *state) override;
};

#include <tuple>

template<class T,class V>
CommaSepParser<T,V>::CommaSepParser(Parser<T,V> *parser):parser(parser){
	cparser=new StringParser(new std::string(","));
}

template<class T,class V>
bool CommaSepParser<T,V>::run(ParserState<std::vector<ParserState<T>*>> *state){
	state->value=new std::vector<ParserState<T>*>();
	size_t end;

	auto [presult,pstate]=parser->runnew(state->source,state->start);
	state->value->push_back(pstate);
	if(!presult){
		return false;
	}
	end=pstate->end;
	while(true){
		auto [cresult,cstate]=cparser->runnew(state->source,end);
		if(!cresult){
			break;
		}
		end=cstate->end;
		auto [presult,pstate]=parser->runnew(state->source,end);
		if(!presult){
			break;
		}
		state->value->push_back(pstate);
		end=pstate->end;
	}
	state->end=end;
	return true;
}

template<class T,class V>
std::vector<V> *CommaSepParser<T,V>::getValue(ParserState<std::vector<ParserState<T>*>> *state){
	std::vector<V> *out=new std::vector<V>();
	for(auto pstate:*(state->value)){
		out->push_back(*(pstate->value));
	}
	return out;
}
#endif
