// vim:ts=3:sts=3:sw=3

#ifndef STACK_HTTP1_CHUNKED_CONTENT_H_
#define STACK_HTTP1_CHUNKED_CONTENT_H_

#include <list>
#include <string>

namespace xi {
namespace h1 {


class ChunkedContent {
   public :
      bool                 Encode(char *pBuf, const int iBufSize, int &iDataLength);
      bool                 Decode(const char *pBuf, int iLength);

      void                 Clear();
      int                  GetSize();
      std::string          operator[](unsigned int index);
      void                 SetFront(const char *pValue);
      void                 SetBack(const char *pValue);

   public :
      ChunkedContent();
      ChunkedContent(char *pBuf);
      ~ChunkedContent();

   private :
      std::list<std::string> chunk_list_;
};


}
}       
#endif
