// vim:ts=3:sts=3:sw=3

#ifndef XI_DEFINE_H_
#define XI_DEFINE_H_

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#define _ABORT(sec)  do { sleep(sec); abort(); } while(0)
#define _EXIT(sec)   do { sleep(sec); exit(1); } while(0)

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
   TypeName(const TypeName&);               \
void operator=(const TypeName&)


// logging callback function으로 util.hxx에 정의된 SetupLoggingCallbacks() 로
// callback을 등록하면 라이브러리 에서 남기는 로그를 callback 받을 수 있다.
// - level : 1:error, 2:warning, 3:info, 4:debug
// - logstr : 로그
// - logsize : 로그 길이
// - file : source filename
// - line : source file에서의 log 호출 라인
typedef void (*normal_logging_callback)(unsigned level, const char *logstr, const size_t logsize);
typedef void (*verbose_logging_callback)(unsigned level, const char *logstr, const size_t logsize, const char *file, unsigned line);
typedef void (*llt_logging_callback)(const char *logstr, const size_t logsize);


namespace db
{
   namespace sqlstate
   {
      typedef enum {
         SUCCESS = 0,
         NO_ROWS,
         NO_CONNECTION,
         CONSTRAINT_FAIL,
         UNIQUE_CONSTRAINT,
         TRUNCATED,
         QUERY_TIMEOUT,
         INVALID_ARGUMENT,
         INVALID_STATEMENT,
         UNKNOWN_ERROR,
         END_OF_ENUM
      } e;
      const char *name(e param);
      bool        scope(e param);
   }
}


