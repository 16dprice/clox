#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "value.h"

char* DEFAULT = "\033[0m";
char* RED = "\033[0;31m";
char* GREEN = "\033[0;32m";
char* YELLOW = "\033[0;33m";
char* BLUE = "\033[0;34m";
char* PURPLE = "\033[0;35m";
char* CYAN = "\033[0;36m";
char* WHITE = "\033[0;37m";

void resetConsoleColor() {
  printf("%s", DEFAULT);
}

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("%s================ %s ================\n", RED, name);
  resetConsoleColor();

  for(int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
  uint8_t constant = chunk->code[offset + 1];

  printf("%s%-16s %s%4d '", PURPLE, name, GREEN, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  resetConsoleColor();

  return offset + 2;
}

static int simpleInstruction(const char* name, int offset) {
  printf("%s%s\n", PURPLE, name);
  resetConsoleColor();

  return offset + 1;
}

int disassembleInstruction(Chunk* chunk, int offset) {
  printf("%s%04d%s ", CYAN, offset, DEFAULT);

  if(offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    printf("   | ");
  } else {
    printf("%4d ", chunk->lines[offset]);
  }

  uint8_t instruction = chunk->code[offset];
  switch(instruction) {
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}
