#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <span>

struct ImageView {
  std::span<const int> storage;
  std::size_t width;
  std::size_t channels;
  std::size_t stride;

  [[nodiscard]] int at(std::size_t row, std::size_t column,
                       std::size_t channel) const {
    return storage[row * stride + column * channels + channel];
  }
};

int main() {
  const std::array<int, 12> bgr_pixels{
      1, 2, 3, 4, 5, 6,
      7, 8, 9, 10, 11, 12,
  };
  const ImageView image{bgr_pixels, 2, 3, 6};

  std::cout << "BGR at (1, 0) = " << image.at(1, 0, 0) << ", "
            << image.at(1, 0, 1) << ", " << image.at(1, 0, 2) << "\n";
  assert(image.at(1, 0, 0) == 7);
  assert(image.at(1, 0, 1) == 8);
  assert(image.at(1, 0, 2) == 9);
}
