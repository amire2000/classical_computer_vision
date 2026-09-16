#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

int main() {
  constexpr std::size_t width = 2;
  constexpr std::size_t stride = 4;
  const std::array<int, 8> storage{
      10, 20, -1, -1,
      30, 40, -1, -1,
  };
  constexpr std::size_t row = 1;
  constexpr std::size_t column = 1;
  const std::size_t offset = row * stride + column;

  std::cout << "pixel(" << row << ", " << column << ") = "
            << storage[offset] << "\n";
  assert(width == 2);
  assert(offset == 5);
  assert(storage[offset] == 40);
}
