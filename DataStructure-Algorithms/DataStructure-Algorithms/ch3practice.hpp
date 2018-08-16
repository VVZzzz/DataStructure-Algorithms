#pragma once
#include "MyList.h"
#include <string>
#include <list>
#include <stack>
#include <iostream>
#include <cctype>
#include <cstdlib>

template <typename Object = int>
struct T_Node
{
	Object m_data;
	T_Node *prev;
	T_Node *next;
	T_Node(Object object = Object(),
		T_Node *p = nullptr, T_Node *n = nullptr) :
		m_data(object), prev(p), next(n) { }
};

//3.1
template <typename Object>
void printLots(std::list<Object>L, std::list<int>P) {
	typename std::list<int>::const_iterator P_itr;
	typename std::list<Object>::const_iterator L_itr;
	int start = 0;
	L_itr = L.cbegin();
	for (P_itr itr = P.cbegin(); itr != P.cend(); itr++) {
		while (start<*itr&&L_itr!=L.cend()){
			start++;
			L_itr++;
		}
		if () {
		}
		std::cout << *L_itr << std::endl;
	}
}

//3.2 a
template <typename Object>
void swapWithNext(T_Node<Object> *beforep) {
	T_Node<Object> *prvp = beforep->next, *nextp = beforep->next;
	prvp->next = nextp->next;
	nextp->next = prvp;
	beforep->next = nextp;
}

//3.2 b
template <typename Object>
void swapWithNext_Dual(T_Node<Object> *beforep) {
	T_Node<Object> *prvp = beforep->next, *nextp = beforep->next;
	prvp->next = nextp->next;
	nextp->next = prvp;
	beforep->next = nextp;

	prvp->next->prev = prvp;
	prvp->prev = nextp;
	nextp->prev = beforep;
}

//3.3
template <typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const	Object & x) {
	for (auto itr = start; itr != end;itr++) 
		if (*itr==x) 
			break;
	return itr;
}

//3.4
template <typename Object>
MyList<Object> instersection(const MyList<Object> & L1,
	const MyList<Object> & L2) {
	MyList<Object> intersect;
	MyList<Object>::const_iterator iterL1 = L1.begin();
	MyList<Object>::const_iterator iterL2 = L2.begin();
	while (iterL1 != L1.end() && iterL2 != L2.end()) {
		if (*iterL1==*iterL2) {
			intersect.push_back(*iterL1);
			iterL1++;
			iterL2++;
		}
		else if (*iterL1<*iterL2) {
			iterL1++;
		}
		else {
			iterL2++;
		}
	}
	return intersect;
}

// 3.5
template <typename T>
MyList<T> instersect(const MyList<T> & L1,
	const MyList<T> & L2) {
	MyList<T> intersect;
	MyList<T>::const_iterator iterL1 = L1.begin();
	MyList<T>::const_iterator iterL2 = L2.begin();
	while (iterL1 != L1.end() && iterL2 != L2.end()) {
		if (*iterL1<*iterL2) {
			intersect.push_back(*iterL1);
			iterL1++;
		}
		else if (*iterL1>*iterL2) {
			intersect.push_back(*iterL2);
			iterL2++;
		}
		else {
			intersect.push_back(*iterL2);
			iterL1++;
			iterL2++;
		}
	}
	return intersect;
}

//3.11
template <typename Object>
struct SLNode {
	Object data;
	SLNode *next;
	SLNode(const Object &d=Object(), SLNode *n = nullptr)
	:data(d),next(n) {}
};

