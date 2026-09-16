#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

int max_absolute_difference(const std::array<int, 3>& manual,
                            const std::array<int, 3>& reference) {
  // TODO: Return the largest absolute difference between matching values.
  static_cast<void>(manual);
  static_cast<void>(reference);
  return 0;
}

int main() {
  const std::array<int, 3> manual{77, 150, 29};
  const std::array<int, 3> reference{76, 150, 30};
  const int difference = max_absolute_difference(manual, reference);

  std::cout << "maximum difference = " << difference << "\n";
  assert(difference == 1);
}
