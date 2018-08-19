#pragma once
#include "MyList.h"
/*�ײ����ݽṹΪ˫������*/
template<typename T>
class MyDeque {
public:
	MyDeque() { l(); };
	~MyDeque() {};
	void  push(T &obj) { l.push_front(obj); }
	T pop() {
		T obj = l.front();

		l.pop_front();
		return obj;
	}
	void inject(T &obj) { l.push_back(obj); }
	T eject() {
		T obj = l.back();
		l.pop_back();
		return obj;
	}
	
private:
	MyList<T> l;
};
