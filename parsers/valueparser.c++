#include "valueparser.h++"

#include <tuple>

ValueParser::ValueParser(){
	i=new IntParser();
}

void nextParser(ParserState<Value> *state){
	switch(state->value->type){
	case ValueType::INT:
		state->value->type=ValueType::END;
		return;
	default:
		state->value->type=ValueType::END;
		return;
	}
}

bool ValueParser::run(ParserState<Value> *state){
	state->value=new Value{};
	size_t end;
	state->value->type=ValueType::INT;
	while(state->value->type!=ValueType::END){
		bool result;
		switch(state->value->type){
		case ValueType::INT:
			{
				ParserState<bigint> *istate;
				std::tie(result,istate)=i->runnew(state->source,state->start);
				state->value->i=istate;
				state->end=istate->end;
			}
			break;
		}
		if(result){
			return true;
		}else{
			nextParser(state);
		}
	}
	return false;
}
/*
bool ValueParser::backtrack(ParserState<Value> *state){
	size_t end;
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
			state->end=end;
			return true;
		}else{
			nextParser(state);
		}
	}
	return false;
};*/