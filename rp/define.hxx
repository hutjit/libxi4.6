#ifndef XI_RP_DEFINE_H_
#define XI_RP_DEFINE_H_

#include <stdint.h>
#include "xi/define.hxx"

namespace xi {
namespace rp {


typedef uint32_t sessid_t;    // 0: invalid id, 8bit:reserve + 20bit:index + 4bit:seq, 20bit(1,048,576)
typedef uint16_t membid_t;    // 0: invalid id
typedef uint16_t pbgid_t;     // 0: invalid id

typedef uint32_t resource_t;  // resource_t
typedef uint32_t payload_t;   // payload_t

namespace result {
   typedef enum {
      SUCCESS = 0,
      FAIL,
      REDIRECT_FSM,
      DO_RELEASE,

      CONFLICT,
      DUPLICATION,
      INVALID_ARGS,
      INVALID_IHSESSION,
      INVALID_STATE,
      NOT_FOUND,
      UNSUPPORTED_FEATURE,

      RESOURCE_ATTACH_FAIL,
      RESOURCE_NOT_FOUND,
      RESOURCE_OBTAIN_FAIL,
      INTERFACE_FAIL,

      OUT_OF_RANGE
   } e;

   const char *name(result::e value);
}

namespace replica {
   namespace opcode {
      typedef enum {
         NONE = 0,
         SIMPLEX_ALLOC,
         SIMPLEX_FREE,
         BULK_REPLICATION_BEGIN,
         BULK_REPLICATION_END,
         REPLICA_REQUEST,
         REPLICA_RESPONSE,
         END_OF_ENUM
      } e;
      const char *name(e param);
      bool        scope(e param);
   }
}


}
}

#endif
