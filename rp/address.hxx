#ifndef XI_RP_ADDRESS_H_
#define XI_RP_ADDRESS_H_

#include "rp/define.hxx"

namespace xi {
namespace rp {

class Address {
   public :
      Address();
      Address(pbgid_t pbgid, sessid_t sessid, membid_t membid);

      void                 Clear();

      pbgid_t              GetPbgId();
      sessid_t             GetSessId();
      membid_t             GetMembId();

      void                 SetPbgId(pbgid_t id);
      void                 SetSessId(sessid_t id);
      void                 SetMembId(membid_t id);

   private :
      pbgid_t              pbg_id_;
      sessid_t             sess_id_;
      membid_t             memb_id_;
};

}
}

#endif
