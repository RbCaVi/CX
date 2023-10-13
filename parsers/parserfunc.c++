template<class T>
struct ParserState{
	Buffer source;
	size_t start,end;
	bool success;
	T *value;
}

template<class T,class BtInfo>
struct BtParserState:public ParseResult<T>{
	BtInfo *btinfo;
}

template<class T>
class Parser{
	ParseResult run(ParseResult )
}