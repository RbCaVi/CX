#include "buffer.h++"

#include <cstring>

Buffer::Buffer(const char *data):data(data),length(strlen(data)){}
Buffer::Buffer(const char *data,const size_t length):data(data),length(length){}

const char &Buffer::operator[](const size_t i){
	return data[i];
}

Buffer *Buffer::substr(const size_t start){
	return new Buffer(data,start,length);
}
Buffer *Buffer::substr(const size_t start,const size_t end){
	return new Buffer(data,start,end);
}

Buffer::Buffer(const char *data,const size_t start,const size_t end):data(data+start),length(end-start){}