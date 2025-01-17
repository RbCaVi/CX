#include "exprparser.h++"

#include <iostream>

ExprParser::ExprParser(Buffer *source):Parser(source),children(new std::vector<ValueParser*>()){}

bool ExprParser::run(size_t start){
	this->start=start;
	value=new Expr{new std::vector<ExprChild*>(),NULL};
	// parse two values and a binary op
	ValueParser *v1=new ValueParser(source);
	children->push_back(v1);
	op=new BinaryOpParser(source);
	ValueParser *v2=new ValueParser(source);
	children->push_back(v2);
	bool out1=v1->run(start);
	std::cout << out1 << ' ' << v1->end << std::endl;
	if(!out1){
		return false;
	}
	bool out2=op->run(v1->end);
	std::cout << out2 << ' ' << op->end << std::endl;
	if(!out2){
		return false;
	}
	bool out3=v2->run(op->end);
	std::cout << out3 << ' ' << v2->end << std::endl;
	if(!out3){
		return false;
	}
	end=v2->end;
	value->op=op->value->op;
	value->children->push_back(new ExprChild{.type=ExprType::VALUE,.value=v1->value});
	value->children->push_back(new ExprChild{.type=ExprType::VALUE,.value=v2->value});
	return true;
}

bool ExprParser::backtrack(){
	return false;
};
