// vim:ts=3:sts=3:sw=3

#ifndef XI_TRANSPORT_H_
#define XI_TRANSPORT_H_ 


#include <list>
#include <memory>
#include "xi/define.hxx"
#include "xi/packet.hxx"
#include "xi/socket.hxx"

namespace xi {

class TransportImp;

class Transport {
   public :
      Transport();
      virtual ~Transport();

      bool              SetConfig(String name, String value);
      String            GetConfig(String name) const;
      bool              ReloadServerCertificate(const char *cert_file, const char *key_file);

      bool              Bind(const std::list<SocketAddr> &bind_set);
      bool              Start();
      bool              Pause();

      bool              Connect(IN const SocketAddr &remote_addr, IN SocketAddr *bind_addr, OUT SocketAddr &assigned_addr);
      bool              Connect(IN std::unique_ptr<Packet> packet, IN SocketAddr *bind_addr, OUT SocketAddr &assigned_addr);
      bool              Send(std::unique_ptr<Packet> packet, xi::ioctrl::e opt = xi::ioctrl::NONE);
      bool              Close(const SocketAddr &addr);
      bool              Exist(const SocketAddr &addr) const;
      bool              SetTrust(const SocketAddr &addr);
      bool              Trusted(const SocketAddr &addr) const;
      bool              Started() const;
      xi::msec_t        GetSendTime(const SocketAddr &addr) const;
      xi::msec_t        GetRecvTime(const SocketAddr &addr) const;
      xi::sostate::e    GetSocketState(const SocketAddr &addr) const;
      bool              Verbose();

      uint32_t          GetSslCtxSize() const;
      SSL_CTX          *GetClientSslCtx(uint32_t index) const;
      SSL_CTX          *GetServerSslCtx(uint32_t index) const;
      bool              GetX509NotAfterDiff(OUT int &day, OUT int &sec) const;

      virtual void      OnNotify(xi::ioevt::e event, SocketAddr &addr) = 0;
      virtual void      OnNotify(xi::ioevt::e event, std::unique_ptr<Packet> packet);
      virtual bool      OnReceive(Socket *socket) = 0;

   private :
      TransportImp     *imp_;
      bool              started_;
};

}
#endif
