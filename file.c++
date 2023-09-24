#include "file.h++"

// A function that will read a file at a path into an allocated buffer
Buffer *pathtobuf(std::filesystem::path path) {
  FILE *fptr;
  long length;
  char *buf;

  fptr = fopen(path.string().c_str(), "rb");
  if (!fptr){
    return NULL;
  }
  fseek(fptr, 0, SEEK_END);
  length = ftell(fptr);
  buf = (char*)malloc(length);
  fseek(fptr, 0, SEEK_SET);
  fread(buf, length, 1, fptr);
  fclose(fptr);

  Buffer *out=new Buffer(buf,length);

  return out; // Return the buffer
}
