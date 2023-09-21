#include <vector>
#include <cstddef>
#include <string>
#include <iterator>
#include <iostream>

class Buffer{
public:
	const char *data;
	const int length;
	Buffer(const char *data,const int length):data(data),length(length){}

	const char &operator[](const int i){
		return data[i];
	}

	Buffer *substr(const int start){
		return new Buffer(data,start,length);
	}
	Buffer *substr(const int start,const int end){
		return new Buffer(data,start,end);
	}

private:
	Buffer(const char *data,const int start,const int end):data(data+start),length(end-start){}
};

enum ParseNodeType{
	INT,
};

class ParseTreeNode;

class ParserNode{
public:
	virtual ParseTreeNode *run(Buffer &s)=0;
	virtual ~ParserNode(){}
};

class LinesIterator{
public:
	class iterator{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = std::string;
    using pointer           = value_type*;  // or also 
    using reference         = value_type&;  // or also value_type&
		LinesIterator *source;
		std::string *content;
	public:
		explicit iterator(LinesIterator *source):source(source),content(source->getLine()){}
		explicit iterator(LinesIterator *source,std::string *content):source(source),content(content){}

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

	virtual std::string *getLine()=0;
};

class ParseNodeDataLinesIterator;

class ParseNodeData{
public:
	virtual ParseNodeDataLinesIterator *getLines();

	virtual ~ParseNodeData(){}
};

class ParseNodeDataLinesIterator:public LinesIterator{
public:
	ParseNodeData *data;
	ParseNodeDataLinesIterator(ParseNodeData *data):data(data){}
};

class ParseNodeDataLinesDefaultIterator:public ParseNodeDataLinesIterator{
public:
	ParseNodeData *data;
	bool used=false;
	ParseNodeDataLinesDefaultIterator(ParseNodeData *data):ParseNodeDataLinesIterator(data){}
	std::string *getLine(){
		if(used){
			return NULL;
		}
		used=true;
		return new std::string("Node");
	}
};

ParseNodeDataLinesIterator *ParseNodeData::getLines(){
	return new ParseNodeDataLinesDefaultIterator(this);
}

template<class T>
void begin(T* x){
	**x;
}

template<class T>
void end(T* x){
	**x;
}

class ParseTreeNode;

class ParseNodeLinesIterator:public LinesIterator{
	ParseTreeNode *node;
	LinesIterator *current;
	int index=-1;
public:
	ParseNodeLinesIterator(ParseTreeNode *node);

	std::string *getLine();
};

class ParseTreeNode{
public:
	ParseTreeNode *parent=NULL;
	std::vector<ParseTreeNode*> *children;
	ParseNodeType type;
	ParseNodeData *data;

	ParseTreeNode(ParseNodeType type,ParseNodeData *data):children(new std::vector<ParseTreeNode*>()),type(type),data(data){}
	
	void addChild(ParseTreeNode *child){
		children->push_back(child);
	}

	ParseNodeLinesIterator *getLines(){
		return new ParseNodeLinesIterator(this);
	}

	~ParseTreeNode(){
		for(auto child:*children){
			delete child;
		}
		delete children;
	}
};

ParseNodeLinesIterator::ParseNodeLinesIterator(ParseTreeNode *node):node(node),current(node->data->getLines()){}

std::string *ParseNodeLinesIterator::getLine(){
	std::string *value=current->getLine();
	while(value==NULL){
		index++;
		if(index>=node->children->size()){
			return NULL;
		}
		current=(*(node->children))[index]->getLines();
		std::string *value=current->getLine();
	}
	return value;
}

class IntData:public ParseNodeData{
public:
	int value;

	IntData(int v):value(v){}
};

bool isNum(const char c){
	return c>='0'&&c<='9';
}

int toNum(const char c){
	return c-'0';
}

class IntNode:public ParserNode{
public:
	ParseTreeNode *run(Buffer &s){
		int n=0;
		int i;
		for(i=0;isNum(s[i])&&i<s.length;i++){
			n*=10;
			n+=toNum(s[i]);
		}
		s.substr(i);
		return new ParseTreeNode(ParseNodeType::INT,new IntData(n));
	}
};

int main(int argc, char const *argv[])
{
	Buffer *s=new Buffer("456",3);
	ParserNode *n=new IntNode();
	ParseTreeNode *t=n->run(*s);
	LinesIterator *x=t->getLines();
	for(std::string &i:*x){
		std::cout << "'" << i << "'" << std::endl;
	}
	return 0;
}