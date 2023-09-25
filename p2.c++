#include <cstdio>

#include "buffer.h++"
#include "whitespace.h++"
#include "intparser.h++"

int main(int,char**){
	Buffer *s=new Buffer("  0x456abc");
	printf("%i\n",skipWhitespace(s,0));
	IntParser *p=new IntParser(s);
	bool r=p->run(0);
	printf("%i %i %i %i\n",r,p->start,p->end,p->value);
}