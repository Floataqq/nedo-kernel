#ifndef KERNEL_GLOBALS
#define KERNEL_GLOBALS

#include "IDT.cpp"

extern "C" IDT::IDTR g_idtr;
extern "C" IDT::Entry g_idt[256];

#else
#endif
