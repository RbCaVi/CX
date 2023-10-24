
#include "parser.h++"
#include <utility>
#include <tuple>
#include <variant>

//https://stackoverflow.com/a/53398815
template<typename ... input_t>
using variant_cat_t=
decltype(std::variant_cat(
    std::declval<input_t>()...
));

template<size_t idx,typename input_t>
using variant_get_t=
decltype(std::get<idx>(std::declval<input_t>()));

template<class... Ps>
using getT=std::variant<typename Ps::State*...>;

template<class... Ps>
using getV=std::variant<typename Ps::Value*...>;

template<size_t idx,class TupleP,class VariantT,class VariantV,class... Ps>
class VariantParserImpl;

template<size_t idx,class TupleP,class VariantT,class VariantV>
class VariantParserImpl<idx,TupleP,VariantT,VariantV>:public Parser<VariantT,VariantV>{
protected:
	TupleP *parsers;
	bool run(ParserState<VariantT> *state) override;
	VariantV *getValue(ParserState<VariantT> *state) override;
};

template<size_t idx,class TupleP,class VariantT,class VariantV,class P,class... Ps>
class VariantParserImpl<idx,TupleP,VariantT,VariantV,P,Ps...>:public VariantParserImpl<idx+1,TupleP,VariantT,VariantV,Ps...>{
protected:
	bool run(ParserState<VariantT> *state) override;
	VariantV *getValue(ParserState<VariantT> *state) override;
};

template<class... Ps>
class VariantParser:public VariantParserImpl<0,std::variant<Ps*...>,getT<Ps...>,getV<Ps...>,Ps...>{
	//typedef deinterleaveT<TVs...> T;
	//typedef deinterleaveV<TVs...> V;
	//typedef VariantParserImpl<0,deinterleaveT<TVs...>,deinterleaveV<TVs...>,getparsertuple<TVs...>,TVs...> TParser;
	typedef std::tuple<Ps*...> TupleP;
	typedef getT<Ps...> VariantT;
	typedef getV<Ps...> VariantV;
	typedef VariantParserImpl<0,std::variant<Ps*...>,getT<Ps...>,getV<Ps...>,Ps...> TParser;
public:
	VariantParser(Ps *...ps);
	bool run(ParserState<VariantT> *state) override;
	VariantV *getValue(ParserState<VariantT> *state) override;
};

template<class... Ps>
VariantParser<Ps...>::VariantParser(Ps *...ps){
	this->parsers=new TupleP(ps...);
}








template<class... Ps>
bool VariantParser<Ps...>::run(ParserState<VariantT> *state){
	state->value=new VariantT();
	state->end=state->start;
	return TParser::run(state);
}

template<class... Ps>
VariantParser<Ps...>::VariantV *VariantParser<Ps...>::getValue(ParserState<VariantT> *state){
	return TParser::getValue(state);
}







template<size_t idx,class TupleP,class VariantT,class VariantV>
bool VariantParserImpl<idx,TupleP,VariantT,VariantV>::run(ParserState<VariantT> *state){
	return true;
}

template<size_t idx,class TupleP,class VariantT,class VariantV>
VariantV *VariantParserImpl<idx,TupleP,VariantT,VariantV>::getValue(ParserState<VariantT> *state){
	return new VariantV();
}

template<size_t idx,class TupleP,class VariantT,class VariantV,class P,class... Ps>
bool VariantParserImpl<idx,TupleP,VariantT,VariantV,P,Ps...>::run(ParserState<VariantT> *state){
	auto [presult1,pstate1]=std::get<idx>(*(this->parsers))->runnew(state->source,state->end);
	if(!presult1){
		return false;
	}
	std::get<idx>(*(state->value))=pstate1;
	state->end=pstate1->end;
	bool presult2=VariantParserImpl<idx+1,TupleP,VariantT,VariantV,Ps...>::run(state);
	if(!presult2){
		return false;
	}
	return true;
}

template<size_t idx,class TupleP,class VariantT,class VariantV,class P,class... Ps>
VariantV *VariantParserImpl<idx,TupleP,VariantT,VariantV,P,Ps...>::getValue(ParserState<VariantT> *state){
	VariantV *out=VariantParserImpl<idx+1,TupleP,VariantT,VariantV,Ps...>::getValue(state);
	std::get<idx>(*out)=std::get<idx>(*(this->parsers))->getValue(std::get<idx>(*(state->value)));
	return out;
}