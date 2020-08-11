#ifndef XI_RP_ELEMENT_H_
#define XI_RP_ELEMENT_H_

#include "xi/string.hxx"
#include "xi/object_input_stream.hxx"
#include "xi/object_output_stream.hxx"
#include "rp/define.hxx"

namespace xi {
namespace rp {


class Payload;
class Container;

class Element {
   public :
      Element(resource_t type, bool type_member, bool ha_state = false);
      virtual ~Element();

      resource_t           GetType();
      sessid_t             GetSessionId();

      void                 NextTurn();
      Container           *GetParent();
      void                 SetParent(Container *parent);
      sessid_t             GetIndex() const;
      void                 SetIndex(sessid_t id);
      static sessid_t      CalcIndex(sessid_t id);
      static uint8_t       CalcTurn(sessid_t id);
      uint8_t              GetSeqNumber();
      void                 SetSeqNumber(uint8_t value);

      virtual void         Clear() = 0;
      virtual result::e    OnReceive(Payload &primitive) = 0;
      virtual result::e    Send(Payload &primitive) = 0;

      // redundancy
      virtual bool         Deserialize(xi::ObjectInputStream &stream) = 0;
      virtual void         OnHaActivate() = 0;
      bool                 IsHaActivated();
      void                 SetHaActivated();
      bool                 IsMember();

   private :
      Container           *parent_;
      resource_t           type_;
      sessid_t             id_;
      uint8_t              turn_;
      bool                 ha_active_;
      bool                 type_member_;
};


}
}

#endif
