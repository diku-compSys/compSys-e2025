
#include <stddef.h>
#include <stdint.h>

// NOTE: Use of symbols provide for nicer disassembly, but is not required for A4.
// Feel free to remove this parameter or pass in a NULL pointer and ignore it.

struct symbols;
void disassemble(uint32_t addr, uint32_t instruction, char* result, size_t buf_size, struct symbols* symbols);
