// vim:ts=3:sts=3:sw=3
// coding convention : https://google.github.io/styleguide/cppguide.html

#ifndef STACK_WEBSOCKET_MESSAGE_H_
#define STACK_WEBSOCKET_MESSAGE_H_

#include "xi/bytes.hxx"
#include "xi/string.hxx"
#include "xi/socket_addr.hxx"
#include "stack/websocket/define.hxx"


namespace xi {
namespace websocket {


class Message {
   public :
      Message();
      ~Message();

      void Clear();

      void SetRemoteId(xi::String &remote_id);
      void SetRemoteAddr(const xi::SocketAddr &remote_addr);
      void SetRemoteCsModel(websocket::csmod::e model);

      void SetFin(bool flag);
      void SetMask(bool flag);
      void SetOpcode(websocket::opcode::e code);
      void SetPayload(websocket::opcode::e code, const uint8_t *payload, uint32_t length);

      const char *GetRemoteId();
      xi::SocketAddr &GetRemoteAddr();
      websocket::csmod::e GetRemoteCsModel();

      bool GetFin();
      websocket::opcode::e GetOpCode();
      xi::Bytes &Payload();
      const uint8_t *GetPayload();
      uint32_t GetPayloadLength();

      websocket::result::e Encode(bool want_masking, uint8_t *buffer, const uint32_t bufsize, uint32_t &occupied);
      websocket::result::e Decode(bool want_masking, const uint8_t *stream, uint32_t length);
      static websocket::result::e DecodeTest(IN bool want_masking, IN const uint8_t *stream, IN uint32_t length, OUT uint32_t &occupied);

   private :
      xi::SocketAddr remote_addr_;
      xi::String remote_id_; // SocketKey가 설정되지 않았다면 remote_id_로 connection을 찾아 전송한다.
      websocket::csmod::e remote_cs_model_; // remote_id_로 connection을 찾을 때 cs-model이 지정할 수 있다.

      bool fin_;
      websocket::opcode::e opcode_;
      bool mask_;
      xi::Bytes payload_;
      uint32_t mask_key_;
};


}
}
#endif
