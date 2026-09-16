#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

std::array<int, 16> resize_nearest(const std::array<int, 4>& source) {
  constexpr std::size_t source_width = 2;
  constexpr std::size_t destination_width = 4;
  std::array<int, 16> destination{};

  for (std::size_t row = 0; row < destination_width; ++row) {
    for (std::size_t column = 0; column < destination_width; ++column) {
      const std::size_t source_row = row * source_width / destination_width;
      const std::size_t source_column =
          column * source_width / destination_width;
      destination[row * destination_width + column] =
          source[source_row * source_width + source_column];
    }
  }
  return destination;
}

int main() {
  const std::array<int, 4> source{10, 20, 30, 40};
  const std::array<int, 16> resized = resize_nearest(source);

  std::cout << "corners = " << resized[0] << ", " << resized[3] << ", "
            << resized[12] << ", " << resized[15] << "\n";
  assert(resized[0] == 10);
  assert(resized[3] == 20);
  assert(resized[12] == 30);
  assert(resized[15] == 40);
}
