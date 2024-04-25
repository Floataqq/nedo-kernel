global g_idt
global g_idtr

section .text
bits 64

section .bss
g_idt:                              ; global idt space
  resb 4096
g_idtr:                             ; global ist descriptor space
  resb 10 


