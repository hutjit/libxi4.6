// vim:ts=3:sts=3:sw=3

#ifndef XI_MUTEX_H_
#define XI_MUTEX_H_

#include <pthread.h>
#include "xi/define.hxx"

namespace xi {

class Mutex {
   public :
      class ScopedLock {
         public :
            inline ScopedLock(const Mutex &mutex) : lock_((Mutex &)mutex) { lock_.Lock(); }
            ~ScopedLock() { lock_.Unlock(); }

         private :
            Mutex &lock_;
            DISALLOW_COPY_AND_ASSIGN(ScopedLock);
      };

      Mutex();
      ~Mutex();

      void              Lock();
      void              Unlock();

   private :
      pthread_mutex_t   mutex_;
};

}

#endif
