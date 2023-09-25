#ifndef WHITESPACE_H
#define WHITESPACE_H

#include <cstddef>

#include "buffer.h++"

bool isWhitespace(const char c);

size_t skipWhitespace(Buffer *source,size_t start);
#endif