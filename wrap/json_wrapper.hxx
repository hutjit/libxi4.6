#ifndef WRAP_JSON_WRAPPER_H_
#define WRAP_JSON_WRAPPER_H_

#include "wrap/cJSON.h"
#include "xi/string.hxx"


namespace xi {
   namespace wrap {


class JsonWrapper {
   public :
      class Object {
         public :
            Object();
            Object(cJSON *obj);

            cJSON      *Reference();

            bool        IsValid();
            bool        IsNumber();
            bool        IsString();
            bool        IsArray();
            bool        IsBoolean();

            Object      GetItem(const char *name);
            Object      GetItem(String &name);

            int         GetNumber();
            int         GetInt();
            double      GetFloat();
            const char *GetString();
            int         GetArraySize();
            Object      GetArrayItem(int item);
            bool        GetBoolean();

         private :
            cJSON      *m_Object;
      };

   public :
      JsonWrapper();
      ~JsonWrapper(); 

      void              Clear();
      bool              Parse(const char *value);
      bool              IsValid();

      JsonWrapper::Object GetRoot();

   private :
      DISALLOW_COPY_AND_ASSIGN(JsonWrapper);

   private :
      cJSON            *m_RootObject;
      cJSON            *m_Cursor;
};


   }
}

#endif
