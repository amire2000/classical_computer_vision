#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

int bgr_to_gray(int blue, int green, int red) {
  return (77 * red + 150 * green + 29 * blue + 128) / 256;
}

int main() {
  constexpr std::size_t channels = 3;
  const std::array<int, 6> bgr{0, 0, 255, 255, 255, 255};
  std::array<int, 2> gray{};

  for (std::size_t pixel = 0; pixel < gray.size(); ++pixel) {
    const std::size_t first_channel = pixel * channels;
    gray[pixel] = bgr_to_gray(bgr[first_channel], bgr[first_channel + 1],
                               bgr[first_channel + 2]);
  }

  std::cout << "gray row = " << gray[0] << ", " << gray[1] << "\n";
  assert(gray[0] == 77);
  assert(gray[1] == 255);
}
