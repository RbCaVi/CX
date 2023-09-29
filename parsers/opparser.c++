#include "../whitespace.h++"
#include "opparser.h++"

#define BOPCOUNT 32

static std::string ops[BOPCOUNT]={
	"=>","=<",">=","<=","<>","==","!=>","!=<","!>=","!<=","!<>","!=","!>","!<",">","<",
	"**","//","*","/","+","-",
	"&&","&","||","|",
	//"@@","@*","@/","@+","@-","@&","@|","@",
};

enum Precedence{
	UNARY=0,
	AND=1,
	OR=2,
	COMP=3,
	BITAND=4,
	BITOR=5,
	POWER=6,
	ADD=7,
	MULT=8,
};

// zero for unary ops
static Precedence bprecedences[BOPCOUNT]={
	COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,
	POWER,MULT,MULT,MULT,ADD,ADD,
	AND,BITAND,OR,BITOR,
	//"@@","@*","@/","@+","@-","@&","@|","@",
};

BinaryOpParser::BinaryOpParser(Buffer *source):Parser(source){}

bool BinaryOpParser::run(size_t start){
	this->start=start;
	size_t starti=skipWhitespace(source,start);
	bool matched=false;
	size_t i,opi;
	for(opi=0;opi<BOPCOUNT;opi++){
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
		op=new std::string(ops[opi]);
		precedence=bprecedences[opi];
		end=start+i;
		return true;
	}
	return false;
}

bool BinaryOpParser::backtrack(){
	return false;
};

#define UOPCOUNT 5

static std::string uops[UOPCOUNT]={
	"*","+","-","&","!",
	//"@@","@*","@/","@+","@-","@&","@|","@",
};

// zero for unary ops
/*static Precedence uprecedences[UOPCOUNT]={
	UNARY,UNARY,UNARY,UNARY,UNARY,
	//"@@","@*","@/","@+","@-","@&","@|","@",
};*/

UnaryOpParser::UnaryOpParser(Buffer *source):Parser(source){}

bool UnaryOpParser::run(size_t start){
	this->start=start;
	size_t starti=skipWhitespace(source,start);
	bool matched=false;
	size_t i,opi;
	for(opi=0;opi<UOPCOUNT;opi++){
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
		op=new std::string(ops[opi]);
		//precedence=uprecedences[opi];
		end=start+i;
		return true;
	}
	return false;
}

bool UnaryOpParser::backtrack(){
	return false;
};