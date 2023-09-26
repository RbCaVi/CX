#include "valueparser.h++"

ValueParser::ValueParser(Buffer *source):Parser(source){}

ValueType nextType(ValueType type){
	switch(type){
	case ValueType::INT:
		return ValueType::END;
	default:
		return ValueType::END;
	}
}

void ValueParser::nextParser(){
	switch(type){
	case ValueType::START:
		parser.i=new IntParser(source);
		type=ValueType::INT;
		return;
	case ValueType::INT:
		delete parser.i;
		type=ValueType::END;
		return;
	default:
		type=ValueType::END;
		return;
	}
}

void ValueParser::setValue(){
	switch(type){
	case ValueType::INT:
		value->i=parser.i->value;
	}
}

bool ValueParser::run(size_t start){
	this->start=start;
	type=ValueType::INT;
	nextParser();
	while(type!=ValueType::END){
		Parser *p;
		switch(type){
		case ValueType::INT:
			p=parser.i;
		}
		bool result=p->run(start);
		if(result){
			setValue();
			end=p->end;
			return true;
		}else{
			nextParser();
		}
	}
	return false;
}

bool ValueParser::backtrack(){
	bool backtrack=true;
	while(type!=ValueType::END){
		Parser *p;
		switch(type){
		case ValueType::INT:
			p=parser.i;
		}
		bool result;
		if(backtrack){
			result=p->backtrack();
		}else{
			result=p->run(start);
		}
		if(result){
			setValue();
			end=p->end;
			return true;
		}else{
			nextParser();
		}
	}
	return false;
};