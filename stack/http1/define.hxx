// vim:ts=3:sts=3:sw=3

#ifndef STACK_HTTP1_DEFINE_H_
#define STACK_HTTP1_DEFINE_H_ 

#include "xi/string.hxx"

namespace xi {
namespace h1 {


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
   const char *name(e param);
   bool        scope(e param);
   e           code(const String &name);
   e           code(const char *name, const uint32_t len);
}


}
}

#endif
