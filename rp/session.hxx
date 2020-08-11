#ifndef XI_RP_SESSION_H_
#define XI_RP_SESSION_H_

#include <map>
#include "xi/mutex.hxx"
#include "xi/datetime.hxx"
#include "xi/socket_addr.hxx"
#include "xi/object_input_stream.hxx"
#include "xi/object_output_stream.hxx"
#include "rp/element.hxx"

namespace xi {
namespace rp {

class Payload;
class Member;

typedef std::map<membid_t, Member*> MemberTable;

class Session : public Element {
   public :
      static const unsigned MAX_MEMBER_INDEX = 4;

   public :
      Session(resource_t type);
      virtual ~Session();

      virtual void         Clear();
      bool                 HasMembers();
      virtual result::e    OnReceive(Payload &primitive);
      virtual result::e    Send(Payload &primitive);

      void                 Release();
      void                 Lock();
      void                 Unlock();

      membid_t             Attach(Member *member);
      bool                 Detach(membid_t membid);

      Member              *Find(membid_t membid);

      // redundancy
      bool                 Replicate(IN xi::rp::replica::opcode::e code, IN xi::SocketAddr *addr = NULL);
      virtual bool         Deserialize(IN xi::ObjectInputStream &stream);
      virtual void         OnHaActivate();
      Timespec            &Timestamp();

   private :
      membid_t             NextMemberId();
      uint16_t             MemberSize();

      bool                 ReplicateAlloc(IN xi::rp::replica::opcode::e code, OUT xi::Bytes &buffer);
      bool                 ReplicateFree(OUT xi::Bytes &buffer);

      uint32_t             ReplicaBufferSize();
      bool                 Serialize(OUT xi::ObjectOutputStream &stream);

   protected :
      xi::Mutex            lock_;
                           
   private :
      Timespec             timestamp_;
      membid_t             member_seqno_;
      unsigned             member_index_size_;
      Member              *member_index_[MAX_MEMBER_INDEX]; // MAX_MEMBER_INDEX 이하인 경우 index 방식을 사용하여 접근 성능을 높인다.
      MemberTable          member_table_; // MAX_MEMBER_INDEX 초과일 경우 map을 사용하여 동적관리하여 확장성을 높인다.
};

// RbPool 사용법
// - Obtain은 Manager가 Primitive를 수신하여 처리할 주체를 생성한다.
// - Release는 Session의 Detach에서 처리한다.
}
}

#endif
