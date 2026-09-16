#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

int main() {
  constexpr std::size_t width = 3;
  constexpr std::size_t stride = 5;  // Elements between row starts.
  const std::array<int, 10> storage{
      10, 11, 12, -1, -1,
      20, 21, 22, -1, -1,
  };
  constexpr std::size_t row = 1;
  constexpr std::size_t column = 2;
  const std::size_t offset = row * stride + column;

  std::cout << "width " << width << ", stride " << stride << ": pixel("
            << row << ", " << column << ") = " << storage[offset] << "\n";
  assert(offset == 7);
  assert(storage[offset] == 22);
}
