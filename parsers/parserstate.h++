#ifndef PARSER_H
#define PARSER_H

#include "../buffer.h++"

struct BaseParserState{
	Buffer *source;
	size_t start,end;

	BaseParserState(Buffer *source,size_t start);
};

template<class T>
struct ParserState:public BaseParserState{
	T *value;
};

template<class T1,class T2>
struct pair{
	T1 x1;
	T2 x2;
}

template<class T>
class Parser{
public:
	virtual pair<bool,ParserState<T>*> run(Buffer *source,size_t start){
		ParserState<T> *state=new ParserState<T>(source,start);
		return pair(run(state),state);
	}
	virtual bool run(ParserState<T> *state);
	virtual bool backtrack(ParserState<T> *state){return false;}
};

#endif