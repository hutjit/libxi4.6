// vim:ts=3:sts=3:sw=3

#ifndef XILIB_OBJECT_INPUT_STREAM_H_
#define XILIB_OBJECT_INPUT_STREAM_H_

#include <stdint.h>
#include <bitset>
#include <string>
#include "xi/string.hxx"

namespace xi {

class ObjectInputStream
{
   public :
      typedef enum {
         SET,
         CUR,
         END
      } seek;

   public :
      ObjectInputStream(const uint8_t *buffer, uint32_t size); // external memory 사용

      bool Read(OUT bool &value);
      bool Read(OUT int8_t &value);
      bool Read(OUT int16_t &value);
      bool Read(OUT int32_t &value);
      bool Read(OUT int64_t &value);
      bool Read(OUT uint8_t &value);
      bool Read(OUT uint16_t &value);
      bool Read(OUT uint32_t &value);
      bool Read(OUT uint64_t &value);
      bool Read(OUT xi::String &str);
      bool Read(OUT std::string &str);
      bool Read(IN const uint32_t len, OUT uint8_t *buffer);

      const uint8_t *Cursor();
      void Seek(int32_t offset, seek whence);
      uint32_t Used();
      uint32_t Remain();
      bool HasError();

   private :
      bool has_error_;

      const uint8_t *head_;
      const uint8_t *tail_;
      const uint8_t *cursor_;
};

}

#endif
