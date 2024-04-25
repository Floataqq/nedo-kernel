#include "IDT.cpp"
#include "console.cpp"
#include "globals.cpp"

extern "C" void kernel_main() { __asm__("int $0"); }
