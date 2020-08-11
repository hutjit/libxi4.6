#ifndef XI_WORD_BOUNDED_QUEUE_H_
#define XI_WORD_BOUNDED_QUEUE_H_ 

#include <stdio.h>
#include <stdint.h>

namespace xi {

class WordBoundedQueue
{
   public :
      WordBoundedQueue(uint32_t capacity);
      ~WordBoundedQueue();

      uint32_t Capacity();
      uint32_t Size();
      bool Empty();
      bool Full();
      bool TryPush(size_t value);
      bool TryPop(size_t &value);

      uint32_t do_not_use_wheel_gap();

   private :
      const uint32_t slot_size_;
      uint32_t used_size_;
      size_t *buffer_head_;
      size_t *buffer_tail_;
      size_t *write_cursor_;
      size_t *read_cursor_;
};

}

#endif
