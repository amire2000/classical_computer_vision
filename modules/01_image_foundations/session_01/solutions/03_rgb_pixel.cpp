#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

int main() {
  constexpr std::size_t width = 2;
  constexpr std::size_t channels = 3;
  const std::array<int, 12> image{
      1, 2, 3, 4, 5, 6,
      7, 8, 9, 10, 11, 12,
  };
  constexpr std::size_t row = 1;
  constexpr std::size_t column = 0;
  const std::size_t first_channel = (row * width + column) * channels;
  const int channel_sum = image[first_channel] + image[first_channel + 1] +
                          image[first_channel + 2];

  std::cout << "RGB channel sum = " << channel_sum << "\n";
  assert(first_channel == 6);
  assert(channel_sum == 24);
}
