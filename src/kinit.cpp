#ifndef KERNEL_KINIT
#define KERNEL_KINIT

#include "IDT.cpp"
#include "console.cpp"
#include "globals.cpp"
#include "instructions.cpp"

char interrupt[20] = "Interrupt detected!";

extern "C" [[noreturn]] void int_handler(void) {
  VGA::Writer().puts(interrupt, 19);
  while (true) {
  }
}

inline void load_global_idt() {
  g_idtr.size = 4095;
  g_idtr.offset = (uint64_t)&g_idt;
  Instructions::lidt(g_idtr);
}

extern "C" void kinit() {
  // load Interrupt Descriptor Table
  g_idt[0] = IDT::Entry(8, (void *)int_handler);
  // add custom idt entries here
  load_global_idt();
  Instructions::sti();
}

#else
#endif
