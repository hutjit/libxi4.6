// vim:ts=3:sts=3:sw=3

#ifndef XILIB_OBJECT_OUTPUT_STREAM_H_
#define XILIB_OBJECT_OUTPUT_STREAM_H_

#include <stdint.h>
#include <string>
#include "xi/string.hxx"

namespace xi {


class ObjectOutputStream
{
   public :
      typedef enum {
         SET,
         CUR,
         END
      } seek;

   public :
      ObjectOutputStream(uint32_t buffer_size); // internal memory 사용
      ObjectOutputStream(uint8_t *buffer, uint32_t size); // external memory 사용
      ~ObjectOutputStream();

      bool Write(bool value);
      bool Write(int8_t value);
      bool Write(int16_t value);
      bool Write(int32_t value);
      bool Write(int64_t value);
      bool Write(uint8_t value);
      bool Write(uint16_t value);
      bool Write(uint32_t value);
      bool Write(uint64_t value);
      bool Write(const xi::String &str);
      bool Write(const std::string &str);
      bool Write(const uint8_t *buffer, uint32_t size);

      uint8_t *Cursor();
      void Seek(int32_t offset, seek whence);
      uint32_t Used();
      uint32_t Remain();
      bool HasError();

   private :
      uint32_t internal_size_;
      bool has_error_;

      uint8_t *head_;
      uint8_t *tail_;
      uint8_t *cursor_;
};


}

#endif
