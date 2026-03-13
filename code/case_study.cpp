#include <cassert>
#include <exception>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

void may_throw(const std::vector<int> &v) {
  if (v.size() > 8)
    throw std::runtime_error("Hello, world!");
}

void do_something_that_needs_cleanups(int M) {
  // values are '{ 0, 1, ..., M-1 }'
  auto v = std::views::iota(0, M) | std::ranges::to<std::vector>();
  may_throw(v);
}

void catches_and_rethrows(int M) {
  try {
    std::string needs_cleanup{"str"};
    do_something_that_needs_cleanups(M);

  } catch (...) {
    std::cerr << "Catch all; rethrown\n";
    throw;
  }
}

int main(int argc, char *argv[]) try {
  assert(argc == 2);
  std::vector<unsigned char> vc{0x55, 0xaa, 0x55, 0xaa};
  catches_and_rethrows(atoi(argv[1]));
  return 0;

} catch (const std::runtime_error &e) {
  std::cerr << "main: Caught std::runtime_error!\n";
  return -1;
}
