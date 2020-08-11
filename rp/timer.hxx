#ifndef XI_RP_TIMER_H_
#define XI_RP_TIMER_H_

#include "xi/define.hxx"
#include "rp/define.hxx"

namespace xi {
namespace rp {

class TimerImpl;

class Timer
{
   public :
      friend class TcRpTimer;

      Timer(const uint32_t wheeling_second, const uint32_t timer_element_capacity);
      ~Timer();

      timerid_t StartTimer(const xi::msec_t expires, const xi::rp::sessid_t sessid, const xi::rp::membid_t membid, const uint32_t tuparam);
      bool StopTimer(const xi::timerid_t timerid);
      virtual void OnTimeout(xi::timerid_t timerid, xi::rp::sessid_t sessid, xi::rp::membid_t membid, uint32_t tuparam) = 0;

      uint32_t Capacity();
      uint32_t Busy();

   private :
      TimerImpl *impl_;
};

}
}

#endif
