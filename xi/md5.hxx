#ifndef XI_MD5_H_
#define XI_MD5_H_

#include <string>
#include "xi/string.hxx"

namespace xi {


class Md5 {
   public :
      static bool Hash(const uint8_t *in_buffer, const uint32_t in_length, xi::String &out_hex);
      static bool Hash(const uint8_t *in_buffer, const uint32_t in_length, std::string &out_hex);
};


}

#endif
