// vim:ts=3:sts=3:sw=3

#ifndef XI_BUFFER_CURSOR_H_
#define XI_BUFFER_CURSOR_H_

#include <stdint.h>
#include "xi/string.hxx"

namespace xi {

class OutputStreamCursor
{
   public :
      OutputStreamCursor(uint8_t *buffer, uint32_t size);

      bool Write(const char *buffer);
      bool Write(const char *buffer, uint32_t size);
      bool Write(const uint8_t *buffer, uint32_t size);
      bool Write(const xi::String &str);
      bool WriteToString(int8_t value);
      bool WriteToString(int16_t value);
      bool WriteToString(int32_t value);
      bool WriteToString(int64_t value);
      bool WriteToString(uint8_t value);
      bool WriteToString(uint16_t value);
      bool WriteToString(uint32_t value);
      bool WriteToString(uint64_t value);

      uint8_t *Cursor();
      uint32_t Used();
      uint32_t Remain();
      bool HasError();

   private :
      bool result;

      uint8_t *head_;
      uint8_t *tail_;
      uint8_t *cursor_;
};

}

#endif
