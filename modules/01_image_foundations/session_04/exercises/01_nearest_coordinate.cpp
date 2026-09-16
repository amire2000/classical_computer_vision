#include <cassert>
#include <cstddef>
#include <iostream>

std::size_t nearest_source_coordinate(std::size_t destination_coordinate,
                                      std::size_t source_size,
                                      std::size_t destination_size) {
  // TODO: Map the destination coordinate into the source image.
  static_cast<void>(destination_coordinate);
  static_cast<void>(source_size);
  static_cast<void>(destination_size);
  return 0;
}

int main() {
  const std::size_t source = nearest_source_coordinate(3, 2, 4);
  std::cout << "destination 3 reads source " << source << "\n";
  assert(source == 1);
}
