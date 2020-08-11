// vim:ts=3:sts=3:sw=3

#ifndef XI_UTIL_H_
#define XI_UTIL_H_ 

#include <string>
#include <bitset>

#include "xi/define.hxx"
#include "xi/string.hxx"

namespace xi {


const char *Version();

inline bool IsZero(const char *s) { if (NULL == s) return true; if (0 == *s) return true; return false; }
inline bool IsZero(const unsigned char *s) { if (NULL == s) return true; if (0 == *s) return true; return false; }

void Uuid(String &rStr);
void Sleep(unsigned int msec);
inline msec_t CurrentTime()
{
   struct timespec now;
   clock_gettime(CLOCK_REALTIME, &now);
   return (((msec_t)now.tv_sec)*1000) + (((msec_t)now.tv_nsec)/1000000) ; // Millisecond
}

inline msec_t MonotonicTime() // 단조시계(부팅후 시간)
{
   struct timespec now;
   clock_gettime(CLOCK_MONOTONIC, &now);
   return (((msec_t)now.tv_sec)*1000) + (((msec_t)now.tv_nsec)/1000000) ; // Millisecond
}

int Timezone();
int ReloadTimezone();
               
void LTrim(char *pStr);              // ' '
void RTrim(char *pStr);              // ' '
void Trim(char *pStr);               // ' '
               
void LTrimBlank(char *pStr);         // ' ', '\r', '\n', '\t'
void RTrimBlank(char *pStr);         // ' ', '\r', '\n', '\t'
void TrimBlank(char *pStr);          // ' ', '\r', '\n', '\t'
               
const char *SkipSpace(const char *pStr);    // ' '
const char *SkipNonSpace(const char *pStr); // ' '
const char *SkipBlank(const char *pStr);    // ' ', '\r', '\n', '\t'
const char *SkipNonBlank(const char *pStr); // ' ', '\r', '\n', '\t'
const char *SkipNonAlnum(const char *pStr);
const char *SkipAlnum(const char *pStr);
const char *SkipDigit(const char *pStr);    // '0' ~ '9'

std::bitset<256>  Bitset(const char *str);
const char *Skip(const char *pStr, const std::bitset<256> &cs);
const char *SkipToOneOf(const char *pStr, const std::bitset<256> &cs);
                
char ToLower(char ch);
char ToUpper(char ch);
                
bool StrEqual(const char *src, const char *dst);
bool StrEqualNoCase(const char *src, const char *dst);
bool PrefixEqual(const char *src, const char *prefix);
bool PrefixEqualNoCase(const char *src, const char *prefix);
int Strcmp(const char *left, const char *right);
                
uint32_t SuperFastHash(const void *pStr, unsigned int bytelen);
uint16_t Crc16ccitt(const unsigned char *buf, int len);

//time_t Str2Time(const char *datetime); // format : YYYYMMDDHH24MISS

//int UlimitCORE();
//int UlimitOpenFile(int iLimit);
                 
void UriEncode(IN const char *pSrc, OUT String &out);
void UriDecode(IN const char *pSrc, OUT String &out);
void Hex2Dec(IN const char *pSrc, OUT String &out);


xi::result::e SetNonBlock(int fd);
xi::result::e SetBlock(int fd);
xi::result::e SetTcpNodelay(int fd);
int SetReuseAddr(int fd);
int SetTcpNoDelay(int fd);
   // cp socket 의 경우, 기본적으로 Nagle 알고리즘을 사용한다.
   // Nagle 알고리즘은 전송의 효율을 위해, 적은 데이터를 모아서 큰 패킷으로 한번에 보내는 방식이다. 
   // 따라서 적은 양의 데이터가 자주 발생되는 시스템에서는 반응속도가 느려질 수 있다.
   // 이를 해결하기 위해 TcpNoDelay 를 해주면 Nagle 알고리즘이 해제되면서, 패킷이 준비되면 바로 보내게 된다.
int SetKeepAlive(int fd);
int SetLingerOption(int fd, int opt, int sec = 5); // default : 5 Sec
   // 소켓 종료 시 버퍼의 처리 방법에 대해 정의하는 것이지만, 일반적으로는 close 함수의 행동에 대해 정의한다고 생각하면 된다.
   // opt[0] : l_onoff가 0이면 기본적인 TCP로 동작한다.
   // opt[1] : l_onoff가 0이 아니고 l_linger가 0이면 close 할 때 버퍼에 남아있는 내용은 버리고 연결을 끊어버린다.
   // opt[2] : l_onoff가 0이 아니고 l_linger가 0이 아니라면, close 할 때 l_linger 시간만큼(초단위)을 기다린 뒤, 
   //          그때까지 버퍼가 처리되지 않으면 연결을 끊는다.

int ListenTCP(const char *ip, const unsigned int port, int backlog = 5);


int GetIpAddr(const char *pHost);
bool GetIpAddr(IN const char *host, IN const char *service, xi::String &ipstr);

int GetSNDBUF(int fd);
int GetRCVBUF(int fd);
int SetSNDBUF(int fd, int iSize);
int SetRCVBUF(int fd, int iSize);

bool IsIPv4(const char *pIP);
bool IsIPv6(const char *pIP);

bool GetIfaddr(const char *ifaddrname, String &rIp);

bool GetMacAddr(const char *ifname, String &rMac);

bool CreatePidFile(const char *filename);
bool DeletePidFile(const char *filename);

bool CanLogging(unsigned level);
void SetLoggingLevel(unsigned level);
void SetLoggingLLT(bool onoff);
void SetLoggingCallbacks(normal_logging_callback nl, verbose_logging_callback vl, llt_logging_callback ll);
void SetLoggingFile(const char *filename);
void SetLoggingStdout();
void SetLoggingRetentionCount(unsigned int count);
void SetLoggingSegmentBytes(unsigned int bytes);


}

#endif // AXUTIL_H
