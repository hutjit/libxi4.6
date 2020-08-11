// vim:ts=3:sts=3:sw=3
// coding convention : https://google.github.io/styleguide/cppguide.html

#ifndef STACK_WEBSOCKET_DEFINE_H_
#define STACK_WEBSOCKET_DEFINE_H_

#include <stdint.h>
#include "xi/string.hxx"

namespace xi {
namespace websocket {


const char *Version();

namespace opcode {
   typedef enum {
      NONE = 0,
      CONTINUATION,
      TEXT,
      BINARY,
      CLOSE,
      PING,
      PONG,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
   bool        valid(e param);
   e           code(uint8_t encoded);
   uint8_t     encode(e param);
   bool        is_control(e param);
}

namespace result {
   typedef enum {
      NONE = 0,
      SUCCESS,
      WANT_READ,
      PROTOCOL_ERROR,
      SHORTAGE_OF_RESOURCE, 
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace state {
   typedef enum {
      NONE = 0,
      CONNECTING,
      ESTABLISHED,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace csmod {
   typedef enum {
      NONE = 0,
      CLIENT,
      SERVER,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace method
{
   typedef enum {
      NONE = 0,
      GET,
      PUT,
      HEAD,
      POST,
      PATCH,      /* RFC5789 */
      TRACE,
      DELETE,
      CONNECT,
      OPTIONS,
      END_OF_ENUM
   } e;
   const char *name(e type);
   bool        scope(e type);
   e           code(const String &name);
   e           code(const char *name, const uint32_t len);
}


}
}
#endif
