// vim:ts=3:sts=3:sw=3

#ifndef XILIB_SPLITTER_H_
#define XILIB_SPLITTER_H_ 

#include <stdint.h>
#include <vector>
#include "xi/bytes.hxx"

namespace xi {


class Splitter
{
   public :
      Splitter();
      Splitter(const char *str, const char delimiter = ' ');
      Splitter(const char *str, const uint32_t len, const char delimiter = ' ');
      ~Splitter();

      void                 Clear();
      uint32_t             GetSize() const;
      bool                 IsEmpty() const;
      const char          *At(uint32_t index) const;
      const char          *operator[](uint32_t index) const;

      bool                 Parse(const char *str, const char delimiter = ' ');
      bool                 Parse(const char *str, const uint32_t len, const char delimiter = ' ');

   private :
      xi::Bytes            data_;
      
      uint32_t             size_;
      std::vector<const char*> container_;
};


}

#endif
