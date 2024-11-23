#include <iostream>
#include "./src/LinkedList.h"
#include "./src/CustomMemoryResource.h"

int main() {
  CustomMemoryResource customResource;
  std::pmr::polymorphic_allocator<int> allocator(&customResource);
}
