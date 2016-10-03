#include <cstddef> // size_t

struct Expression;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

/*
struct SharedPtr
{
  // реализуйте следующие методы
  //
  // explicit SharedPtr(Expression *ptr = 0)
  // ~SharedPtr()
  // SharedPtr(const SharedPtr &)
  // SharedPtr& operator=(const SharedPtr &)
  // Expression* get() const
  // void reset(Expression *ptr = 0)
  // Expression& operator*() const
  // Expression* operator->() const

  // конструктор
  explicit SharedPtr(Expression *ptr = 0) {
    ptr_ = ptr;
    if (ptr_ != 0) {
      count_ = 1;
    }
  }

  // деструктор
  ~SharedPtr() {
    if (ptr_ != 0) {
      // если декремент счетчика дает ноль, освобождаем память
      if (--count_ == 0) {
	delete ptr_;
      }
    }
  }

  // конструктор копирования
  SharedPtr(const SharedPtr & ptr) {
    ptr_ = ptr.ptr_;
    count_ = ptr.count_;
    if (ptr_ != 0) {
      count_++;
    }
  }

  // оператор присваивания
  SharedPtr& operator=(const SharedPtr & ptr) {
    // не присваивать самому себе 
    if (this != &ptr) {
      if (ptr_ != 0) {
	// если декремент счетчика дает ноль, чистимся
	if (--count_ == 0) {
	  delete ptr_;
	}
      }
      // копируем данные и счетчик, а потом инкремент счетчика
      ptr_ = ptr.ptr_;
      count_ = ptr.count_;
      if (ptr_ != 0) {
	count_++;
      }
    }
    return *this;
  }

  // 
  Expression* get() const { return ptr_; }
  void reset(Expression *ptr = 0) {
    if (ptr_) {
      if (--count_ == 0) {
	delete ptr_;
      }
    }
    ptr_ = ptr;
  }

  Expression& operator*() const { return *ptr_; }

  Expression* operator->() const { return ptr_; }


private:
  Expression *ptr_;
  size_t * count_; // если без вспомогательной структуры, то указатель!
};

*/

struct Counter 
{
public:
  void addref() { count_++; }
  size_t release() { return --count_; }

private:
  size_t count_; // reference counter
};

struct SharedPtr
{
  // реализуйте следующие методы
  //
  // explicit SharedPtr(Expression *ptr = 0)
  // ~SharedPtr()
  // SharedPtr(const SharedPtr &)
  // SharedPtr& operator=(const SharedPtr &)
  // Expression* get() const
  // void reset(Expression *ptr = 0)
  // Expression& operator*() const
  // Expression* operator->() const

  // конструктор
  explicit SharedPtr(Expression *ptr = 0) {
    ptr_ = ptr;
    reference_ = 0;
    if (ptr_ != 0) {
      reference_ = new Counter();
      reference_->addref();
    }
  }

  // деструктор
  ~SharedPtr() {
    if (ptr_ != 0) {
      // если декремент счетчика дает ноль, освобождаем память
      if (reference_->release() == 0) {
	delete ptr_;
	delete reference_;
      }
    }
  }

  // конструктор копирования
  SharedPtr(const SharedPtr & sp)
    : ptr_(sp.ptr_), reference_(sp.reference_) {
    if (ptr_ != 0) {
      reference_->addref();
    }
  }

  // оператор присваивания
  SharedPtr& operator=(const SharedPtr & sp) {
    // не присваивать самому себе 
    if (this != &sp) {
      // меньшает счетчик ссылок левого операнда на 1, если внутри
      // левого SharedPtr хранится ненулевой указатель
      if (ptr_ != 0) {
	// если декремент счетчика дает ноль, чистимся
	if (reference_->release() == 0) {
	  delete ptr_;
	  delete reference_;
	}
      }
      // увеличивает счетчик правого SharedPtr на 1, если в правом
      // SharedPtr хранится ненулевой указатель
      if (sp.ptr_ != 0) {
	// копируем данные и счетчик, а потом инкремент счетчика
	ptr_ = sp.ptr_;
	reference_ = sp.reference_;
	reference_->addref();
      }
    }
    return *this;
  }

