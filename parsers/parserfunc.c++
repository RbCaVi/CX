template<class T>
struct ParseResult{
	size_t start,end;
	T *value;
}

template<class T,class BtInfo>
struct BtParseResult:public ParseResult<T>{
	BtInfo *btinfo;
}