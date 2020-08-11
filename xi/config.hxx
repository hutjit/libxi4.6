// vim:ts=3:sts=3:sw=3

#ifndef XI_CONFIG_H_
#define XI_CONFIG_H_

#include <map>
#include <string>


// ============================================================================
// Reference [ SIP ]
// ----------------------------------------------------------------------------
//   alphanum = ALPHA / DIGIT
//   reserved = ";" / "/" / "?" / ":" / "@" / "&" / "=" / "+" / "$" / ","
// 
// unreserved = alphanum / mark
//       mark = "-" / "_" / "." / "!" / "?" / "*" / "’" / "(" / ")"
// 
//    escaped = "%" HEXDIG HEXDIG
// 
// separators = "(" / ")" / "<" / ">" / "@" / "," / ";" / ":" / "\\" / DQUOTE / "/" / "[" / "]" / "?" / "=" / "{" / "}" / SP / HTAB
// ----------------------------------------------------------------------------


// ============================================================================
// #### Basic Rules #####
// ----------------------------------------------------------------------------
//   alphanum = ALPHA / DIGIT
//       mark = "-" / "_" / "." / "!" / "?" / "*"
// ----------------------------------------------------------------------------
//     Secion = alphanum / mark
//       name = alphanum / mark
//      value = 
// ----------------------------------------------------------------------------
// 주석 = '#'
// ----------------------------------------------------------------------------

namespace xi {

class Config
{
   public :
      typedef enum {
         Success,
         FileNotExist,
         FilePermissionDeny,
         FileOpenFail,
         MemoryNull,
         ParseFail,
         Error
      } ResultType;

      class Section 
      {
         public :
            Section();
            ~Section();

            int                     GetParamCount();
            void                    AddParam(std::string name, std::string value);
            std::string             GetValue(std::string name);

            std::string             GetName(int index);   // index: 0 부터 시작
            std::string             GetValue(int index);  // index: 0 부터 시작

            void                    Clear();

         private :
            std::map<std::string, std::string>     m_Params;
      };

   public :
      Config();
      ~Config();

      ResultType      LoadFile(const char *pFilename);
      ResultType      LoadMemory(const char *pString);
      Section         GetSection(std::string sSection);
      Section         GetSection(int index);            // index: 0 부터 시작
      std::string     GetSectionName(int index);        // index: 0 부터 시작
      int             GetSectionCount();

      void            Clear();

   private :
      bool            ParseFromFP(FILE *pFP);
      bool            ParseFromMemory(const char *pString);
      bool            IsValidName(const char *pName);
      bool            ParseNameValue(const char *pLine, std::string &name, std::string &value);

   private :
      std::map<std::string, Section>        m_Sections;
};

}

#endif

