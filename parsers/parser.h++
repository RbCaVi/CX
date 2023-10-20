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
class ParserBase{
public:
	typedef ParserState<T> State;
	std::pair<bool,State*> runnew(Buffer *source,size_t start){
		State *state=new State(source,start);
		return std::pair(run(state),state);
	}
	virtual bool runback(State *state,bool backwards){
		if(backwards){
			return backtrack(state);
		}else{
			return run(state);
		}
	}
	virtual bool run(State *state){return false;}
	virtual bool backtrack(State *state){return false;}
};

template<class T,class V=T>
class Parser:public ParserBase<T>{
public:
	typedef V Value;
	virtual Value *getValue(ParserBase<T>::State *state)=0;
};

template<class T>
class Parser<T,T>:public ParserBase<T>{
public:
	typedef T Value;
	virtual Value *getValue(ParserBase<T>::State *state) {return state->value;};
};

#endif