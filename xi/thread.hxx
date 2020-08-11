// vim:ts=3:sts=3:sw=3

#ifndef XI_THREAD_H_
#define XI_THREAD_H_ 

#include <stdlib.h>
#include "xi/task.hxx"

namespace xi {

class ThreadImp;

// * Priority Scheduling 지원하지 않음
// * Automatically delete thread object on termination
// * default stack size: 1M
class Thread {
	public :
		Thread();
      virtual ~Thread();

      void              SetStackSize(unsigned int stack_size);

		bool              Start(Task *task);
      void              Stop();
      bool              IsStopped();

	private :
      ThreadImp      *imp_;
};

template<class T>
Thread *CreateThread(unsigned int stack_size, T *object, void (T::*func)())
{
   Thread *thread = new Thread;
   thread->SetStackSize(stack_size);
   if (false == thread->Start(new TaskWithoutParam<T>(object, func))) {
      abort();
   }

   return thread;
}

template<class T, class P>
Thread *CreateThread(unsigned int stack_size, T *object, void (T::*func)(P *), P *param)
{
   Thread *thread = new Thread;
   thread->SetStackSize(stack_size);
   if (false == thread->Start(new TaskWithParam<T, P>(object, func, param))) {
      abort();
   }

   return thread;
}

}

#endif // XI_THREAD_H_
