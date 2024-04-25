#include "IDT.cpp"
#include "globals.cpp"

namespace Instructions {
inline void lidt(IDT::IDTR idtr) { __asm__ volatile("lidt %0" : : "m"(idtr)); }

inline void sti() { __asm__ volatile("sti"); }
inline void cli() { __asm__ volatile("cli"); }

} // namespace Instructions
