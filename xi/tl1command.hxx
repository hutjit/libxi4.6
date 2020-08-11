// vim:ts=3:sts=3:sw=3

#ifndef XI_TL1_COMMAND_H_
#define XI_TL1_COMMAND_H_ 

#include <list>
#include <string>
#include "xi/string.hxx"
#include "xi/input_string_cursor.hxx"

namespace xi {

// # General Input Command Format
// <Command Code Block> [:Staging Parameter Blocks] : [Data Blocks(Name-Defined Parameters)];
//
// ## Command Code Block
// <verb>[-<modifier>[-<modifier>]]
//
// ## Staging Parameter Blocks
// :[<tid>] : Target Identifier
//
// ## Name-Defined Parameters
// :<name>[=<value>]
// example) :SETPR=4,MAXHOP=2,PROTTYPE=1forn or :STS-7-3,FAC-3,SCRIPT=TC1
//
// ## Semi-colon Character
// The semi-colon character (;) terminates a TL1 input message.

class Tl1Command
{
   public :
      bool              Parse(const char *stream, const uint32_t length, const uint32_t staging_blocks);
                      
      void              Clear();
      const char       *Command() const;
      const char       *Staging(const uint32_t index) const; // 0 base
      uint32_t          StagingBlockSize() const;
      const char       *Data(const char *key, bool sensitive = false) const;
      const char       *DataName(const uint32_t index) const; // 0 base
      const char       *DataValue(const uint32_t index) const; // 0 base
      uint32_t          DataBlockSize() const;
                      
   private :          
      bool              ParseNameDefinedParameters(InputStringCursor &cursor);

   private :          
      xi::String        command_;
      std::list<xi::String> staging_blocks_;
      std::list<std::pair<xi::String, xi::String> > data_blocks_;
};


}

#endif
