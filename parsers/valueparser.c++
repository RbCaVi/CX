#include "valueparser.h++"

ValueParser::ValueParser(Buffer *source):Parser(source){}

void ValueParser::nextParser(){
	switch(value->type){
	case ValueType::START:
		parser.i=new IntParser(source);
		value->type=ValueType::INT;
		return;
	case ValueType::INT:
		delete parser.i;
		value->type=ValueType::END;
		return;
	default:
		value->type=ValueType::END;
		return;
	}
}

void ValueParser::setValue(){
	switch(value->type){
	case ValueType::INT:
		value->i=*(parser.i->value);
	}
}

bool ValueParser::run(size_t start){
	this->start=start;
	value=new Value{};
	nextParser();
	while(value->type!=ValueType::END){
		bool result;
		switch(value->type){
		case ValueType::INT:
			auto p=parser.i;
			result=p->run(start);
			end=p->end;
			break;
		}
		if(result){
			setValue();
			this->end=end;
			return true;
		}else{
			nextParser();
		}
	}
	return false;
}

bool ValueParser::backtrack(){
	bool backtrack=true;
	while(value->type!=ValueType::END){
		bool result;
		switch(value->type){
		case ValueType::INT:
			auto p=parser.i;
			if(backtrack){
				result=p->backtrack();
			}else{
				result=p->run(start);
			}
			end=p->end;
			break;
		}
		if(result){
			setValue();
			this->end=end;
			return true;
		}else{
			nextParser();
		}
	}
	return false;
};