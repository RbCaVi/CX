#include <stack>
#include <stdlib.h>
#include <string>

class Buffer{
public:
	char *data;
	int length;
	Buffer(char *data,int length):data(data),length(length){}

	char operator[](int i){
		return data[i];
	}

	Buffer *substr(int start){
		return new Buffer(data,start,length);
	}
	Buffer *substr(int start,int end){
		return new Buffer(data,start,end);
	}

private:
	Buffer(char *data,int start,int end):data(data+start),length(end-start){}
};

template<class Out>
class Parser{
public:
	Buffer &source;
	Out *output;
	int end;

	Parser(Buffer &source):source(source){}

	virtual bool parse(int offset,bool backtrack) = 0;
};



template<class Out>
class AnyParser:public Parser<Out>{
private:
	Parser<Out> **parsers;
	int numParsers;

	int matchedIndex=-1;

	void addParsers(){}
	template<class... Outs> requires std::is_same_v<Out,Outs...> // i don't know if this is the right way
	void addParsers(int pos,Parser<Out> *p,Parser<Outs> *...ps){
		parsers[pos]=p;
		addParsers(pos+1,ps...);
	}

	void initParsers(int size){
		parsers=(Parser<Out>**)malloc(sizeof(Parser<Out>*)*size);
		numParsers=size;
	}

public:
	template<class... Outs> requires std::is_same_v<Out,Outs...>
	AnyParser(Buffer &source,Parser<Outs> *...parsers):Parser<Out>(source){
		initParsers(sizeof...(parsers));
		addParsers(0,parsers...);
	}

	virtual bool parse(int offset,bool backtrack){
		int i=0;
		if(backtrack){
			i=matchedIndex;
		}
		while(i<numParsers){
			if(parsers[i]->parse(offset,backtrack)){
				this->output=parsers[i]->output;
				matchedIndex=i;
				return true;
			}
			i++;
		}
		return false;
	}
};

class StringParser:public Parser<std::string>{
private:
	std::string &pattern;

public:
	StringParser(Buffer &source,std::string &pattern):Parser<std::string>(source),pattern(pattern){}

	virtual bool parse(int offset,bool backtrack){
		if(backtrack){
			return false;
		}
		unsigned int i;
		for(i=0;i<pattern.length();i++){
			if(pattern[i]!=source[i]){
				return false;
			}
		}
		return true;
	}
};

class AnyStringParser:public Parser<std::string>{
private:
	std::string **patterns;
	int numPatterns;

	int matchedIndex=-1;

	void addPatterns(){}
	template<class... Strs> requires std::is_same_v<std::string,Strs...> // i don't know if this is the right way
	void addPatterns(int pos,std::string &p,Strs *...ps){
		patterns[pos]=p;
		addPatterns(pos+1,ps...);
	}

	void initPatterns(int size){
		patterns=(std::string**)malloc(sizeof(std::string*)*size);
		numPatterns=size;
	}

public:
	template<class... Strs> requires std::is_same_v<std::string,Strs...> // i don't know if this is the right way
	AnyStringParser(Buffer &source,Strs &...patterns):Parser<std::string>(source){
		initPatterns(sizeof...(patterns));
		addPatterns(0,patterns...);
	}

	virtual bool parse(int offset,bool backtrack){
		int i=0;
		unsigned int j;
		if(backtrack){
			i=matchedIndex;
		}
		while(i<numPatterns){
			bool matched;
			matched=true;
			std::string pattern=(*patterns)[i];
			for(j=0;j<pattern.length();j++){
				if(pattern[j]!=source[j]){
					matched=false;
					break;
				}
			}
			if(matched){
				this->output=patterns[i];
				matchedIndex=i;
				return true;
			}
			i++;
		}
		return false;
	}
};

template<class... Outs>
class ConcatParser:public Parser<void**>{
private:
	Parser<void> **parsers;
	int numParsers;

	void addParsers(){}
	template<class... Outs2>
	void addParsers(int pos,Parser<void> *p,Parser<Outs2> *...ps){
		parsers[pos]=p;
		addParsers(pos+1,ps...);
	}

	void initParsers(int size){
		parsers=(Parser<void>**)malloc(sizeof(Parser<void>*)*size);
		numParsers=size;
	}

public:
	ConcatParser(Buffer &source,Parser<Outs> *...parsers):Parser(source){
		initParsers(sizeof...(parsers));
		addParsers(0,parsers...);
	}

	virtual bool parse(int offset,bool backwards){
		int i;
		int end;
		if(backwards){
			i=numParsers-1;
			end=parsers[i]->end;
		}else{
			i=0;
			end=offset;
		}
    while(true){
    	if(parsers[i]->parse(end,backwards)){
    		end=parsers[i]->end;
    		(*output)[i]=parsers[i]->output;
    		i++;
    		if(i>=numParsers){
    			this.end=end;
    			return true;
    		}
    	}else{
    		if(i<0){
    			return false;
    		}
    		i--;
    		if(i<0){
    			this.end=offset;
    		}else{
  				this.end=parsers[i]->end;
    		}
    	}
    }
	}
};

class ParserBuilder{
	
}