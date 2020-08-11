// vim:ts=3:sts=3:sw=3

#ifndef XI_RANDOM_H_
#define XI_RANDOM_H_

#include <stdint.h>

namespace xi {

// WELL은 위 MT의 디자이너가 10년후에 고안한 난수 발생 알고리즘 입니다.
// 그의 주장에 따르면 MT보다 40% 빠르고 코드도 더 간단합니다.
// WELL은 분포도에 따라서 WELL512, WELL1024, WELL19947, WELL44497의 종류가 있습니다.
// source code : http://www.iro.umontreal.ca/~panneton/WELLRNG.html

class Random {
   public :
      Random();
      Random(uint32_t seed);
      ~Random();

      void           Seed(uint32_t seed);
      uint32_t       operator()();

   private :
      uint32_t       state_[16];
      uint32_t       index_;
};

}

#endif
