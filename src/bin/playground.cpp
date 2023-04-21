#include <iostream>

#include "types.hpp"
#include "utils/assert.hpp"

using namespace opossum;  // NOLINT(build/namespaces)

int main() {
  Assert(true, "We can use opossum files here :)");
  std::cout << "Hello World" << std::endl;

  return 0;
}