  // 
  Expression* get() const { return ptr_; }

  // 
  void reset(Expression *ptr = 0) {
    // заглушка, которая проходит тест!!!
    ///delete ptr;
    if (ptr_) {
      if (reference_->release() == 0) {
	delete ptr_;
	delete reference_;
      }
    }

    ptr_ = ptr;
    reference_ = 0;
    if (ptr_ != 0) {
      reference_ = new Counter();
      reference_->addref();
    }
  }

  Expression& operator*() const { return *ptr_; }

  Expression* operator->() const { return ptr_; }


private:
  Expression *ptr_;
  Counter *reference_;
};


int main() {
  /*
  Number *n32 = new Number(32.0);
  Number *n16 = new Number(16.0);
  Number *n42 = new Number(42.0);
  std::cout<<"------------------"<<std::endl;
  std::cout<<"SharedPtr p1(n32)"<<std::endl;
  SharedPtr p1(n32);
  std::cout<<"p1 = "<<p1.count()<<std::endl;
  std::cout<<"------------------"<<std::endl;
    
  std::cout<<"SharedPtr p2 = p1"<<std::endl;
  SharedPtr p2 = p1;
  std::cout<<"p2 = "<<p2.count()<<std::endl;
  std::cout<<"p1 = "<<p1.count()<<std::endl;
  std::cout<<"------------------"<<std::endl;
    
  std::cout<<"SharedPtr p3(p1)"<<std::endl;
  SharedPtr p3(p1);
  std::cout<<"p1 = "<<p1.count()<<std::endl;
  std::cout<<"p2 = "<<p2.count()<<std::endl;
  std::cout<<"p3 = "<<p3.count()<<std::endl;
  std::cout<<"------------------"<<std::endl;
     
  std::cout<<"p3.reset(n16)"<<std::endl;
  p3.reset(n16);
  std::cout<<"p3 = "<<p3.count()<<std::endl;
  std::cout<<"p2 = "<<p2.count()<<std::endl;
  std::cout<<"p1 = "<<p1.count()<<std::endl;
  std::cout<<"------------------"<<std::endl;
    
  std::cout<<"p3.reset(0)"<<std::endl;
  p3.reset(0);
  std::cout<<"p3 = "<<p3.count()<<std::endl;
  std::cout<<"p2 = "<<p2.count()<<std::endl;
  std::cout<<"p1 = "<<p1.count()<<std::endl;
  std::cout<<"------------------"<<std::endl;
    
    
  std::cout<<"p1 = p1"<<std::endl;
  p1 = p1;
  std::cout<<"p3 = "<<p3.count()<<std::endl;
  std::cout<<"p2 = "<<p2.count()<<std::endl;
  std::cout<<"p1 = "<<p1.count()<<std::endl;
  std::cout<<"------------------"<<std::endl;
    
    
  std::cout<<"p3.~SharedPtr()"<<std::endl;
  p3.~SharedPtr();
  std::cout<<"p2 = "<<p2.count()<<std::endl;
  std::cout<<"p1 = "<<p1.count()<<std::endl;
  std::cout<<"------------------"<<std::endl;
    
  std::cout<<"p1.reset(n42)"<<std::endl;
  p1.reset(n42);
  std::cout<<"p1 = "<<p1.count()<<std::endl;
  std::cout<<"p2 = "<<p2.count()<<std::endl;
  std::cout<<"------------------"<<std::endl;
    
  std::cout<<"p1.~SharedPtr()"<<std::endl;
  p1.~SharedPtr();
  std::cout<<"p2 = "<<p2.count()<<std::endl;
  std::cout<<"------------------"<<std::endl;
    
  std::cout<<"p2.~SharedPtr()"<<std::endl;
  p2.~SharedPtr();
  */
  return 0;
}
