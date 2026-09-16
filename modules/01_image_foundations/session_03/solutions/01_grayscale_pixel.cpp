#include <cassert>
#include <iostream>

int bgr_to_gray(int blue, int green, int red) {
  return (77 * red + 150 * green + 29 * blue + 128) / 256;
}

int main() {
  const int gray = bgr_to_gray(0, 0, 255);
  std::cout << "gray value = " << gray << "\n";
  assert(gray == 77);
}
