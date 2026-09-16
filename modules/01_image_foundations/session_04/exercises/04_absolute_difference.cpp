#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

std::array<int, 4> absolute_difference(const std::array<int, 4>& left,
                                       const std::array<int, 4>& right) {
  // TODO: Return the absolute difference of each matching pixel.
  static_cast<void>(left);
  static_cast<void>(right);
  return {};
}

int main() {
  const std::array<int, 4> manual{10, 20, 30, 40};
  const std::array<int, 4> reference{9, 20, 31, 40};
  const std::array<int, 4> difference = absolute_difference(manual, reference);

  std::cout << "difference = " << difference[0] << ", " << difference[1]
            << ", " << difference[2] << ", " << difference[3] << "\n";
  assert(difference[0] == 1);
  assert(difference[1] == 0);
  assert(difference[2] == 1);
  assert(difference[3] == 0);
}
