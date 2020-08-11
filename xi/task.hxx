// vim:ts=3:sts=3:sw=3

#ifndef XI_TASK_H_
#define XI_TASK_H_ 

namespace xi {

class Task
{
   public:
      virtual ~Task() {}
      virtual void Exec() = 0;
};

template<class T>
class TaskWithoutParam : public Task {
   public:
      TaskWithoutParam(T *obj, void (T::*func)()) : object_(obj), funcion_(func) {}
      virtual void Exec() { (object_->*funcion_)(); }

   private:
      T *object_;
      void (T::*funcion_)();
};

template<class T, class P>
class TaskWithParam : public Task {
   public:
      TaskWithParam(T *obj, void (T::*func)(P *), P *param) : object_(obj), funcion_(func), param_(param) {}
      virtual void Exec() { (object_->*funcion_)(param_); }

   private:
      T *object_;
      void (T::*funcion_)(P *);
      P *param_;
};

}

#endif
