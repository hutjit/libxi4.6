// vim:ts=3:sts=3:sw=3

#ifndef XI_COUNTER_H_
#define XI_COUNTER_H_

#include <stdint.h>
#include <tbb/atomic.h>

namespace xi {

class Counter
{
   public :
      Counter(uint32_t capacity);
      ~Counter();

      void                 Clear();
      bool                 Increase(uint32_t index);
      uint64_t             Get(uint32_t index) const;

   private :
      const uint32_t       capacity_;
      tbb::atomic<uint64_t> *counter_;
};

}

#endif
