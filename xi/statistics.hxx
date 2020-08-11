// vim:ts=3:sts=3:sw=3

#ifndef XILIB_STATISTICS_H_
#define XILIB_STATISTICS_H_

#include <stdint.h>
#include <string>

namespace xi {


class StatisticsImpl;

class Statistics 
{
   public :
      Statistics();
      ~Statistics();
      void Clear();
      void                 SetExpires(uint32_t hour);
      void                 SetMethodName(uint16_t method, const char *name);
      const char          *GetMethodName(uint16_t method);

      void                 Stat(bool is_recv, uint16_t method, int16_t status_code);
      std::string          ToString();
      std::string          ToStringHour();
      std::string          ToStringRecent10Min();

   private :
      StatisticsImpl      *impl_;
};


}

#endif // XI_STATISTICS_H_
