// vim:ts=3:sts=3:sw=3

#ifndef STACK_HTTP1_RESPONSE_H_
#define STACK_HTTP1_RESPONSE_H_

#include <memory>
#include "xi/socket_addr.hxx"
#include "stack/http1/define.hxx"

namespace xi {
namespace h1 {


class Message;
class Request;

class Response {
   public :
      friend class SessionManager;

   public :
      Response(const char *httpstr, const uint32_t strlen);
      Response(const Request &req, uint16_t status_code);
      ~Response();

      Response               &operator=(const Response &src);
      Response               *Clone() const;
      bool                    HasError() const;

      const xi::SocketAddr   &GetSocketAddr() const;
      void                    SetSocketAddr(const xi::SocketAddr &addr);
      uint64_t                GetUserParam() const;
      xi::h1::method::e       GetRequestMethod() const;

      const char             *GetHttpVersion() const;
      void                    SetHttpVersion(const char *ver);
      uint16_t                GetStatusCode() const;
      void                    SetStatusCode(uint16_t code, const char *phrase = NULL);
      const char             *GetReasonPhrase() const;
      void                    SetReasonPhrase(const char *phrase);

      uint32_t                GetHeaderSize() const;
      const char             *GetHeaderName(const uint32_t index) const;
      const char             *GetHeaderValue(const uint32_t index) const;
      const char             *GetHeaderValue(const char *name) const;
      bool                    AddHeader(const char *name, const char *value);
      bool                    AddHeader(const char *name, uint32_t nlen, const char *value, uint32_t vlen);
      bool                    RemoveHeader(const uint32_t index);
      bool                    RemoveHeader(const char *name);

      const uint8_t          *GetPayload() const;
      uint32_t                GetPayloadSize() const;
      void                    SetPayload(const uint8_t *data, const uint32_t len);
      void                    RemovePayload();

      const char             *ToString();

   private :
      Response();
      Response(std::unique_ptr<xi::h1::Message> primitive);
      Message                *Release();
      Message                *impl_;
      bool                    has_error_;
};


}
}

#endif
