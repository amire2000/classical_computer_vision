#include <cassert>
#include <cstddef>
#include <iostream>

int main() {
  constexpr std::size_t height = 2;
  constexpr std::size_t width = 3;

  // TODO: Replace 0 with the number of grayscale pixels in the image.
  const std::size_t pixel_count = 0;

  std::cout << height << " rows x " << width << " columns = " << pixel_count
            << " pixels\n";
  assert(pixel_count == height * width);
}
