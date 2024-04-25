#ifndef KERNEL_IDT
#define KERNEL_IDT

#include "util/bitset.cpp"
#include <cstdint>
#include <sys/cdefs.h>

namespace IDT {

const uint8_t INTERRUPT_GATE = 0x8e;
const uint8_t TRAP_GATE = 0x8f;

struct [[gnu::packed]] Entry {
public:
  uint16_t pointer_1;
  uint16_t gdt_selector;
  uint8_t ist;
  BitSet<uint8_t> type_attrs;
  uint16_t pointer_2;
  uint32_t pointer_3;
  uint32_t _reserved;

  static Entry missing() {
    Entry e;
    e.pointer_1 = 0;
    e.gdt_selector = 0;
    e.ist = 0;
    e.type_attrs = BitSet<uint8_t>(0b00001110);
    e.pointer_2 = 0;
    e.pointer_3 = 0;
    e._reserved = 0;
    return e;
  }

  Entry() {
    this->pointer_1 = 0;
    this->gdt_selector = 0;
    this->ist = 0;
    this->type_attrs = BitSet<uint8_t>(0b1'00'0'111'0);
    this->pointer_2 = 0;
    this->pointer_3 = 0;
  }

  Entry(uint16_t gdt_selector, void *pointer) {
    uint64_t p = (uint64_t)pointer;
    this->pointer_1 = (uint16_t)p;
    this->gdt_selector = gdt_selector;
    this->pointer_2 = uint16_t(p >> 16);
    this->pointer_3 = uint32_t(p >> 32);
    this->ist = 0;
    this->type_attrs = BitSet<uint8_t>(0b1'00'0'111'0);
  }

  inline void set_present(bool to) { this->type_attrs.set_to(7, to); }
  inline void set_interrupts(bool to) { this->type_attrs.set_to(0, to); }
  inline void set_privelege_level(uint8_t to) {
    this->type_attrs.set_to(5, to & 0b01);
    this->type_attrs.set_to(6, to & 0b10);
  }
  inline void set_stack_index(uint8_t to) { this->ist = to & 0b11; }
};

static_assert(sizeof(Entry) == 16, "IDT Entry size is not 16 bytes!");

struct IDTR {
  uint16_t size;
  uint64_t offset;
} __attribute__((packed));

} // namespace IDT

#else
#endif
