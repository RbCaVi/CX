#include <list>
#include <cstddef>

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

class ParseNodeData{
public:
	virtual ~ParseNodeData(){}
};

class ParseTreeNode{
public:
	ParseTreeNode *parent=NULL;
	std::list<ParseTreeNode*> *children;
	ParseNodeType type;
	ParseNodeData *data;

	ParseTreeNode(ParseNodeType type,ParseNodeData *data):children(new std::list<ParseTreeNode*>()),type(type),data(data){}
	
	void addChild(ParseTreeNode *child){
		children->push_back(child);
	}

	~ParseTreeNode(){
		for(auto child:*children){
			delete child;
		}
		delete children;
	}
};

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
	n->run(*s);
	LinesIterator *x=new LinesIterator();
	for(auto i:*x){}
	x->getLine();
	return 0;
}