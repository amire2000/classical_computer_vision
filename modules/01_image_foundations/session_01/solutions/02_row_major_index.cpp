#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

int main() {
  constexpr std::size_t width = 3;
  const std::vector<int> pixels{10, 11, 12, 20, 21, 22};
  constexpr std::size_t row = 1;
  constexpr std::size_t column = 2;
  const std::size_t index = row * width + column;

  std::cout << "pixel(" << row << ", " << column << ") = " << pixels[index]
            << "\n";
  assert(index == 5);
  assert(pixels[index] == 22);
}
