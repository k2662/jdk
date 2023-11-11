#include "gc/shared/genCollectedHeap.hpp"
#include "gc/serial/serialHeap.hpp"

inline Generation* GenCollectedHeap::young_gen() {
  return SerialHeap::heap()->young_gen();
}