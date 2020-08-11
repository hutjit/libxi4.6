// vim:ts=3:sts=3:sw=3:expandtab

#ifndef XI_SYNC_H_
#define XI_SYNC_H_

#include <pthread.h>

namespace xi {

class Sync {
   public :
      Sync();
      ~Sync();

      void Wait();
      bool Wait(unsigned int usec);
      void Signal();
      void SignalWithoutLock();

   private :
      pthread_cond_t  cond_;
      pthread_mutex_t mutex_;
};

}

#endif

