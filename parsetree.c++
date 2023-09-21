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
};

class ParseTreeNode;

class ParseNodeData{
	virtual void run(ParseTreeNode &parent)=0;
	virtual ~ParseNodeData()=0;
};

class ParseTreeNode{
public:
	ParseTreeNode *parent;
	std::list<ParseTreeNode*> *children;
	ParseNodeType type;

	ParseTreeNode(ParseTreeNode *parent,ParseNodeType type):parent(parent),children(new std::list<ParseTreeNode*>()),type(type),data(NULL){}
	~ParseTreeNode(){
		for(auto child:*children){
			delete child;
		}
		delete children;
	}
};

class ExprData:public ParseNodeData{
	
}