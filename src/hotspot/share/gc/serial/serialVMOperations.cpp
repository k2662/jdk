#include "gc/serial/serialVMOperations.hpp"
#include "gc/shared/gcLocker.hpp"

void VM_GenCollectForAllocation::doit() {
  SvcGCMarker sgcm(SvcGCMarker::MINOR);

  SerialHeap* gch = SerialHeap::heap();
  GCCauseSetter gccs(gch, _gc_cause);
  _result = gch->satisfy_failed_allocation(_word_size, _tlab);
  assert(_result == nullptr || gch->is_in_reserved(_result), "result not in heap");

  if (_result == nullptr && GCLocker::is_active_and_needs_gc()) {
    set_gc_locked();
  }
}

void VM_GenCollectFull::doit() {
  SvcGCMarker sgcm(SvcGCMarker::FULL);

  SerialHeap* gch = SerialHeap::heap();
  GCCauseSetter gccs(gch, _gc_cause);
  gch->do_full_collection(gch->must_clear_all_soft_refs(), _max_generation);
}