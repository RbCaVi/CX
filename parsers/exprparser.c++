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


//* The functions referred to in this algorithm are simple single argument functions such as sine, inverse or factorial. */
//* This implementation does not implement composite functions, functions with a variable number of arguments, or unary operators. */

//while there are tokens to be read:
//    read a token
//    if the token is:
//    - a number:
//        put it into the output queue
//    - a function:
//        push it onto the operator stack 
//    - an operator o1:
//        while (
//            there is an operator o2 at the top of the operator stack which is not a left parenthesis, 
//            and (o2 has greater precedence than o1 or (o1 and o2 have the same precedence and o1 is left-associative))
//        ):
//            pop o2 from the operator stack into the output queue
//        push o1 onto the operator stack
//    - a left parenthesis (i.e. "("):
//        push it onto the operator stack
//    - a right parenthesis (i.e. ")"):
//        while the operator at the top of the operator stack is not a left parenthesis:
//            pop the operator from the operator stack into the output queue
//        pop the left parenthesis from the operator stack and discard it
///* After the while loop, pop the remaining items from the operator stack into the output queue. */
//while there are tokens on the operator stack:
//    /* If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. */
//    {assert the operator on top of the stack is not a (left) parenthesis}
//    pop the operator from the operator stack onto the output queue



//while true
//	try to parse unary operators (/casts?)
//	if value
//		push to out with uops
//	else
//		error
//	if binary operator
//		while top.prec>op.prec||(top.prec==op.prec and op.assoc==LEFT)
//			out.push(opstack.pop())
//		push to opstack
//		cycle
//	if func args
//		funccall
//		cycle
//	if index
//		index
//		cycle
//	if end of expr
//		end
//out.push(opstack.pop())
