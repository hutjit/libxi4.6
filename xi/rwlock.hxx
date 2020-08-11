// vim:ts=3:sts=3:sw=3

#ifndef XI_READ_WRITE_LOCK_H_
#define XI_READ_WRITE_LOCK_H_

#include <pthread.h>
#include "xi/define.hxx"

namespace xi {


class RwLock {
   public :
      class ScopedLockRead {
         public :
            inline ScopedLockRead(const RwLock &rwlock) : lock_((RwLock &)rwlock) { lock_.ReadLock(); }
            ~ScopedLockRead() { lock_.Unlock(); }

         private :
            RwLock &lock_;
            DISALLOW_COPY_AND_ASSIGN(ScopedLockRead);
      };

      class ScopedLockWrite {
         public :
            inline ScopedLockWrite(const RwLock &rwlock) : lock_((RwLock &)rwlock) { lock_.WriteLock(); }
            ~ScopedLockWrite() { lock_.Unlock(); }

         private :
            RwLock &lock_;
            DISALLOW_COPY_AND_ASSIGN(ScopedLockWrite);
      };


   public :
      RwLock();
      ~RwLock();

      void ReadLock();
      void WriteLock();
      void Unlock();

   private :
      pthread_rwlock_t lock_;
      DISALLOW_COPY_AND_ASSIGN(RwLock);
};


}

#endif
