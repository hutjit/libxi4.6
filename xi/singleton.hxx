// vim:ts=3:sts=3:sw=3

#ifndef XI_SINGLETON_H_
#define XI_SINGLETON_H_

#include "xi/mutex.hxx"

namespace xi {

template<class T> class Singleton {
   public:
      static T *Instance();
      template<class U> static T *Instance(const U &);

   protected:
      Singleton();
      ~Singleton();

   public:
      static T *instance_;
      static Mutex lock_;
};

template<class T> Singleton<T>::Singleton()
{
}

template<class T> Singleton<T>::~Singleton()
{
   xi::Mutex::ScopedLock lock(lock_);
   instance_ = NULL;
}

// Function to access the singleton
template<class T> T *Singleton<T>::Instance()
{
   if (NULL == instance_) {
      xi::Mutex::ScopedLock lock(lock_);

      // We have to check it again after we got the lock
      if (NULL == instance_)
         instance_ = new T;
   }

   return instance_;
}


// static members
template<class T> T *Singleton<T>::instance_ = NULL;
template<class T> Mutex Singleton<T>::lock_;

}

#endif
