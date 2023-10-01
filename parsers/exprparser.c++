#include "exprparser.h++"

ExprParser::ExprParser(Buffer *source):Parser(source),children(new std::list<ValueParser*>()){}

bool ExprParser::run(size_t start){
	this->start=start;
	// parse two values and a binary op
	ValueParser *v1=new ValueParser(source);
	children->push_back(v1);
	BinaryOpParser *o=new BinaryOpParser(source);
	ValueParser *v2=new ValueParser(source);
	children->push_back(v2);
	bool out1=v1->run(start);
	if(!out1){
		return false;
	}
	bool out2=o->run(v1->end);
	if(!out2){
		return false;
	}
	bool out3=v2->run(o->end);
	if(!out3){
		return false;
	}
	end=v2->end;
	return true;
}

bool ExprParser::backtrack(){
	return false;
};
