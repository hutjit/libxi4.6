// vim:ts=3:sts=3:sw=3

#ifndef XI_ALARM_H_
#define XI_ALARM_H_

#include <map>
#include "xi/thread.hxx"
#include "xi/string.hxx"
#include "xi/mutex.hxx"
#include "xi/singleton.hxx"
#include "xi/util.hxx"

namespace xi {

class AlarmEl 
{
   public :
      virtual ~AlarmEl()  { m_Key.Clear(); }
      virtual void          Timeout() = 0;

      const char           *GetKey();
      uint32_t            GetSize();
      bool                  IsEqual(const char *pKey);

   protected :
      String              m_Key;
};

class AlarmMgr : public Singleton<AlarmMgr>
{
   public :
      static const uint32_t   TABLE_SIZE = 20;
      typedef std::multimap<msec_t, AlarmEl*>           ALARMTABLE;
      typedef std::multimap<msec_t, AlarmEl*>::iterator ALARMITER;

      AlarmMgr();
      ~AlarmMgr();

      uint64_t            Start(uint32_t ms, AlarmEl *pEl);
      bool                  Stop(uint64_t id, const char *pKey);

      void                  RunTrigger();

   private :
      Thread             *m_pThread;

      Mutex               m_lock[TABLE_SIZE];
      ALARMTABLE            m_table[TABLE_SIZE];
};

template<class T>
class TAlarmEl : public AlarmEl 
{
   public :
      TAlarmEl(T *_t, void (T::*_j)(const char *), const char *pArg) : t(_t), j(_j) { m_Key = pArg; }
      virtual ~TAlarmEl() {}

      virtual void          Timeout() { (t->*j)(m_Key.c_str()); }

   private :
      T *t;
      void (T::*j)(const char *pArg);
};

template<class T>
uint64_t AlarmStart(T *_t, void (T::*_j)(const char *), uint32_t ms, const char *pArg)
{
   if (IsZero(pArg)) return 0;

   AlarmEl *pEl = new TAlarmEl<T>(_t, _j, pArg);
   return AlarmMgr::Instance()->Start(ms, pEl);
}

bool AlarmStop(uint64_t id, const char *pKey);

}

#endif // XI_ALARM_H_
