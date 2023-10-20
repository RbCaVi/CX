#include "intparser.h++"

#include "../whitespace.h++"

static bool isNum(const char c,unsigned int base){
	if(base>10){
		return (c>='a'&&c-'a'<base-10)||(c>='a'&&c-'A'<base-10)||(c>='0'&&c<'9');
	}
	return c>='0'&&c<('0'+base);
}

static int toNum(const char c,unsigned int base){
	if(base>10&&((c>='a'&&c-'a'<base-10)||(c>='A'&&c-'A'<base-10))){
		if(c>='a'&&c-'a'<base-10){
			return 10+c-'a';
		}else{
			return 10+c-'A';
		}
		return true;
	}
	return c-'0';
}

bool IntParser::run(ParserState<bigint> *state){
	state->value=new bigint(0);
	bigint *value=state->value;
	Buffer *source=state->source;
	size_t i;
	unsigned int base=10;
	bool firstdigit=true;
	size_t starti=skipWhitespace(source,state->start);
	for(i=starti;i<source->length&&isNum((*source)[i],base);i++){
		(*(state->value))*=base;
		int toAdd=toNum((*source)[i],base);
		if(toAdd==0&&firstdigit){
			// octal/hex literals?
			i++;
			char letter=(*source)[i];
			if(letter=='x'||letter=='X'){
				base=16;
			}else if(letter=='b'||letter=='B'){
				base=2;
			}else if(letter=='o'||letter=='O'){
				base=8;
			}
		}
		(*value)+=toAdd;
		firstdigit=false;
	}
	if(i==starti){
		return false;
	}
	state->end=i;
	return true;
}

