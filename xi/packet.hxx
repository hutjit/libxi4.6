// vim:ts=3:sts=3:sw=3

#ifndef XI_PACKET_H_
#define XI_PACKET_H_ 

#include "xi/define.hxx"
#include "xi/socket_addr.hxx"
#include "xi/string.hxx"

namespace xi {


class Packet : public Bytes {
   public :
      Packet(const uint32_t buffer_size);
      Packet(const uint32_t buffer_size, const uint8_t *buffer, const uint32_t length);
      ~Packet();

      void                 Clear();
      Packet              *Clone();
      Packet              &operator=(const Packet &src);

      void                 SetData(const uint32_t buffer_size, const uint8_t *buffer, const uint32_t length);
      uint32_t             GetDataCursor();
      void                 SetDataCursor(uint32_t cursor);

      bool                 IsTimeout() const;
      bool                 IsTimeout(int timeout) const;
      void                 UpdateTime();
      long                 GetExceedTime() const;
      long                 GetExceedTime(int timeout) const;

      void                 SetRemoteAddr(const SocketAddr &remote_addr);
      void                 GetRemoteAddr(SocketAddr &remote_addr) const;
      const SocketAddr    &GetRemoteAddr() const;
      SocketAddr          &RemoteAddr();

      void                 SetTracelog(String &log);
      const char          *GetTracelog() const;

      void                 SetReserve1(const char *value);
      const char          *GetReserve1() const;

   private :            
      uint32_t             data_cursor_;
      time_t               time_;
      int                  expires_;
      SocketAddr           remote_addr_;
      String               trace_log_;
      String               reserve1_;
};


}

#endif
