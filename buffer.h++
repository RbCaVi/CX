#ifndef BUFFER_H
#define BUFFER_H
#include <cstddef>

class Buffer{
public:
	const char *data;
	const size_t length;
	Buffer(const char *data);
	Buffer(const char *data,const size_t length);

	const char &operator[](const size_t i);
	Buffer *substr(const size_t start);
	Buffer *substr(const size_t start,const size_t end);

private:
	Buffer(const char *data,const size_t start,const size_t end);
};
#endif