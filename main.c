#include "src/common.h"
#include "src/chunk.h"
#include "src/debug.h"
#include "src/vm.h"

int main(int argc, const char* argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_RETURN, 123);

  disassembleChunk(&chunk, "Test Chunk");

  freeVM();
  freeChunk(&chunk);

  return 0;
}
