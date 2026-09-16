#include <cassert>
#include <cstddef>
#include <iostream>

int main() {
  constexpr std::size_t height = 2;
  constexpr std::size_t width = 3;
  const std::size_t pixel_count = height * width;

  std::cout << height << " rows x " << width << " columns = " << pixel_count
            << " pixels\n";
  assert(pixel_count == height * width);
}
