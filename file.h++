#ifndef FILE_H
#define FILE_H

#include <filesystem>

#include "buffer.h++"

Buffer *pathtobuf(std::filesystem::path path);
#endif