// vim:ts=3:sts=3:sw=3

#ifndef XI_SOCKET_ADDR_H_
#define XI_SOCKET_ADDR_H_

#include <arpa/inet.h>
#include "xi/define.hxx"

namespace xi {

class SocketAddr {
   public :
      SocketAddr();
      ~SocketAddr();

      void                    Clear();

      socketkey_t             GetSocketKey() const;
      bool                    CheckSocketKey() const;
      indexid_t               GetSocketID() const;
      void                    SetSocketID(indexid_t socketID);
      int                     GetFD() const;
      void                    SetFD(int fd);
      uint16_t                GetPort() const;
      void                    SetPort(uint16_t port);
      uint16_t                GetLocalPort() const;
      void                    SetLocalPort(uint16_t port);
      const char             *GetIpStr(char *dst, socklen_t size) const;
      bool                    GetSockaddr(struct sockaddr_in *addr) const;
      bool                    GetSockaddr(struct sockaddr_in6 *addr) const;
      void                    SetSockaddr(struct sockaddr_in *addr);
      void                    SetSockaddr(struct sockaddr_in6 *addr);

      iptype::e               GetIpType() const;
      bool                    SetIpType(iptype::e value);
      ipver::e                GetIpVer() const;

      bool                    SetIpPort(const char *ip, uint16_t port);
      bool                    SetHostPort(const char *host, uint16_t port);

      uint64_t                GetUserParam() const;
      void                    SetUserParam(uint64_t param);

      bool                    operator==(const SocketAddr &src) const;
      bool                    operator!=(const SocketAddr &src) const;

      bool                    IsInAddrAny() const;
      static bool             IsIPv4(const char *ip);
      static bool             IsIPv6(const char *ip);

   private :
      int32_t                 socket_fd_;
      indexid_t               socket_id_;

      ipver::e                ip_version_;
      iptype::e               ip_type_;
      union {
         in_addr  ip4;
         in6_addr ip6;
      }                       remote_addr_;
      uint16_t                remote_port_;
      uint16_t                local_port_;

      uint64_t                user_param_;

      // IPv4 32bit   ex) 192.168.0.1, 3*4+3=15
      // IPv6 128bit  ex) 2001:0db8:85a3:08d3:1319:8a2e:0370:7334, 4*8+7=39
      //char m_ipStr[sizeof("255.255.255.255")];    // only IPv4 supported
      //char m_portStr[sizeof("65536")];
};

// ===========================================================================
// IPv4
// ---------------------------------------------------------------------------
// <bits/sockaddr.h>
// typedef unsigned short int sa_family_t;
//
// <linux/in.h>
// struct in_addr {
//    __be32  s_addr;
// };
//
// #define __SOCK_SIZE__   16      /* sizeof(struct sockaddr)  */
// struct sockaddr_in {
//   sa_family_t        sin_family; /* Address family       */
//   __be16             sin_port;   /* Port number          */
//   struct in_addr     sin_addr;   /* Internet address     */
// 
//   /* Pad to size of `struct sockaddr'. */
//   unsigned char      __pad[__SOCK_SIZE__ - sizeof(short int) - sizeof(unsigned short int) - sizeof(struct in_addr)];
// };

// ===========================================================================
// IPv6
// ---------------------------------------------------------------------------
// <linux/in6.h>
//
// struct in6_addr
// {
//    union
//    {
//       __u8             u6_addr8[16];
//       __be16           u6_addr16[8];
//       __be32           u6_addr32[4];
//    } in6_u;
// #define s6_addr        in6_u.u6_addr8
// #define s6_addr16      in6_u.u6_addr16
// #define s6_addr32      in6_u.u6_addr32
// };
// 
// struct sockaddr_in6 {
//    unsigned short int  sin6_family;    /* AF_INET6 */
//    __be16              sin6_port;      /* Transport layer port # */
//    __be32              sin6_flowinfo;  /* IPv6 flow information */
//    struct in6_addr     sin6_addr;      /* IPv6 address */
//    __u32               sin6_scope_id;  /* scope id (new in RFC2553)[인터페이스 인덱스 아이디] */
// };

}

#endif // XI_SOCKETADDR_H_
