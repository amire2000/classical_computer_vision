#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

int max_absolute_difference(const std::array<int, 3>& manual,
                            const std::array<int, 3>& reference) {
  int maximum = 0;
  for (std::size_t index = 0; index < manual.size(); ++index) {
    const int difference = manual[index] - reference[index];
    const int absolute_difference = difference < 0 ? -difference : difference;
    maximum = std::max(maximum, absolute_difference);
  }
  return maximum;
}

int main() {
  const std::array<int, 3> manual{77, 150, 29};
  const std::array<int, 3> reference{76, 150, 30};
  const int difference = max_absolute_difference(manual, reference);

  std::cout << "maximum difference = " << difference << "\n";
  assert(difference == 1);
}
