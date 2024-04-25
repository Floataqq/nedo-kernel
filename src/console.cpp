#ifndef KERNEL_CONSOLE
#define KERNEL_CONSOLE

#include <cstdint>
namespace VGA {
enum Color {
  Black = 0,
  Blue = 1,
  Green = 2,
  Cyan = 3,
  Red = 4,
  Magenta = 5,
  Brown = 6,
  LightGray = 7,
  DarkGray = 8,
  LightBlue = 9,
  LightGreen = 10,
  LightCyan = 11,
  LightRed = 12,
  Pink = 13,
  Yellow = 14,
  White = 15,
};

struct VGAChar {
  char chr;
  Color fore, back;

  VGAChar(char c, Color fore, Color back) {
    this->chr = c;
    this->fore = fore;
    this->back = back;
  }

  VGAChar(char c) : VGAChar(c, White, Black) {}

  uint16_t value() { return (fore << 8) | (back << 12) | chr; }
};

const uint16_t SCREEN_WIDTH = 80, SCREEN_HEIGHT = 25;

struct Writer {
  volatile uint16_t *buf;
  Color fore, back;
  uint16_t cursor;

  Writer(volatile uint16_t *buf, Color fore, Color back) {
    this->cursor = 0;
    this->buf = buf;
    this->fore = fore;
    this->back = back;
  }

  Writer(Color fore, Color back)
      : Writer((volatile uint16_t *)0xb8000, fore, back) {}

  Writer() : Writer(White, Black) {}

  void put_vga_char(VGAChar c) {
    switch (c.chr) {
    case '\n':
      while (cursor % SCREEN_WIDTH) {
        buf[cursor] = VGAChar(' ', c.fore, c.back).value();
        cursor += 1;
        cursor %= SCREEN_WIDTH * SCREEN_HEIGHT;
      }
      break;
    default:
      buf[cursor] = c.value();
      cursor += 1;
      cursor %= SCREEN_WIDTH * SCREEN_HEIGHT;
    }
  }

  inline void put_char(char c) {
    this->put_vga_char(VGAChar(c, this->fore, this->back));
  }

  void put_vga_string(VGAChar *c, uint32_t length) {
    for (uint32_t i = 0; i < length; i++)
      this->put_vga_char(c[i]);
  }

  void puts(char *c, uint32_t length) {
    for (uint32_t i = 0; i < length; i++)
      this->put_char(c[i]);
  };
};
} // namespace VGA

#else
#endif
