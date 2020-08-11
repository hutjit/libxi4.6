#ifndef XI_RP_MEMBER_H_
#define XI_RP_MEMBER_H_

#include "rp/element.hxx"

namespace xi {
namespace rp {


class Session;
class Payload;

class Member : public Element {
   public :
      Member(resource_t type);
      virtual ~Member();

      virtual void         Clear();
      virtual result::e    OnReceive(Payload &primitive);
      virtual result::e    Send(Payload &primitive);

      void                 Grouping(Session *parent, membid_t id);
      Session             *GetSession();
      sessid_t             GetSessionIndex();
      sessid_t             GetSessionId();
      membid_t             GetMemberId();

      // redundancy
      void                 Replicate();
      virtual uint32_t     SerializeSize();
      virtual bool         Serialize(xi::ObjectOutputStream &stream);
      virtual bool         Deserialize(xi::ObjectInputStream &stream);
      virtual void         OnHaActivate();

   protected :
      membid_t             id_;
      Session             *parent_;
};


}
}

#endif
