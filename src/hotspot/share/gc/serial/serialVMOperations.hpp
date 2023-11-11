#ifndef SHARE_GC_SERIAL_SERIALVMOPERATIONS_HPP
#define SHARE_GC_SERIAL_SERIALVMOPERATIONS_HPP

#include "gc/shared/gcVMOperations.hpp"
#include "gc/serial/serialHeap.hpp"

class VM_GenCollectForAllocation : public VM_CollectForAllocation {
 private:
  bool        _tlab;                       // alloc is of a tlab.
 public:
  VM_GenCollectForAllocation(size_t word_size,
                             bool tlab,
                             uint gc_count_before)
    : VM_CollectForAllocation(word_size, gc_count_before, GCCause::_allocation_failure),
      _tlab(tlab) {
    assert(word_size != 0, "An allocation should always be requested with this operation.");
  }
  ~VM_GenCollectForAllocation()  {}
  virtual VMOp_Type type() const { return VMOp_GenCollectForAllocation; }
  virtual void doit();
};

// VM operation to invoke a collection of the heap as a
// SerialHeap heap.
class VM_GenCollectFull: public VM_GC_Operation {
 private:
  SerialHeap::GenerationType _max_generation;
 public:
  VM_GenCollectFull(uint gc_count_before,
                    uint full_gc_count_before,
                    GCCause::Cause gc_cause,
                    SerialHeap::GenerationType max_generation)
    : VM_GC_Operation(gc_count_before, gc_cause, full_gc_count_before,
                      max_generation != SerialHeap::YoungGen /* full */),
      _max_generation(max_generation) { }
  ~VM_GenCollectFull() {}
  virtual VMOp_Type type() const { return VMOp_GenCollectFull; }
  virtual void doit();
};


#endif // SHARE_GC_SERIAL_SERIALVMOPERATIONS_HPP