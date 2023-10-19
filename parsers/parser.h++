#ifndef PARSER_H
#define PARSER_H

#include <utility>
#include "../buffer.h++"

struct BaseParserState{
	Buffer *source;
	size_t start,end;

	BaseParserState(Buffer *source,size_t start);
};

template<class T>
struct ParserState:public BaseParserState{
	T *value;
	ParserState(Buffer *source,size_t start):BaseParserState(source,start){}
};

template<class T>
class Parser{
public:
	typedef ParserState<T> State;
	std::pair<bool,ParserState<T>*> runnew(Buffer *source,size_t start){
		ParserState<T> *state=new ParserState<T>(source,start);
		return std::pair(run(state),state);
	}
	virtual bool runback(ParserState<T> *state,bool backwards){
		if(backwards){
			return backtrack(state);
		}else{
			return run(state);
		}
	}
	virtual bool run(ParserState<T> *state){return false;}
	virtual bool backtrack(ParserState<T> *state){return false;}
};

#endif