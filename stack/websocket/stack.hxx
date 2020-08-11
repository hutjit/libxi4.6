// vim:ts=3:sts=3:sw=3
// coding convention : https://google.github.io/styleguide/cppguide.html

#ifndef STACK_WEBSOCKET_STACK_H_
#define STACK_WEBSOCKET_STACK_H_

#include <list>
#include <map>
#include <set>
#include "xi/thread_pool.hxx"
#include "stack/websocket/message.hxx"

namespace xi {
namespace websocket {


class TransportManager;

class RemoteAddr {
   public :
      RemoteAddr();

      xi::String id_; // SocketKey가 없을 경우 connection을 찾기 위한 ID로 사용
      xi::String host_;
      uint16_t port_;
      xi::String resource_name_;
      std::map<std::string, std::string> extra_headers_; // map<header, value>
};

class Parameters {
   public :
      Parameters();

      std::list<xi::SocketAddr> bind_list_;
      unsigned int            thread_count_;
      xi::ThreadPool         *thread_pool_;
      unsigned int            authtimeout_;
      uint32_t                default_packet_size_;

      xi::String              ca_cert_path_;
      xi::String              client_cert_path_;
      xi::String              client_key_path_;
      xi::String              server_cert_path_;
      xi::String              server_key_path_;
      bool                    tls_sesscache_off_;
      bool                    tls_verify_peer_;

      std::list<RemoteAddr>   remote_addr_list_;
      xi::String              client_id_;
      xi::SocketAddr          client_bind_ip_;

      std::set<std::string>   accept_while_list_;
};

class Stack {
   public :
      Stack();
      virtual ~Stack();

      bool Initialize(xi::websocket::Parameters &param);
      bool Start();

      virtual void OnReceive(xi::websocket::Message &message) = 0;
      virtual void OnNotify(xi::ioevt::e status, xi::SocketAddr &addr, const char *http_request) = 0;
      bool Send(xi::websocket::Message &message);
      bool Exist(SocketAddr &addr);
      bool Close(SocketAddr &addr);

   private :
      TransportManager *transport_;
};


}
}
#endif
