//#include <iterator>
#include <cstdio>

#include "buffer.h++"
#include "whitespace.h++"

class ParserNode{
public:
	size_t start,end;
	Buffer *source;

	ParserNode(Buffer *source):source(source){}

	virtual bool run(size_t start)=0;
	virtual bool backtrack()=0;

//	virtual NextIterator<std::string> *getLines()=0;
};

class IntParser:public ParserNode{
	bool isNum(const char c,unsigned int base){
		if(base>10){
			return (c>='a'&&c-'a'<base-10)||(c>='a'&&c-'A'<base-10)||(c>='0'&&c<'9');
		}
		return c>='0'&&c<('0'+base);
	}

	int toNum(const char c,unsigned int base){
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

public:
	unsigned long long value;

	IntParser(Buffer *source):ParserNode(source){}

	bool run(size_t start){
		this->start=start;
		value=0;
		size_t i;
		unsigned int base=10;
		bool firstdigit;
		for(i=skipWhitespace(source,start);isNum((*source)[i],base)&&i<source->length;i++){
			value*=base;
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
			value+=toAdd;
			firstdigit=false;
		}
		if(i==start){
			return false;
		}
		end=this->start+i;
		return true;
	}

	bool backtrack(){
		return false;
	};
};

int main(int,char**){
	Buffer *s=new Buffer("  0x456abc");
	printf("%i\n",skipWhitespace(s,0));
	IntParser *p=new IntParser(s);
	bool r=p->run(0);
	printf("%i %i %i %i\n",r,p->start,p->end,p->value);
}