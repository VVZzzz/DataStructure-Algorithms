### 在class中定义struct
	class A {
	  /*struct temp;*/
	  public:
		temp *fun1();   
	  private:   
		struct temp{};
	}
这样会报错。因为temp定义在后面，除非在前置声明temp类型才可以。
在用自定义类型时候，一定要在开头声明。

### class中的private的struct在类外无法访问
	class A {
	  struct A;
	  public:
		temp *func1();
	  private:
		struct temp {};
	}
	A::temp* A::func1(){}
struct类似成员变量，私有的成员变量在类外是无法访问的。所以这个函数的返回类型，在类外无法解析。通常struct被定义为private的时候，说明这个struct不在类外使用，只在类内作为工具使用。