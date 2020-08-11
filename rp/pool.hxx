#ifndef XI_RP_POOL_H_
#define XI_RP_POOL_H_

#include <map>

#include "xi/define.hxx"
#include "xi/datetime.hxx"
#include "xi/mutex.hxx"
#include "xi/socket_addr.hxx"
#include "stack/websocket/message.hxx"
#include "rp/element.hxx"

namespace xi {
namespace rp {

class Container;
class PoolReplicator;
class ReplicaFrame;

class Pool {
   public :
      static const unsigned   MAX_TABLE_SIZE = 10; // ~5개 까지는 full scan이 빠르고 ~10까지는 비슷, 그 이상은 map 이 빠르다.

   public :
      Pool();
      ~Pool();

      static Pool            *Instance();
      bool                    StartReplicator(xi::rp::pbgid_t id, const char *bind_ip, uint16_t bind_port, const char *remote_ip, uint16_t remote_port);
      void                    SetHaActive();
      bool                    IsHaActive();

      Element                *Obtain(resource_t type);
      Element                *Find(resource_t type, sessid_t id);
      void                    Release(Element *object);

      void                    Clear();
      bool                    Push(Element *object);
      void                    GetStatus(resource_t type, uint32_t &total, uint32_t &idle, uint32_t &busy);
#ifdef __XI_UNIT_TEST__
      uint32_t                GetStandbyBusyCount(resource_t type);
#endif

      bool                    ActivatedReplica();
      void                    OnReplicaNotify(IN xi::ioevt::e status, IN xi::SocketAddr addr);
      void                    OnReplica(IN xi::websocket::Message &replica);
      bool                    SendReplica(IN xi::websocket::Message &replica);

   private :
      Container              *FindContainer(resource_t type);
      bool                    SendBulkControlPacket(replica::opcode::e code, xi::SocketAddr &addr);
      bool                    SendBulkReplication(IN uint32_t replica_count, IN xi::SocketAddr &addr, OUT bool &completed);
      bool                    SendReplicaResponse(IN xi::SocketAddr &addr, IN ReplicaFrame &request);

   private :
      static xi::Mutex        instance_lock_;
      static Pool            *instance_;

      xi::Mutex               lock_;
      Container              *container_index_[MAX_TABLE_SIZE];
      bool                    ha_active_;

      // redundancy
      xi::String              topology_id_;
      PoolReplicator         *replicator_;

      // bulk replication control
      Timespec                bulk_begin_;
      Timespec                bulk_end_;
      unsigned                bulk_pool_index_;
      sessid_t                bulk_session_index_;
};


}
}

#endif
