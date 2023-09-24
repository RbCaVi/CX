#include <iterator>
#include <cstdio>
#include <cstring>

class Buffer{
public:
	const char *data;
	const size_t length;
	Buffer(const char *data):data(data),length(strlen(data)){}
	Buffer(const char *data,const size_t length):data(data),length(length){}

	const char &operator[](const size_t i){
		return data[i];
	}

	Buffer *substr(const size_t start){
		return new Buffer(data,start,length);
	}
	Buffer *substr(const size_t start,const size_t end){
		return new Buffer(data,start,end);
	}

private:
	Buffer(const char *data,const size_t start,const size_t end):data(data+start),length(end-start){}
};

/*template<class T>
class NextIterator{
public:
	class iterator{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
		NextIterator *source;
		T *content;
	public:
		explicit iterator(NextIterator<T> *source):source(source),content(source->getLine()){}
		explicit iterator(NextIterator<T> *source,std::string *content):source(source),content(content){}

		iterator& operator++(){
			content=source->getLine();
			return *this;
		}

		iterator operator++(int){
			iterator retval = *this;
			++(*this);
			return retval;
		}

		bool operator==(iterator other) const {
			return content == other.content;
		}

		bool operator!=(iterator other) const {
			return !(*this == other);
		}

		reference operator*() const {
			return *content;
		}
	};

	iterator begin(){
		return iterator(this);
	}

	iterator end(){
		return iterator(this,NULL);
	}

	virtual T *next()=0;
};*/

class ParserNode{
public:
	size_t start,end;
	Buffer *source;

	ParserNode(Buffer *source):source(source){}

	virtual bool run(size_t start)=0;
	virtual bool backtrack()=0;

//	virtual NextIterator<std::string> *getLines()=0;
};

bool isWhitespace(const char c){
	return c==' '||c=='\n'||c=='\t'||c=='\f'||c=='\v';
}

size_t skipWhitespace(Buffer *source,size_t start){
	size_t i=start;
	while(isWhitespace((*source)[i])&&i<source->length){
		i++;
	}
	return i;
}

class IntParser:public ParserNode{
	bool isNum(const char c,unsigned int base){
		if(base>10){
			return (c>='a'&&c-'a'<base-10)||(c>='a'&&c-'A'<base-10)||(c>='0'&&c<'9');
		}
		return c>='0'&&c<('0'+base);
	}

	int toNum(const char c,unsigned int base){
		if(base>10&&((c>='a'&&c-'a'<base-10)||(c>='A'&&c-'A'<base-10))){
			if(c>='a'&&c-'a'<base-10){
				return 10+c-'a';
			}else{
				return 10+c-'A';
			}
			return true;
		}
		return c-'0';
	}

public:
	unsigned long long value;

	IntParser(Buffer *source):ParserNode(source){}

	virtual bool run(size_t start){
		this->start=start;
		value=0;
		size_t i;
		unsigned int base=10;
		bool firstdigit;
		for(i=skipWhitespace(source,start);isNum((*source)[i],base)&&i<source->length;i++){
			value*=base;
			int toAdd=toNum((*source)[i],base);
			if(toAdd==0&&firstdigit){
				// octal/hex literals?
				i++;
				if((*source)[i]=='x'||(*source)[i]=='X'){
					base=16;
				}else if((*source)[i]=='b'||(*source)[i]=='B'){
					base=2;
				}else if((*source)[i]=='o'||(*source)[i]=='O'){
					base=8;
				}
			}
			value+=toAdd;
			firstdigit=false;
		}
		if(i==start){
			return false;
		}
		end=this->start+i;
		return true;
	}

	virtual bool backtrack(){
		return false;
	};
};

int main(int,char**){
	Buffer *s=new Buffer("  0x456abc");
	printf("%i\n",skipWhitespace(s,0));
	IntParser *p=new IntParser(s);
	bool r=p->run(0);
	printf("%i %i %i %i\n",r,p->start,p->end,p->value);
}