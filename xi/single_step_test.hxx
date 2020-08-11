// vim:ts=3:sts=3:sw=3:expandtab

#ifndef XI_SINGLE_STEP_TEST_H_
#define XI_SINGLE_STEP_TEST_H_

#include <tbb/atomic.h>

namespace xi {

class SingleStepTest {
   public :
      SingleStepTest();
      ~SingleStepTest();

      void Block(unsigned int step); // step_ 의 값을 설정한다.
      bool Blocked(); // Blocking()에서 대기여부 리턴
      void Blocking(unsigned int step); // step_ != step 이 될때까지 Blocking()에서 대기한다.
      unsigned int Step();

   private :
      tbb::atomic<unsigned int> step_;
      tbb::atomic<bool> blocked_;
};

}

#endif

