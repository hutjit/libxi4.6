// vim:ts=3:sts=3:sw=3

#ifndef XI_CLI_BRIDGE_H_
#define XI_CLI_BRIDGE_H_ 

#include <map>
#include <string>
#include "xi/socket_addr.hxx"
#include "xi/tl1command.hxx"

namespace xi {
namespace cli {

typedef uint64_t context_t;

class Parameters
{
   public :
      Parameters();

      xi::SocketAddr       bind_addr_;
      std::string          banner_;
      std::string          prompt_;
      std::string          help_msg_;
      uint32_t             session_pool_size_;
      std::map<std::string, std::string> login_accounts_;
};

class CliImpl;

class Bridge
{
   public :
      Bridge();
      ~Bridge();

      bool                 Initialize(Parameters &param);
      bool                 Start();

      virtual bool         OnCommand(context_t ctx, xi::Tl1Command &tl1cmd) = 0;
      virtual std::string  OnShowInterval(context_t ctx, unsigned id) = 0;

      bool                 SetShowIntervalName(unsigned id, const char *name); // [0 .. 9]
      bool                 ScheduleShowInterval(context_t ctx, unsigned id, time_t interval);
      bool                 CancelShowInterval(context_t ctx, unsigned id);

      bool                 ShowPrompt(context_t ctx);
      bool                 ShowHelpMsg(context_t ctx);
      bool                 ShowMessage(context_t ctx, const char *msg);
      std::string          Uptime();

   private :
      CliImpl             *impl_;
};


}
}

#endif
