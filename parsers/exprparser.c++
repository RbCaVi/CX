#include "exprparser.h++"

#include <iostream>

ExprParser::ExprParser(){
	v=new ValueParser();
	op=new BinaryOpParser();
}

bool ExprParser::run(ParserState<Expr> *state){
	state->value=new Expr{new std::vector<ExprChild*>(),NULL};
	// parse two values and a binary op
	ValueParser::State *vstate1, *vstate2;
	BinaryOpParser::State *opstate;
	bool out1,out2,out3;
	std::tie(out1,vstate1)=v->runnew(state->source,state->start);
	if(!out1){
		return false;
	}
	std::tie(out2,opstate)=op->runnew(state->source,vstate1->end);
	if(!out2){
		return false;
	}
	std::tie(out3,vstate2)=v->runnew(state->source,opstate->end);
	if(!out3){
		return false;
	}
	state->value->op=opstate->value->op;
	state->value->children->push_back(new ExprChild{.type=ExprType::VALUE,.value=vstate1->value});
	state->value->children->push_back(new ExprChild{.type=ExprType::VALUE,.value=vstate2->value});
	state->end=vstate2->end;
	return true;
}