/**

http://shatteredterminal.com/2008/11/scoped_ptr-and-unique_ptr-smart-pointers/

see also:
boost::scoped_ptr
boost::shared_ptr

http://www.codeproject.com/Articles/15351/Implementing-a-simple-smart-pointer-in-c

 */

struct Expression;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct ScopedPtr
{
  // реализуйте следующие методы:
  //
  // explicit ScopedPtr(Expression *ptr = 0)
  // ~ScopedPtr()
  // Expression* get() const
  // Expression* release()
  // void reset(Expression *ptr = 0)
  // Expression& operator*() const
  // Expression* operator->() const

  explicit ScopedPtr(Expression *ptr = 0) { ptr_ = ptr; }
  //~ScopedPtr() { delete this->get(); }

  ~ScopedPtr() { 
    if (ptr_ != 0) {
      delete ptr_; 
    }
  }

  Expression* get() const { return ptr_; }

  Expression* release() {  
    Expression *new_ptr;
    new_ptr = ptr_;
    ptr_ = 0;
    return new_ptr;
  }

  void reset(Expression *ptr = 0) {
    if (ptr_) {
      delete ptr_;
    }
    ptr_ = ptr;
    //new ScopedPtr(ptr);
  }

  Expression& operator*() const { return *ptr_; }
  Expression* operator->() const { return ptr_; }


private:
  // запрещаем копирование ScopedPtr
  ScopedPtr(const ScopedPtr&);
  ScopedPtr& operator=(const ScopedPtr&);

  Expression *ptr_;
};

int main() {
  return 0;
}
