#include "../whitespace.h++"
#include "opparserstate.h++"

#define BOPCOUNT 32

static std::string ops[BOPCOUNT]={
	"=>","=<",">=","<=","<>","==","!=>","!=<","!>=","!<=","!<>","!=","!>","!<",">","<",
	"**","//","*","/","+","-",
	"&&","&","||","|",
	//"@@","@*","@/","@+","@-","@&","@|","@",
};

// zero for unary ops
static Precedence bprecedences[BOPCOUNT]={
	COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,COMP,
	POWER,MULT,MULT,MULT,ADD,ADD,
	AND,BITAND,OR,BITOR,
	//"@@","@*","@/","@+","@-","@&","@|","@",
};

bool BinaryOpParser::run(ParserState<BinaryOp> *state){
	Buffer *source=state->source;
	size_t starti=skipWhitespace(source,state->start);
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
		state->value=new BinaryOp{.op=new std::string(ops[opi]),.precedence=bprecedences[opi]};
		state->end=starti+i;
		return true;
	}
	return false;
}

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

bool UnaryOpParser::run(ParserState<UnaryOp> *state){
	Buffer *source=state->source;
	size_t starti=skipWhitespace(source,state->start);
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
		state->value=new UnaryOp{.op=new std::string(ops[opi])/*,.precedence=uprecedences[opi]*/};
		state->end=starti+i;
		return true;
	}
	return false;
}