// vim:ts=3:sts=3:sw=3

#ifndef XI_LAZY_DESTRUCTOR_H_
#define XI_LAZY_DESTRUCTOR_H_

#include <map>
#include "xi/mutex.hxx"
#include "xi/util.hxx"
#include "xi/singleton.hxx"
#include "xi/task.hxx"
#include "xi/thread.hxx"

namespace xi {

template<class T>
class Garbage : public Task
{
   public:
      Garbage(T *obj) : object_(obj) {}
      virtual ~Garbage()
      {
         delete object_;
      }

      virtual void Exec() {}

   private:
      T *object_;
};

class LazyDestructor : public Singleton<LazyDestructor>
{
   public :
      LazyDestructor();
      ~LazyDestructor();

      void Push(Task *garbage, msec_t delay);
      void Housekeeper();

   private :
      static const uint32_t MAX_ORDERED_MAP_SIZE = 4;

      Thread *housekeeper_;
      Mutex m_orderedMapLock[MAX_ORDERED_MAP_SIZE];
      std::multimap<msec_t, Task*> m_orderedMap[MAX_ORDERED_MAP_SIZE];
};

}

#endif
