#include "commasepparser.h++"

#include <tuple>

template<class T>
CommaSepParser<T>::CommaSepParser(Parser<T> parser):parser(parser){
	cparser=new StringParser(",");
}

template<class T>
bool CommaSepParser<T>::run(ParserState<std::vector<ParserState<T*>>> *state){
	size_t end;

	bool presult;
	ParserState<T*> *pstate;

	std::tie(presult,pstate)=parser.runnew(state->source,state->start);
	if(!presult){
		return false;
	}
	end=pstate->end;
	while(true){
		auto [cresult,cstate]=cparser.runnew(state->source,end);
		if(!cresult){
			break;
		}
		end=cstate->end;
		std::tie(presult,pstate)=parser.runnew(state->source,end);
		if(!presult){
			break;
		}
		end=pstate->end;
		// parse comma
		// if not
		//   break
		// parse thing
		// if not
		//   break
	}
	state->end=end;
	return true;
}
