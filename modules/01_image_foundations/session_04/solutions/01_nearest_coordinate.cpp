#include <cassert>
#include <cstddef>
#include <iostream>

std::size_t nearest_source_coordinate(std::size_t destination_coordinate,
                                      std::size_t source_size,
                                      std::size_t destination_size) {
  return destination_coordinate * source_size / destination_size;
}

int main() {
  const std::size_t source = nearest_source_coordinate(3, 2, 4);
  std::cout << "destination 3 reads source " << source << "\n";
  assert(source == 1);
}
