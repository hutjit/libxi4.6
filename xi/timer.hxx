// vim:ts=3:sts=3:sw=3

#ifndef XI_TIMER_H_
#define XI_TIMER_H_ 

#include "xi/define.hxx"

namespace xi {

class TimerImp;

class Timer {
   public :
      Timer();
      virtual ~Timer();

      timerid_t               StartTimer(uint32_t interval_msec, const uint8_t *buffer, const uint32_t buflen);
      bool                    StopTimer(timerid_t timerid);
      virtual void            OnTimeout(timerid_t timerid, uint8_t *buffer, uint32_t buflen) = 0;  // business logic 으로 callback

   private :
      TimerImp             *imp_;
};

}

#endif // XI_TIMER_H_
