// vim:ts=3:sts=3:sw=3

#ifndef XI_SHA512_H_
#define XI_SHA512_H_

#include <string>
#include "xi/string.hxx"

namespace xi {

class Sha512 {
   public :
      static bool Hash(const uint8_t *in_buffer, const uint32_t in_length, xi::String &out_hex);
      static bool Hash(const uint8_t *in_buffer, const uint32_t in_length, std::string &out_hex);
};

}

#endif
