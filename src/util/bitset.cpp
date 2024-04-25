#include <cstdint>
template <typename T> class [[gnu::packed]] BitSet {
public:
  T value;
  BitSet<T>() {}
  BitSet<T>(T value) { this->value = value; }
  inline constexpr void set(uint32_t index) { //
    this->value |= (T)1 << index;
  }
  inline constexpr void clear(uint32_t index) {
    this->value &= ~((T)1 << index);
  }
  inline constexpr void toggle(uint32_t index) {
    this->value ^= ((T)1 << index);
  }
  inline constexpr bool check(uint32_t index) {
    return (this->value >> index) & (T)1;
  }
  inline constexpr void set_to(uint32_t index, bool to) {
    this->value = (this->value & ~((T)1 << index)) | ((T)to << index);
  }
};
