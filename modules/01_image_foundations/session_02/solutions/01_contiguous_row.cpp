#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <span>

int main() {
  constexpr std::size_t width = 3;
  const std::array<int, 6> storage{10, 11, 12, 20, 21, 22};
  const std::span<const int> pixels{storage};
  const std::span<const int> row = pixels.subspan(width, width);

  std::cout << "row starts with " << row[0] << " and ends with " << row[2]
            << "\n";
  assert(row[0] == 20);
  assert(row[2] == 22);
}
