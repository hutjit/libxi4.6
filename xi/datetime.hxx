// vim:ts=3:sts=3:sw=3

#ifndef XI_AXTIME_H_
#define XI_AXTIME_H_ 

#include "xi/define.hxx"
#include "xi/string.hxx"

// ======================================================================================================
// [strftime Parameters] http://www.cplusplus.com/reference/ctime/strftime/
// ---+------------------------------------------------------------------------+-------------------------
//    | Replaced by                                                            | Example
// ---+------------------------------------------------------------------------+-------------------------
// %a | Abbreviated weekday name *                                             | Thu
// %A | Full weekday name *                                                    | Thursday
// %b | Abbreviated month name *                                               | Aug
// %B | Full month name *                                                      | August
// %c | Date and time representation *                                         | Thu Aug 23 14:55:02 2001
// %C | Year divided by 100 and truncated to integer (00-99)                   | 20
// %d | Day of the month, zero-padded (01-31)                                  | 23
// %D | Short MM/DD/YY date, equivalent to %m/%d/%y                            | 08/23/01
// %e | Day of the month, space-padded ( 1-31)                                 | 23
// %F | Short YYYY-MM-DD date, equivalent to %Y-%m-%d                          | 2001-08-23
// %g | Week-based year, last two digits (00-99)                               | 01
// %G | Week-based year                                                        | 2001
// %h | Abbreviated month name * (same as %b)                                  | Aug
// %H | Hour in 24h format (00-23)                                             | 14
// %I | Hour in 12h format (01-12)                                             | 02
// %j | Day of the year (001-366)                                              | 235
// %m | Month as a decimal number (01-12)                                      | 08
// %M | Minute (00-59)                                                         | 55
// %n | New-line character ('\n')                                              |
// %p | AM or PM designation                                                   | PM
// %r | 12-hour clock time *                                                   | 02:55:02 pm
// %R | 24-hour HH:MM time, equivalent to %H:%M                                | 14:55
// %S | Second (00-61)                                                         | 02
// %t | Horizontal-tab character ('\t')                                        |
// %T | ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S                | 14:55:02
// %u | ISO 8601 weekday as number with Monday as 1 (1-7)                      | 4
// %U | Week number with the first Sunday as the first day of week one (00-53) | 33
// %V | ISO 8601 week number (00-53)                                           | 34
// %w | Weekday as a decimal number with Sunday as 0 (0-6)                     | 4
// %W | Week number with the first Monday as the first day of week one (00-53) | 34
// %x | Date representation *                                                  | 08/23/01
// %X | Time representation *                                                  | 14:55:02
// %y | Year, last two digits (00-99)                                          | 01
// %Y | Year                                                                   | 2001
// %z | ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100)          |
//    | If timezone cannot be termined, no characters                          | +100
// %Z | Timezone name or abbreviation *                                        |
//    | If timezone cannot be termined, no characters                          | CDT
// %% | A % sign                                                               | %
// ---+------------------------------------------------------------------------+-------------------------

//	%a  요일 이름의 약자  	
//	%A 	요일 이름 	
//	%b 	월 이름의 약자 	
//	%B 	월 이름 	
//	%c 	지역 날짜와 시간 	
//	%d 	날짜( 01-31) 	
//	%H 	시간(00-23) 	
//	%l 	시간(01-12) 	
//	%j 	1월 1일 이후의 날짜(001-366) 	
//	%m 	월(01-12) 	
//	%M  분(00-59)
//	%p 	AM 또는 PM
//	%S 	초(00-59)
//	%w 	요일(0-6)
//	%x 	지역 날짜
//	%X 	지역 시간
//	%y 	연도(00-99)	
//	%Y 	연도(예, 2003)
//	%% 	퍼센트 기호(%)

/// milli : m : 1/1,000
/// micro : u : 1/1,000,000
/// nano  : n : 1/1,000,000,000

namespace xi {

#define AX_DATETIME_DEFAULT   "%Y%m%d%H%M%S"
#define AX_DATETIME_FULLISO   "%Y-%m-%d %H:%M:%S"
#define AX_DATETIME_ISO8601   "%Y-%m-%dT%H:%M:%S"
#define DATETIME_DEFAULT      "%Y%m%d%H%M%S"
#define DATETIME_FULLISO      "%Y-%m-%d %H:%M:%S"
#define DATETIME_ISO8601      "%Y-%m-%dT%H:%M:%S"


class DateTime
{
   public :
      DateTime();
      DateTime(time_t dtValue);
      ~DateTime();

      char                   *ToString(const char *pFormat = AX_DATETIME_DEFAULT, bool zulu = false);
      time_t                  GetTime();
      time_t                  GetGMT();
      void                    SetNow();
      void                    SetTime(time_t time, bool zulu = false);
      time_t                  SetTime(const char *pTime); // 2011-06-11T07:03:54, 2011-06-11T09:13:52Z
      time_t                  SetYYYYMMDDHH24MISS(const char *pTime, bool zulu = false);
      static bool             AnalyzeFormat(IN const char *pTimeStr, IN uint32_t len, OUT String &rFormat, OUT String *collect = NULL);
                            
   private :                
      char                    strDateTime[32];
      time_t                  m_dt;
      struct tm               m_st;
};

class Timespec
{
   public :
      typedef enum {
         SEC,     // second
         MSEC,    // millisecond
         USEC,    // microsecond
         NSEC     // nanosecond
      } TimeUnits;

   public :
      Timespec();
      Timespec(IN const uint64_t t, IN TimeUnits tunit = SEC, IN bool zulu = false);
      Timespec(IN const char *rfc3339dt, IN unsigned int len);

      void                    SetNow();
      void                    Set(IN const uint64_t t, IN TimeUnits tunit, IN bool zulu = false);
      void                    Set(IN const time_t sec, IN const long nsec, IN bool zulu = false);
      //                                         2011-06-11T07:03:54, 2011-06-11T09:13:52.123456789Z
      bool                    Set(IN const char *rfc3339dt, IN unsigned int len);

      void                    Add(IN uint64_t t, IN TimeUnits tunit);
      void                    AddSec(time_t sec);
      void                    AddSecfrac(long nsec);

      void                    Sub(IN uint64_t t, IN TimeUnits tunit);
      void                    SubSec(time_t sec);
      void                    SubSecfrac(long nsec);

      time_t                  Time(bool zulu = false) const;
      long                    Secfrac() const;
      uint64_t                Convert(IN TimeUnits tunit, IN bool zulu = false) const;

      const char             *Strftime(char *buffer, size_t buflen, const char *fmt = AX_DATETIME_DEFAULT, unsigned int secfrac = 6, bool zulu = false);

      Timespec               &operator=(const Timespec &src);
      bool                    operator>(const Timespec &src);
      bool                    operator<(const Timespec &src);
      bool                    operator>=(const Timespec &src);
      bool                    operator<=(const Timespec &src);
      bool                    operator==(const Timespec &src);

   private :
      unsigned int            ParseTimeNumoffset(const char *tzoffset, OUT int &offset);

   private :
      struct timespec         timespec_;
};

/// struct timeval {
/// 	time_t      tv_sec;     /* seconds */
/// 	suseconds_t tv_usec;    /* microseconds */
/// };
/// struct timespec {
/// 	time_t  tv_sec;     /* seconds */
/// 	long    tv_nsec;    /* nanoseconds */
/// };

}

#endif
