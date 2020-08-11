// vim:ts=3:sts=3:sw=3

#ifndef XI_PARAMS_H_
#define XI_PARAMS_H_ 

#include <list>
#include "xi/string.hxx"

namespace xi {

class Params
{
   public :
      class Param {
         public :
            Param()           { ExistValue = false; }

            String          Name;
            String          Value;
            bool              ExistValue;
      };

      typedef std::list<Param>::iterator Iterator;
   public :
      Params();
      Params(const char *pStr, bool isTrim = false);
      Params(const char *pStr, const char ParamDelimiter, const char NameDelimiter, bool isTrim = false);
      ~Params();

      bool                  Parse(const char *pStr, bool isTrim = false);
      bool                  Parse(const char *pStr, const char ParamDelimiter, const char NameDelimiter, bool isTrim = false);

      void                  Clear();
      bool                  IsEmpty();
      unsigned int          GetSize();
      Param                *GetAt(unsigned int idx);
      const char           *GetValue(const char *pName);

      Iterator              Begin();
      Iterator              End();
      void                  Erase(Iterator it);
      void                  PushFront(Param el);
      void                  PushBack(Param el);


      String              ToString();
      bool                  Encode(char *pBuf, const int bufsize, int &datasize);

      void                  SetParamDelimiter(char value);
      void                  SetNameDelimiter(char value);

   private :
      char                  m_ParamDelimiter;
      char                  m_NameDelimiter;

      std::list<Param>      m_Params;
};

}

#endif
