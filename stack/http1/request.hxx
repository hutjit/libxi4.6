// vim:ts=3:sts=3:sw=3

#ifndef STACK_HTTP1_REQUEST_H_
#define STACK_HTTP1_REQUEST_H_

#include <memory>
#include "xi/socket_addr.hxx"
#include "stack/http1/define.hxx"

namespace xi {
namespace h1 {


class Message;

class Request {
   public :
      friend class SessionManager;

   public :
      Request(const char *httpstr, const uint32_t strlen);
      Request(const char *url, xi::h1::method::e method = xi::h1::method::GET);
      Request(xi::h1::method::e method, const char *scheme, const char *path, const char *authority);
      ~Request();

      Request                &operator=(const Request &src);
      Request                *Clone() const;
      bool                    HasError() const;

      xi::msec_t              GetSentTime() const;
      void                    SetSentTime(xi::msec_t time);
      const xi::SocketAddr   &GetSocketAddr() const;
      void                    SetSocketAddr(const xi::SocketAddr &addr);
      uint64_t                GetUserParam() const;
      void                    SetUserParam(uint64_t param);

      const char             *GetHttpVersion() const;
      void                    SetHttpVersion(const char *ver);
      xi::h1::method::e       GetMethod() const;
      void                    SetMethod(xi::h1::method::e method);
      const char             *GetPath() const;
      void                    SetPath(const char *path);
      uint32_t                GetQueryParamsSize() const;
      const char             *GetQueryParamsName(const uint32_t index) const;
      const char             *GetQueryParamsValue(const uint32_t index) const;
      const char             *GetQueryParamsValue(const char *name) const;
      bool                    AddQueryParams(const char *name, const char *value);
      bool                    AddQueryParams(const char *name, uint32_t nlen, const char *value, uint32_t vlen);
      bool                    RemoveParams(const uint32_t index);
      bool                    RemoveParams(const char *name);

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
      Request();
      Request(std::unique_ptr<xi::h1::Message> primitive);
      Message                *Release();
      Message                *impl_;
      bool                    has_error_;
      xi::msec_t              sent_time_;
};


}
}

#endif
