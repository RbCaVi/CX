#include "../buffer.h++"

struct BaseParserState{
	Buffer source;
	size_t start,end;

	BaseParserState(Buffer *source,size_t start);
}

template<class T>
struct ParserState:public BaseParserState{
	T *value;
}

template<class T>
class Parser{
	virtual bool run(ParserState<T> *state);
	virtual bool backtrack(ParserState<T> *state);
}