// vim:ts=3:sts=3:sw=3


#ifndef XI_LOGGER_H_
#define XI_LOGGER_H_

#include <set>
#include <string>

#include "tbb/concurrent_queue.h"

#include "xi/mutex.hxx"
#include "xi/singleton.hxx"
#include "xi/string.hxx"
#include "xi/thread.hxx"
#include "xi/sync.hxx"

typedef void (*normal_logging_callback)(unsigned level, const char *logstr, const size_t logsize);
typedef void (*verbose_logging_callback)(unsigned level, const char *logstr, const size_t logsize, const char *file, unsigned line);
typedef void (*llt_logging_callback)(const char *logstr, const size_t logsize);

namespace xi {


#define XIVERBLOGGING(level, args) do {                                        \
   xi::Logger *logger = xi::Logger::Instance();                                \
   if (logger->CanLogging(level)) {                                            \
      xi::String *oss = logger->CreateLogHead(pthread_self(), level);          \
      (*oss) << args;                                                          \
      logger->VerboseLogging(level, oss, __FILE__, __LINE__);                  \
   }                                                                           \
} while (0)

#define XILOGGING(level, args) do {                                            \
   xi::Logger *logger = xi::Logger::Instance();                                \
   if (logger->CanLogging(level)) {                                            \
      xi::String *oss = logger->CreateOutHead(pthread_self());                 \
      (*oss) << args;                                                          \
      logger->NormalLogging(level, oss);                                       \
   }                                                                           \
} while (0)

#define XILLTOUT(args) do {                                                    \
   xi::Logger *logger = xi::Logger::Instance();                                \
   if (logger->CanLLTLogging()) {                                              \
      xi::String *oss = logger->CreateLltHead(pthread_self());                 \
      (*oss) << args;                                                          \
      logger->LltLogging(oss);                                                 \
   }                                                                           \
} while (0)


#define SETLOGPATH(path)         xi::Logger::Instance()->SetFileName(path)
#define SETLOGLEVEL(level)       xi::Logger::Instance()->SetLevel(level)
#define GETLOGLEVEL()            xi::Logger::Instance()->GetLevel()
#define SETLOGFILESIZE(limit)    xi::Logger::Instance()->SetFileSegmentSize(limit)
#define GETLOGFILESIZE()         xi::Logger::Instance()->GetFileSegmentSize()
#define SETLOGFILELIMIT(limit)   xi::Logger::Instance()->SetFileRetentionCount(limit)
#define GETLOGFILELIMIT()        xi::Logger::Instance()->GetFileRetentionCount()
#define SETLLTFLAG(flag)         xi::Logger::Instance()->SetLLT(flag)
#define CANLOGGING(level)        xi::Logger::Instance()->CanLogging(level)
#define CANLLTLOGGING()          xi::Logger::Instance()->CanLLTLogging()

#define DLOG(A)                  XIVERBLOGGING(xi::loglevel::DEBUG,   A)
#define ILOG(A)                  XIVERBLOGGING(xi::loglevel::INFO,    A)
#define WLOG(A)                  XIVERBLOGGING(xi::loglevel::WARNING, A)
#define ELOG(A)                  XIVERBLOGGING(xi::loglevel::ERROR,   A)
                                         
#define DOUT(A)                  XILOGGING(xi::loglevel::DEBUG,       A)
#define IOUT(A)                  XILOGGING(xi::loglevel::INFO,        A)
#define WOUT(A)                  XILOGGING(xi::loglevel::WARNING,     A)
#define EOUT(A)                  XILOGGING(xi::loglevel::ERROR,       A)

#define LLTOUT(A)                XILLTOUT(A)

#define RED(data)                "[1;31m" << data << "[0m"
#define GREEN(data)              "[1;32m" << data << "[0m"
#define YELLOW(data)             "[1;33m" << data << "[0m"
#define BLUE(data)               "[1;34m" << data << "[0m"
#define PURPLE(data)             "[1;35m" << data << "[0m"
#define CYAN(data)               "[1;36m" << data << "[0m"
#define WHITE(data)              "[1;37m" << data << "[0m"
                                 
#define DRED(data)               "[31m" << data << "[0m"
#define DGREEN(data)             "[32m" << data << "[0m"
#define DYELLOW(data)            "[33m" << data << "[0m"
#define DBLUE(data)              "[34m" << data << "[0m"
#define DPURPLE(data)            "[35m" << data << "[0m"
#define DCYAN(data)              "[36m" << data << "[0m"
#define DWHITE(data)             "[37m" << data << "[0m"
                                 
#define BRED(data)               "[1;41m" << data << "[0m"
#define BGREEN(data)             "[1;42m" << data << "[0m"
#define BYELLOW(data)            "[1;43m" << data << "[0m"
#define BBLUE(data)              "[1;44m" << data << "[0m"
#define BPURPLE(data)            "[1;45m" << data << "[0m"
#define BCYAN(data)              "[1;46m" << data << "[0m"
#define BWHITE(data)             "[1;47m" << data << "[0m"



class Logger : public Singleton<Logger> {
   public :
      Logger();
      ~Logger();

      bool                  CanLogging(xi::loglevel::e level);
      bool                  CanLLTLogging();

      xi::String           *CreateOutHead(pthread_t pid);
      xi::String           *CreateLogHead(pthread_t pid, xi::loglevel::e level);
      xi::String           *CreateLltHead(pthread_t pid);
      void                  LltLogging(xi::String *oss);
      void                  NormalLogging(xi::loglevel::e level, xi::String *oss);
      void                  VerboseLogging(xi::loglevel::e level, xi::String *oss, const char *file, unsigned line);
      void                  ThreadLogger();

      void                  SerVerbose(bool flag);
      xi::loglevel::e       SetLevel(xi::loglevel::e level);
      xi::loglevel::e       GetLevel();
      void                  SetFileName(const char *fileName);
      const char           *GetFileName();
      void                  SetStdout();
      void                  SetCallback(normal_logging_callback, verbose_logging_callback, llt_logging_callback);

      void                  SetFileSegmentSize(unsigned int bytes);
      unsigned int          GetFileSegmentSize();
      void                  SetFileRetentionCount(unsigned int count);
      unsigned int          GetFileRetentionCount();

      void                  SetLLT(bool flag);

   private :
      FILE                 *CheckFile();
      void                  EraseExpiredLog();
      void                  GetLogFileList(std::set<std::string> &rLogList);

   private :
      xi::logoutput::e      output_type_;
      uint32_t              log_head_length_;
      uint32_t              llt_head_length_;

      bool                  verbose_;
      bool                  llt_level_;
      xi::loglevel::e       log_level_;
      xi::String            log_filename_;
      unsigned int          file_segment_bytes_;
      unsigned int          file_retention_count_;

      // file
      tbb::concurrent_bounded_queue<String*> queue_;
      Sync                  wakeup_;
      Thread               *housekeeper_;
      FILE                 *logging_fp_;

      // callback
      normal_logging_callback normal_logging_callback_;
      verbose_logging_callback verbose_logging_callback_;
      llt_logging_callback llt_logging_callback_;
};


}

#endif // XI_LOG_H_
