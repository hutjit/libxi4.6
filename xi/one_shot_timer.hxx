// vim:ts=3:sts=3:sw=3

#ifndef XI_ONESHOT_TIMER_H_
#define XI_ONESHOT_TIMER_H_ 

#include <time.h>
#include <map>
#include "xi/define.hxx"
#include "xi/singleton.hxx"
#include "xi/mutex.hxx"
#include "xi/thread.hxx"
#include "xi/util.hxx"

// #############################################################################
// * 하위 호환성을 위해 남겨놓았다.
// * 지원제외 항목이므로, 사용하지 말아야 한다.
// #############################################################################

namespace xi {

typedef uint32_t OSTID;

typedef enum {
   TFSM_IDLE = 0,
   TFSM_WAIT_TIMEOUT
} TIMER_STATE;

class OneShotTimer {
   public:
      OneShotTimer() : m_timerId(0), m_expireTime(0), m_state(TFSM_IDLE) {}
      virtual ~OneShotTimer() {}

      void                    StartTimer(uint32_t interval, int iParam); // msec
      bool                    StopTimer();

      virtual void            TriggerTimeout(OSTID id) = 0;
      bool                    IsWaitTimeout()         { return (TFSM_WAIT_TIMEOUT == m_state); }
      OSTID                   GetTimerId()            { return m_timerId; }

   protected :
      // StartTimer에서 timerid를 할당 받는다.
      // StopTimer에서 timerid를 반납한다.
      void                    ChangeState(TIMER_STATE state, OSTID id = 0);

   protected :
      xi::Mutex               m_lock;
      OSTID                   m_timerId;
      xi::msec_t              m_expireTime;
      TIMER_STATE             m_state;
                              
      int                     m_iParam;
};

template<class T>
class TOneShotTimer : public xi::OneShotTimer {
   public:
      TOneShotTimer(T *_t, void (T::*_j)(int)) : t(_t), j(_j) {}
      virtual void TriggerTimeout(OSTID id) { 
         if (id != GetTimerId()) 
            return;

         m_lock.Lock();
         if (IsWaitTimeout()) {
            ChangeState(TFSM_IDLE);
            m_lock.Unlock();

            (t->*j)(m_iParam); 

         } else {
            m_lock.Unlock();
         }
      }

   private:
      T *t;
      void (T::*j)(int);
};

// ****** ShortTimer의 생성 및 삭제는 아래의 함수 쌍을 이용해야 한다. ******
template<class T>
xi::OneShotTimer *CreateOneShotTimer(T *t, void (T::*j)(int)) {
   return (new TOneShotTimer<T>(t, j));
}

void DeleteOneShotTimer(xi::OneShotTimer *pTimer);


// =====================================================================================================
// xi::OneShotTimerMgr
// -----------------------------------------------------------------------------------------------------
class OneShotTimerMgr : public Singleton<OneShotTimerMgr>
{
   public :
      class TimerEl {
         public :
            TimerEl() : m_timerId(0), m_pTimer(NULL) {}
            TimerEl(OSTID timerId, xi::OneShotTimer *pTimer) : m_timerId(timerId), m_pTimer(pTimer) {}

            OSTID             GetTimerId()    { return m_timerId; }
            xi::OneShotTimer *GetTimer()      { return m_pTimer; }

         private :
            OSTID             m_timerId;
            xi::OneShotTimer *m_pTimer;
      };

      typedef std::multimap<xi::msec_t, TimerEl>::iterator TQMAP_ITER;

   public :
      OneShotTimerMgr();
      ~OneShotTimerMgr();

      OSTID                   GetNextTimerID_unsafe();

      OSTID                   StartTimer(xi::msec_t expireTime, xi::OneShotTimer *pTimer);
      void                    StopTimer(xi::msec_t expireTime, xi::OneShotTimer *pTimer);
      void                    DeleteTimer(xi::OneShotTimer *pTimer);
                              
      void                    RunTrigger();
      void                    RunSlowDestructor();

   private :
      // -------------------- RunWorker --------------------
      xi::Mutex                                 m_lock;
      xi::Thread                               *m_pTimerWorker;
      std::multimap<xi::msec_t, TimerEl>        m_timeQueue;

      // -------------------- TimerID --------------------
      OSTID                                     m_NextTimerID;

      // -------------------- Slow Destructor --------------------
      xi::Mutex                                 m_slowDestructorLock;
      std::multimap<time_t, xi::OneShotTimer *> m_slowDestructorTable;
};

}

#endif 
