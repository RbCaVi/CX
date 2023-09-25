#include "whitespace.h++"

bool isWhitespace(const char c){
	return c==' '||c=='\n'||c=='\t'||c=='\f'||c=='\v';
}

size_t skipWhitespace(Buffer *source,size_t start){
	size_t i=start;
	while(isWhitespace((*source)[i])&&i<source->length){
		i++;
	}
	return i;
}