template <typename Object>
class SingleList {
public:
	SingleList() { init(); }
	~SingleList() {

	}
	int Size() {
		std::cout << m_size << endl;
		return m_size;
	}
	void print() {
		SLNode<Object> *p = m_phead->next;
		while (p!=nullptr) {
			std::cout << p->data << " " << std::endl;
		}
	}
	bool isContainX(const Object & x,SLNode<Object> &itr=nullptr) {
		SLNode<Object> *p = m_phead->next;
		while (p!=nullptr) {
			if (p->data==x) {
				itr = p;
				return true;
			}
		}
		return false;
	}
	void ins_delX(const Object & x) {
		SLNode<Object> *pos = nullptr;
		if (isContainX(x,pos)) {
			auto p = m_phead->next;
			while (p!=nullptr&&p->next!=pos)
				p = p->next;
			p->next = pos->next;
			delete pos;
			m_size--;
		}
		else {
			auto p = new SLNode<Object>(x,nullptr);
			auto itr = m_phead;
			while (itr != nullptr && itr->next != nullptr) {
				if (itr->next>=x) {
					p->next = itr->next;
					itr->next = p;
					m_size++;
					return;
				}
				itr = itr->next;
			}
		}
	}
	void eraseList(SLNode<Object> *h) {
		auto ptr = h;
		decltype(h) nextptr;
		while (ptr!=nullptr) {
			nextptr = ptr->next;
			delete ptr;
			ptr = nextptr;
		}
	}
private:
	SLNode<Object> *m_phead;
	int m_size;
	void init() {
		m_size = 0;
		m_phead = new SLNode<Object>;
	}

};

//3.13 
//3.14
//3.15
//3.16
//3.17略
//3.21TODO

//3.22
/*使用后缀表达式计算 + -* / ^，输入=结束 */
double evalPostFix() {
	std::string token;
	std::stack<double> s;
	double temp = 0.0;
	while (std::cin>>token && token[0] != '=') {
		if (std::isdigit(token[0])) {
			s.push(std::atof(token.c_str()));
		}
		else {
			temp = s.top();
			s.pop();
			switch (token[0]) {
			case '+':
				temp += s.top();
				break;
			case '-':
				temp = s.top() - temp;
				break;
			case '*':
				temp *= s.top();
				break;
			case '/':
				temp = s.top() / temp;
				break;
			case '^':
				temp = std::pow(s.top(), temp);
				break;
			default:
				std::cout << "不支持的运算" << std::endl;
				break;
			}
			s.pop();
			s.push(temp);
		}
	}
	return s.top();
}

//3.23(a,b)
/*从中缀表达式到后缀表达式的转换,运算符为+ - * / ( ) ^ */
//注意这里^运算符是从右向左结合，2^2^3=2^(2^3)而非4^3。
//此题答案有误，下面函数正确
std::string inToPostFix() {
	std::string token;
	std::stack<char> s;
	std::string ret;
	double temp = 0.0;
	while (std::cin >> token && token[0] != '=') {
		switch (token[0]) {
		case '+': case '-':
			while (!s.empty() && s.top() != '(') {
				ret.push_back(s.top());
				s.pop();
			}
			s.push(token[0]);
			break;
		case '*': case '/':
			while (!s.empty() && s.top() != '(') {
				if (s.top() == '^' || s.top() == '*' || s.top() == '/') {
					ret.push_back(s.top());
					s.pop();
					continue;
				}
				else
					break;
			}
			s.push(token[0]);
			break;
		case '(':
			s.push(token[0]);
			break;
		case ')':
			while (!s.empty() && s.top() != '(') {
				ret.push_back(s.top());
				s.pop();
			}
			if (!s.empty()) s.pop();
			break;
		case '^':
			//加上就成为由左向右结合
			/*while (!s.empty()) {
				if (s.top() == '^') {
					ret.push_back(s.top());
					s.pop();
				}
				else
					break;
			}*/
			s.push(token[0]);
			break;
		default:
			ret.append(token);
			break;
		}
	}
	while (!s.empty()) {
		ret.push_back(s.top());
		s.pop();
	}
	return ret;
}

//3.23 c 
std::string postToinFix() {
	std::string token;
	std::stack<std::string> s;
	std::string temp;
	while (std::cin>>token && token[0] != '=') {
		switch (token[0]) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			temp = s.top();
			s.pop();
			temp = "(" + s.top() + token + temp + ")";
			s.pop();
			s.push(temp);
			break;
		default:
			s.push(token);
			break;
		}
	}
	return s.top();
}

//3.24
//参见文档

//3.25
/*
a.参见文档
b.参见文档
*/

//

