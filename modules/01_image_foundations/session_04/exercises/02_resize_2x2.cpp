#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

std::array<int, 16> resize_nearest(const std::array<int, 4>& source) {
  // TODO: Resize the 2 x 2 source to a 4 x 4 result with nearest neighbor.
  static_cast<void>(source);
  return {};
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
