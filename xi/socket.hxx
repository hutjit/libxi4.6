// vim:ts=3:sts=3:sw=3

#ifndef XI_SOCKET_H_
#define XI_SOCKET_H_ 

#include <list>
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "xi/socket_addr.hxx"
#include "xi/packet.hxx"
#include "xi/mutex.hxx"

namespace xi {

namespace so_state {
   typedef enum {
      NONE = 0,
      SYN_SENT,
      ESTABLISHED,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

namespace ssl_state {
   typedef enum {
      NONE = 0,
      ACCEPTING,
      CONNECTING,
      ESTABLISHED,
      BROKEN,
      END_OF_ENUM
   } e;
   const char *name(e param);
   bool        scope(e param);
}

class Socket {
   public :
      Socket();       
      ~Socket();      

      SocketAddr          &RemoteAddr();
      indexid_t            GetID() const;
      int                  GetFD() const;
      const char          *GetRemoteIpStr();
      uint16_t             GetRemotePort() const;
      so_state::e          GetState() const;
      ioctrl::e            GetIoctl() const;
      void                 GetRemoteAddr(SocketAddr &remoteAddr);
      SocketAddr          &GetRemoteAddr();
      xi::msec_t           GetCreateTime() const;
      xi::msec_t           GetLastRecvTime() const;
      xi::msec_t           GetLastSendTime() const;
      iptype::e            GetIpType() const;

      bool                 Send(const char *pTag);
      result::e            Recv(const char *pTag, uint32_t iPacketBufferSize);

      void                 SetID(indexid_t socketID);
      void                 SetState(so_state::e state);
      void                 SetIoctl(ioctrl::e opt);
      void                 SetUserParam(uint64_t param);
      int                  SetLinger(int opt, int sec = 2);
      void                 SetRemoteAddr(SocketAddr &remoteAddr);
      void                 SetTrust(bool flag);
      void                 SetLogging(iodebug::e level, color::e send_color);

      bool                 Connect(const char *pTag, const SocketAddr &remoteAddr, const uint32_t nLimit, const char *pLocalIp = NULL);

      void                 UpdateRecvTime();
      void                 UpdateSendTime();
      bool                 Valid() const;
      uint32_t             GetRemainCount() const;
      bool                 Trusted() const;

      Packet              *unsafePopReadingBuf();
      bool                 unsafePushReadingBuf(Packet *pBuf);
      void                 PushSendPacket(Packet *pBuf);
      Packet              *unsafeFrontDeferredMsg();
      Packet              *unsafePopFrontDeferredMsg();

      void                 Clear();
      void                 Close(bool immediate = false);
      void                 SetNotifyAccept(bool value);
      bool                 IsNotifyAccept() const;

      bool                 CreateTlsCtx(const char *tag, SSL_CTX *ctx);
      ssl_state::e         GetTlsState() const;
      void                 SetTlsState(ssl_state::e state);
      ssl_state::e         CheckTlsState(const char *pTag, const char *alpn = NULL);
      bool                 IsServerMode() const;
      bool                 IsTlsSession() const;
      bool                 HasTlsCtx() const;

      const char          *GetPeerCertSubject() const;

   private :           
      bool                 ConnectIPv4(const char *pTag, const uint32_t nLimit, const char *pLocalIp);
      bool                 ConnectIPv6(const char *pTag, const uint32_t nLimit, const char *pLocalIp);

   private :           
      indexid_t            id_;
      SocketAddr           remote_addr_;

      iodebug::e           verbose_level_;
      color::e             send_color_;

      bool                 trusted_;
      bool                 server_mode_;
      xi::msec_t           create_time_;
      xi::msec_t           last_recv_time_;
      xi::msec_t           last_send_time_;
      so_state::e          state_;
      ioctrl::e            ioctrl_;

      Packet              *recv_packet_;
      std::list<Packet *>  send_packet_queue_;
      uint32_t             remain_packet_count_;

      char                 ip_str_[8*sizeof("ffff")];
      bool                 accept_notify_;

      SSL                 *ssl_;
      ssl_state::e         ssl_state_;
      String               peer_cert_subject_;
};

}

#endif // __Socket_H__
