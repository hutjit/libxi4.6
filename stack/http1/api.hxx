// vim:ts=3:sts=3:sw=3
// coding convention : https://google.github.io/styleguide/cppguide.html

#ifndef STACK_HTTP1_API_H_
#define STACK_HTTP1_API_H_ 

#include "xi/thread_pool.hxx"
#include "stack/http1/request.hxx"
#include "stack/http1/response.hxx"

namespace xi {
namespace h1 {


class SessionManager;

class Parameters {
   public :
      Parameters();

      unsigned int      thread_count_;
      xi::ThreadPool   *thread_pool_;

      std::list<SocketAddr> bind_list_;
      unsigned int      io_thread_size_;
      unsigned int      authtimeout_;
      uint32_t          default_packet_size_;

      xi::String        ca_cert_path_;
      xi::String        client_cert_path_;
      xi::String        client_key_path_;
      xi::String        server_cert_path_;
      xi::String        server_key_path_;
      bool              tls_sesscache_off_;
      bool              tls_verify_peer_;

      uint32_t          keep_alive_timeout_;
      uint32_t          keep_alive_max_;
};

class Api {
   public :
      Api();
      virtual ~Api();

      bool              Initialize(const xi::h1::Parameters &cfg);
      const char       *Version();
      bool              Start();

      uint32_t          GetKeepAliveTimeout() const;
      uint32_t          GetKeepAliveMax() const;
      bool              SetKeepAliveTimeout(const uint32_t timeout);
      bool              SetKeepAliveMax(const uint32_t max);
      bool              ReloadServerCertificate(const char *cert_file, const char *key_file);

      bool              Close(const xi::SocketAddr &addr);
      bool              Exist(const xi::SocketAddr &addr) const;
      bool              Connect(IN std::unique_ptr<xi::h1::Request> request, OUT xi::SocketAddr &allocated, IN xi::SocketAddr *bind = NULL);
      bool              Send(IN std::unique_ptr<xi::h1::Request> request);
      bool              Send(IN std::unique_ptr<xi::h1::Response> response, IN xi::ioctrl::e sendopt = xi::ioctrl::NONE);
      virtual void      OnNotify(xi::ioevt::e status, xi::SocketAddr &addr) = 0;
      virtual void      OnReceive(std::unique_ptr<xi::h1::Request> request) = 0;
      virtual void      OnReceive(std::unique_ptr<xi::h1::Response> response) = 0;
      virtual void      OnSendFail(std::unique_ptr<xi::h1::Request> request) = 0;
                          
      std::string       DebugStat();

   private :              
      SessionManager   *tl_;
};


}
}

#endif
