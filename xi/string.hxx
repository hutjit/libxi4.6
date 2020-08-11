// vim:ts=3:sts=3:sw=3

#ifndef XI_STRING_H_
#define XI_STRING_H_

#include <string>
#include "xi/bytes.hxx"

namespace xi {

class String : public Bytes
{
   public :
      static const unsigned int UNIT_SIZE = 32;
      static const int npos = -1;
      // typedef enum {
      //   TRIM_WHITESPACE     = 0x01, // 공백, 탭, 개행문자
      //   TRIM_ALNUM          = 0x02, // alpha, number 
      //   TRIM_NON_ALNUM      = 0x04, // alpha, number가 아닌 모든 문자
      // } eTrimType;
      // TRIM_SINGLE_QUOTED  = 0x02, // "" 인용구
      // TRIM_DOUBLE_QUOTED  = 0x04, // "" 인용구

      String(unsigned int iSize = 0); // buffersize 초기화
      String(const String &rStr);
      String(const std::string &str);
      String(const char *cstr);
      String(const char *cstr, unsigned int iSize);

      bool                 operator==(String &rStr);
      bool                 operator==(const std::string &rStr);
      bool                 operator==(const char *pStr);
      bool                 operator!=(String &rStr);
      bool                 operator!=(const std::string &rStr);
      bool                 operator!=(const char *pStr);

      String              &operator=(const std::string &rStr);
      String              &operator=(const String &rStr);
      String              &operator=(const char *cstr);
      String              &operator=(const char chr);
      String              &operator=(const int16_t nValue);
      String              &operator=(const uint16_t nValue);
      String              &operator=(const int32_t nValue);
      String              &operator=(const uint32_t nValue);
      String              &operator=(const int64_t nValue);
      String              &operator=(const uint64_t nValue);
                         
      String              &operator+=(const String &rStr);
      String              &operator+=(const char *cstr);
      String              &operator+=(const char ch);
      String              &operator+=(short number);
      String              &operator+=(unsigned short number);
      String              &operator+=(int number);
      String              &operator+=(unsigned int number);
      String              &operator+=(long number);
      String              &operator+=(unsigned long number);
      String              &operator+=(float number);
      String              &operator+=(double number);
      char                &operator[](unsigned int index);

      String              &operator<<(const String &right);
      String              &operator<<(const std::string &right);
      String              &operator<<(const bool right);
      String              &operator<<(const char *right);
      String              &operator<<(const unsigned char *right);
      String              &operator<<(const char right);
      String              &operator<<(const unsigned char right);
      String              &operator<<(const float right);
      String              &operator<<(const double right);
      String              &operator<<(const int16_t right);
      String              &operator<<(const uint16_t right);
      String              &operator<<(const int32_t right);
      String              &operator<<(const uint32_t right);
      String              &operator<<(const int64_t right);
      String              &operator<<(const uint64_t right);

      const char          *c_str() const;
      const char          *c_log() const;
      void                 Clear();
      void                 Resize(unsigned int iSize);
      void                 Csnprintf(unsigned int iLength, const char *cfmt, ...);

      int                  Find(char ch, int iOffset = 0) const;
      int                  Find(const String &str, int iOffset = 0) const;
      int                  Find(const char *cstr, int iOffset = 0) const;
      int                  FindLast(char ch, int iOffset = String::npos) const;
      int                  FindLast(const String &str, int iOffset = String::npos) const;
      int                  FindLast(const char *cstr, int iOffset = String::npos) const;

      String               Left(int iLen) const;
      String               Right(int iLen) const;
      String               Mid(int iStart, int iLen = String::npos) const;

      void                 Replace(const char *pTarget, const char *pSubs, bool bAll = true, int iOffset = 0);
      uint32_t             Count(const char ch);

      void                 Assign(const std::string &str);
      void                 Assign(String &str);
      void                 Assign(const char ch);
      void                 Assign(const char *str);
      void                 Assign(const char *str, unsigned int len);
      void                 Assign(const int16_t value);
      void                 Assign(const uint16_t value);
      void                 Assign(const int32_t value);
      void                 Assign(const uint32_t value);
      void                 Assign(const int64_t value);
      void                 Assign(const uint64_t value);

      void                 Append(const std::string &str);
      void                 Append(const String &str);
      void                 Append(const char ch);
      void                 Append(const char *str);
      void                 Append(const char *str, unsigned int len);
      void                 Append(const int16_t value);
      void                 Append(const uint16_t value);
      void                 Append(const int32_t value);
      void                 Append(const uint32_t value);
      void                 Append(const int64_t value);
      void                 Append(const uint64_t value);

      bool                 IsEqual(const char chr) const;
      bool                 IsEqual(const char *pStr) const;
      bool                 IsEqual(const std::string &str) const;
      bool                 IsEqual(String &str) const;
      bool                 IsEqualNoCase(const char *pStr) const;
      bool                 IsPrefixEqual(String &rPrefix);
      bool                 IsSuffixEqual(String &rSuffix);

      void                 LTrim();
      void                 RTrim();
      void                 Trim();
      void                 TrimQuoted();

      void                 LTrimNonAlnum();
      void                 RTrimNonAlnum();
      void                 TrimNonAlnum();

      void                 ToLower();
      void                 ToUpper();

      bool                 IsDigit() const;
      bool                 IsXDigit() const;
      bool                 IsAlnum() const;

      int                  AsInt() const;
      int16_t              AsInt16() const;
      uint16_t             AsUInt16() const;
      int32_t              AsInt32() const;
      uint32_t             AsUInt32() const;
      int64_t              AsInt64() const;
      uint64_t             AsUInt64() const;
};

}

#endif