namespace xi {

// type define
typedef uint64_t msec_t;
typedef uint64_t socketkey_t;
typedef uint32_t timerid_t;
typedef uint32_t indexid_t;


namespace loglevel
{
   typedef enum {
      NONE = 0,
      ERROR = 1,
      WARNING = 2,
      INFO = 3,
      DEBUG = 4,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
   e           code(const char *name);
}

namespace logoutput
{
   typedef enum {
      NONE,
      FILE,
      STDOUT,
      CALLBACK,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace result
{
   typedef enum {
      NONE = 0,
      SUCCESS,
      FAIL,
      NOT_FOUND,
      WANT_READ,
      WANT_WRITE,
      INVALID_ARGUMENT,
      UNIQUE_CONSTRAINT,
      INVALID_STATEMENT,
      ROW_IS_REFERENCED,
      NO_REFERENCED_ROW,
      TRUNCATED,
      SHORTAGE_OF_RESOURCE,
      FATAL,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace iomod
{
   typedef enum {
      NONE = 0,
      BASIC,
      ENHANCED,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
   e           code(const char *name);
}

namespace ioevt
{
   typedef enum {
      NONE = 0,
      ACCEPT,
      CONNECT,
      CONNECT_FAIL,
      SEND_FAIL,
      PEER_CLOSE,
      READ_FAIL,
      KEEPALIVE_TIMEOUT,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace ioctrl
{
   typedef enum {
      NONE = 0,
      SEND_AND_CLOSE,   // 전송 후 종료
      SEND_AND_KEEP,    // 상태 유지
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace iodebug {
   typedef enum {
      NONE = 0,
      VERBOSE,
      SLIGHTLY,
      SILENTLY,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
   e           code(const char *name);
}

namespace iptype
{
   typedef enum {
      NONE = 0,
      UDP,
      TCP,
      TLS,
      SCTP,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace ipver
{
   typedef enum {
      NONE = 0,
      V4,
      V6,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace sostate
{
   typedef enum {
      NONE,
      SYN_SENT,
      TLS_HANDSHAKING,
      ESTABLISHED,
      BROKEN,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace color
{
   typedef enum {
      NONE = 0,
      RED,
      GREEN,
      YELLOW,
      BLUE,
      PURPLE,
      CYAN,
      WHITE,
      DRED,
      DGREEN,
      DYELLOW,
      DBLUE,
      DPURPLE,
      DCYAN,
      DWHITE,
      BRED,
      BGREEN,
      BYELLOW,
      BBLUE,
      BPURPLE,
      BCYAN,
      BWHITE,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
   e           code(const char *name);
   const char *starttag(e param);
   const char *endtag(e param);
}

namespace iocfg {
   // - "interface-name" : SetName(std::string name);
   // - "io-thread"
   // - "ssl-ctx"
   // - "packet-buffer-size" : SetPacketBufferSize(uint32_t iPacketBufferSize);
   // - "authentication-timeout" : SetWaitAuthTime(int iSec);
   // - "application-keep-alive-timeout"
   // - "connect-timeout"
   // - "backlog-size" : SetTcpBacklog(int nBacklog);
   // - "max-session" : SetMaxAcceptFdset(uint32_t nLimit);
   // - "max-packet-queue"
   // - "verbose-level" : default "verbose", ["slightly", "silently"] 패킷 send/recv 정보 출력
   // - "recv-log-color" : SetRecvColor(enColor color);
   // - "send-log-color" : SetSendColor(enColor color);
   // - "send-socket-buffer"
   // - "recv-socket-buffer"
   // - "ca-certificate-file" : SetCaCert(const char *pCaCertFile, bool useBuffer = false);
   // - "client-certificate-file" : SetClientCert(const char *pCertFile, bool useBuffer = false);
   // - "client-certkey-file" : SetClientKey(const char *pKeyFile, const char *pPasswd, bool useBuffer = false);
   // - "client-certkey-file-password" : SetClientKey(const char *pKeyFile, const char *pPasswd, bool useBuffer = false);
   // - "server-certificate-file" : SetServerCert(const char *pCertFile, bool useBuffer = false);
   // - "server-certkey-file" : SetServerKey(const char *pKeyFile, const char *pPasswd, bool useBuffer = false);
   // - "server-certkey-file-password" : SetServerKey(const char *pKeyFile, const char *pPasswd, bool useBuffer = false);
   // - "tls-session-cache" : SetTlsSessCacheOff();
   // - "tls-server-verify" : SetTlsServerVerify(int opt);
   // - "tls-client-verify" : SetTlsClientVerify(int opt);

   namespace boolean {
      typedef enum {
         NONE = 0,
         TCP_NODELAY,
         TLS_SESSION_CACHE,
         TLS_VERIFY_PEER,
         END_OF_ENUM
      } e;
      const char *name(e param);
      bool        scope(e param);
      e           code(const char *name);
      bool        default_value(e value);
   }

   namespace numeric {
      typedef enum {
         NONE = 0,
         IO_THREAD,
         PACKET_BUFFER_SIZE,
         AUTHENTICATION_TIMEOUT,
         APPLICATION_KEEP_ALIVE_TIMEOUT,
         CONNECT_TIMEOUT,
         BACKLOG_SIZE,
         MAX_CONNECTION,
         MAX_PACKET_QUEUE,
         SEND_SOCKET_BUFFER,
         RECV_SOCKET_BUFFER,
         END_OF_ENUM
      } e;
      const char *name(e param);
      bool        scope(e param);
      e           code(const char *name);
      int32_t     default_value(e value);
   }

   namespace characters {
      typedef enum {
         NONE = 0,
         INTERFACE_NAME,
         VERBOSE_LEVEL,  // verbose, slightly, silently
         RECV_LOG_COLOR,
         SEND_LOG_COLOR,
         CA_CERTIFICATE_FILE,
         CLIENT_CERTIFICATE_FILE,
         CLIENT_CERTKEY_FILE,
         SERVER_CERTIFICATE_FILE,
         SERVER_CERTKEY_FILE,
         SERVER_TLS_ALPN,
         END_OF_ENUM
      } e;
      const char *name(e param);
      bool        scope(e param);
      e           code(const char *name);
      const char *default_value(e value);
   }
}

}

#endif // XI_TYPEDEF_H_
