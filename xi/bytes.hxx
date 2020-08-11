// vim:ts=3:sts=3:sw=3

#ifndef XILIB_BYTES_H_
#define XILIB_BYTES_H_

#include "xi/define.hxx"

namespace xi {


class Bytes 
{
   public :
      static const unsigned int UNIT_SIZE = 32;

   public :
      Bytes(const uint32_t reserve = 0);
      Bytes(const uint8_t *data, const uint32_t size);
      Bytes(const uint32_t reserve, const uint8_t *data, const uint32_t size);
      ~Bytes();

      void Clear(); 
      bool IsEmpty() const;
      void Reserve(const uint32_t size);
      void Resize(const uint32_t size);
      void Assign(const uint32_t reserve, const uint8_t *data, const uint32_t size);
      void Append(const uint8_t *data, unsigned int size);

      uint8_t *GetData() const;
      uint32_t GetSize() const;
      uint32_t GetReserve() const;

      Bytes &operator=(const Bytes &rBA);
      bool operator==(const Bytes &rBA);
      bool operator!=(const Bytes &rBA);
      Bytes *Clone();

      // hex encode/decode
      const char *ConvByte2Hex(const uint8_t *pSrc, uint32_t size);
      void ConvHex2Byte(const char *pSrc, uint32_t size);

      // base64 encode/decode
      bool Base64Encode(const uint8_t *pSrc, uint32_t size, bool padding = true);
      bool Base64Decode(const uint8_t *pSrc, uint32_t size);

      // percent encode/decode
      // - https://en.wikipedia.org/wiki/Percent-encoding
      void PercentEncode(const char *src, uint32_t len);
      void PercentDecode(const char *src, uint32_t len);

   protected :
      uint8_t *pointer_;
      uint32_t reserve_;
      uint32_t size_;
};


}

#endif
