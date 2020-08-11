// vim:ts=3:sts=3:sw=3

#ifndef XI_THREAD_POOL_H_
#define XI_THREAD_POOL_H_ 

#include <list>

#include <tbb/concurrent_queue.h>
#include <tbb/atomic.h>

#include "xi/mutex.hxx"
#include "xi/sync.hxx"
#include "xi/thread.hxx"

namespace xi {

class ThreadPool 
{
   public:
      friend class Thread;

      static const uint32_t   kMaxQueueSize     = 200000;
      static const uint32_t   kMaxThreadCount   = 200;

   public:
      ThreadPool();
      ~ThreadPool();

      bool                    Initialize(uint32_t thread_count, unsigned int stack_size, uint32_t queue_size = kMaxQueueSize);

      void                    Enqueue(Task *pJob);

      uint32_t                PendingTaskCount();
      uint32_t                IdleThreadCount();
      uint32_t                TotalThreadCount();

   private :
      void                    TaskConsumer(uint32_t *id);
      bool                    TaskConsume();
      void                    WaitSignal(uint32_t thread_id);

   private :
      bool                    activated_;
      bool                    stop_;

      uint32_t                task_queue_limit_;
      tbb::atomic<uint32_t>   pending_task_count_;
      tbb::concurrent_bounded_queue<Task*>  task_queue_;

      Mutex                   lock_;
      bool                    idle_thread_flag_[kMaxThreadCount];
      uint32_t                total_thread_count_;
      std::list<Thread*>      thread_list_;

      Sync                    thread_wakeup_;
};

}

#endif // XI_THREADPOOL_H_
