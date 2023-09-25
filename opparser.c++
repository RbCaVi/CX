#include "whitespace.h++"
#include "opparser.h++"

#define OPCOUNT 33

static std::string ops[OPCOUNT]={
	"=>","=<",">=","<=","<>","==","!=>","!=<","!>=","!<=","!<>","!=","!>","!<",">","<",
	"**","//","*","/","+","-",
	"&&","&","||","|","!",
	//"@@","@*","@/","@+","@-","@&","@|","@",
};

// zero for unary ops
static unsigned int precedences[OPCOUNT]={
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	6,8,8,8,7,7,
	1,4,2,5,0,
	//"@@","@*","@/","@+","@-","@&","@|","@",
};

OpParser::OpParser(Buffer *source):Parser(source){}

bool OpParser::run(size_t start){
	this->start=start;
	size_t starti=skipWhitespace(source,start);
	bool matched=false;
	size_t i,opi;
	for(opi=0;opi<OPCOUNT;opi++){
		matched=true;
		std::string *op=&ops[opi];
		for(i=0;i<op->size();i++){
			if((*op)[i]!=(*source)[starti+i]){
				matched=false;
				break;
			}
		}
		if(matched){
			break;
		}
	}
	if(matched){
		op=&ops[opi];
		precedence=precedences[opi];
		end=start+i;
		return true;
	}
	return false;
}

bool OpParser::backtrack(){
	return false;
};