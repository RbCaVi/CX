
#include "parser.h++"
#include <utility>
#include <tuple>

template<class... Ps>
using getT=std::tuple<typename Ps::State*...>;

template<class... Ps>
using getV=std::tuple<typename Ps::Value...>;

template<size_t idx,class TupleP,class TupleT,class TupleV,class... Ps>
class TupleParserImpl;

template<size_t idx,class TupleP,class TupleT,class TupleV>
class TupleParserImpl<idx,TupleP,TupleT,TupleV>:public Parser<TupleT,TupleV>{
protected:
	TupleP *parsers;
	bool run(ParserState<TupleT> &state) override;
	TupleV getValue(ParserState<TupleT> &state) override;
};

template<size_t idx,class TupleP,class TupleT,class TupleV,class P,class... Ps>
class TupleParserImpl<idx,TupleP,TupleT,TupleV,P,Ps...>:public TupleParserImpl<idx+1,TupleP,TupleT,TupleV,Ps...>{
protected:
	bool run(ParserState<TupleT> &state) override;
	TupleV getValue(ParserState<TupleT> &state) override;
};

template<class... Ps>
class TupleParser:public TupleParserImpl<0,std::tuple<Ps*...>,getT<Ps...>,getV<Ps...>,Ps...>{
	//typedef deinterleaveT<TVs...> T;
	//typedef deinterleaveV<TVs...> V;
	//typedef TupleParserImpl<0,deinterleaveT<TVs...>,deinterleaveV<TVs...>,getparsertuple<TVs...>,TVs...> TParser;
	typedef std::tuple<Ps*...> TupleP;
	typedef getT<Ps...> TupleT;
	typedef getV<Ps...> TupleV;
	typedef TupleParserImpl<0,std::tuple<Ps*...>,getT<Ps...>,getV<Ps...>,Ps...> TParser;
public:
	TupleParser(Ps *...ps);
	bool run(ParserState<TupleT> &state) override;
	TupleV getValue(ParserState<TupleT> &state) override;
};

template<class... Ps>
TupleParser<Ps...>::TupleParser(Ps *...ps){
	this->parsers=new TupleP(ps...);
}








template<class... Ps>
bool TupleParser<Ps...>::run(ParserState<TupleT> &state){
	state.value=new TupleT();
	state.end=state.start;
	return TParser::run(state);
}

template<class... Ps>
TupleParser<Ps...>::TupleV TupleParser<Ps...>::getValue(ParserState<TupleT> &state){
	return TParser::getValue(state);
}







template<size_t idx,class TupleP,class TupleT,class TupleV>
bool TupleParserImpl<idx,TupleP,TupleT,TupleV>::run(ParserState<TupleT> &state){
	return true;
}

template<size_t idx,class TupleP,class TupleT,class TupleV>
TupleV TupleParserImpl<idx,TupleP,TupleT,TupleV>::getValue(ParserState<TupleT> &state){
	return {};
}

template<size_t idx,class TupleP,class TupleT,class TupleV,class P,class... Ps>
bool TupleParserImpl<idx,TupleP,TupleT,TupleV,P,Ps...>::run(ParserState<TupleT> &state){
	auto [presult1,pstate1]=std::get<idx>(*(this->parsers))->runnew(state.source,state.end);
	if(!presult1){
		return false;
	}
	std::get<idx>(*(state.value))=&pstate1;
	state.end=pstate1.end;
	bool presult2=TupleParserImpl<idx+1,TupleP,TupleT,TupleV,Ps...>::run(state);
	if(!presult2){
		return false;
	}
	return true;
}

template<size_t idx,class TupleP,class TupleT,class TupleV,class P,class... Ps>
TupleV TupleParserImpl<idx,TupleP,TupleT,TupleV,P,Ps...>::getValue(ParserState<TupleT> &state){
	TupleV out=TupleParserImpl<idx+1,TupleP,TupleT,TupleV,Ps...>::getValue(state);
	std::get<idx>(out)=std::get<idx>(*(this->parsers))->getValue(*std::get<idx>(*(state.value)));
	return out;
}