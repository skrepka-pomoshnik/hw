#include <atomic>

template <class Obj>

class MyLittleAtomicStack {
    std::atomic<Obj*> top_ptr;
    Obj* Pop() {
        while(1) {
            Obj* rptr = top_ptr;
            if (!rptr) return nullptr;
            Obj* next_ptr = rptr->next;
            if (top_ptr.compare_exchange_weak(rptr, next_ptr)) {
                return rptr;
            }
        }
    }
    void Push(Obj* obj_ptr) {
      while(1) {
        Obj* next_ptr = top_ptr;
        obj_ptr->next = next_ptr;
        if (top_ptr.compare_exchange_weak(next_ptr, obj_ptr)) {
          return;
        }
      }
    }
  };


int main (int argc, char* argv[]) {
}

