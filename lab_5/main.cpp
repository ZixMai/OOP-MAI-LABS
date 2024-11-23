#include <iostream>
#include "./src/LinkedList.h"
#include "./src/CustomMemoryResource.h"

int main() {
  CustomMemoryResource customResource;
  std::pmr::polymorphic_allocator<int> allocator(&customResource);
  LinkedList<int, std::pmr::polymorphic_allocator<int>> list(allocator);
  list.push_front(1);
  list.pop_front();
  std::cout << list.front() << std::endl;
}
