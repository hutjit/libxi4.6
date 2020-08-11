#ifndef XI_RP_PAYLOAD_H_
#define XI_RP_PAYLOAD_H_

#include "rp/address.hxx"

namespace xi {
namespace rp {

class Session;

class Payload {
   public :
      Payload(payload_t type);
      virtual ~Payload();

      payload_t            GetType();

      Session             *GetSessReference();
      void                 SetSessReference(Session *pSession);

      Address             &GetSrcAddr();
      Address             &GetDstAddr();

      void                 SetSrcAddr(Address &addr);
      void                 SetDstAddr(Address &addr);

      pbgid_t              GetSrcPbgId();
      sessid_t             GetSrcSessId();
      membid_t             GetSrcMembId();

      void                 SetSrcPbgId(pbgid_t id);
      void                 SetSrcSessId(sessid_t id);
      void                 SetSrcMembId(membid_t id);

      pbgid_t              GetDstPbgId();
      sessid_t             GetDstSessId();
      membid_t             GetDstMembId();

      void                 SetDstPbgId(pbgid_t id);
      void                 SetDstSessId(sessid_t id);
      void                 SetDstMembId(membid_t id);

      virtual Payload     *Clone() = 0;

   protected :               
      payload_t            type_;

      Address              src_addr_;
      Address              dst_addr_;
      Session             *session_ref_;
};

}
}

#endif
