// vim:ts=3:sts=3:sw=3

#ifndef XILIB_INPUT_STRING_CURSOR_H_
#define XILIB_INPUT_STRING_CURSOR_H_

#include <stdint.h>
#include <bitset>
#include "xi/string.hxx"

namespace xi {

class InputStringCursor
{
   public :
      typedef enum {
         SET,
         CUR,
         END
      } seek;

   public :
      InputStringCursor(const char *buffer, uint32_t size);

      bool Read(IN const uint32_t len, OUT uint8_t *buffer);

      bool ReadDigit(xi::String &str);
      bool ReadAlpha(xi::String &str);
      bool ReadAlnum(xi::String &str);

      bool ReadNon(const char nonchar, xi::String &str);
      bool ReadNonBlank(xi::String &str);
      bool ReadNonCrlf(xi::String &str);

      bool Skip(const std::bitset<256> &bs);
      bool Skip(char ch);
      bool SkipAlpha();
      bool SkipAlnum();
      bool SkipBlank();
      bool SkipCrlf();
      bool SkipCr();
      bool SkipLf();
      bool SkipSpace();

      bool SkipNon(const std::bitset<256> &bs);
      bool SkipNon(char nonchar);
      bool SkipNonBlank();
      bool SkipNonCrlf();
      bool SkipNonCr();
      bool SkipNonLf();

      bool ReverseSkipAlnum();

      bool MoveCursor(uint32_t step);
      void Seek(int32_t offset, seek whence);
      const char *Cursor() const;
      uint32_t Used() const;
      uint32_t Remain() const;
      bool End() const;

   private :
      const char *head_;
      const char *tail_;
      const char *cursor_;
};

}

#endif
