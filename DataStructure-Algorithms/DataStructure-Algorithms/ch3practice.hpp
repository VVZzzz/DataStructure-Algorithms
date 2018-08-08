#pragma once
#include "MyList.h"
template <typename Obeject>
struct Node
{
	Object data;
	Node *prev;
	Node *next;
	Node(const Object &object = Object(),
		Node *p = nullptr, Node *n = nullptr) :
		data(object), prev(p), next(n) { }
};

//3.1
template <typename Obeject>
void printLots(list<Obeject>L, list<int>P) {
	typename list<int>::const_iterator P_itr;
	typename list<Obeject>::const_iterator L_itr;
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
template <typename Obeject>
void swapWithNext(Node *beforep) {
	Node *prvp = beforep->next, *nextp = beforep->next;
	prvp->next = nextp->next;
	nextp->next = prvp;
	beforep->next = nextp;
}

//3.2 b
template <typename Obeject>
void swapWithNext_Dual(Node *beforep) {
	Node *prvp = beforep->next, *nextp = beforep->next;
	prvp->next = nextp->next;
	nextp->next = prvp;
	beforep->next = nextp;

	prvp->next->prev = prvp;
	prvp->prev = nextp;
	nextp->prev = beforep;
}

//3.3
template <typename Iterator, typename Obeject>
Iterator find(Iterator start, Iterator end, const	Obeject & x) {
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
template <typename Object>
MyList<Object> instersection(const MyList<Object> & L1,
	const MyList<Object> & L2) {
	MyList<Object> intersect;
	MyList<Object>::const_iterator iterL1 = L1.begin();
	MyList<Object>::const_iterator iterL2 = L2.begin();
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
	SLNode(const Object &object d=Object(), Node *n = nullptr)
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
	bool isContainX(const Object & x,SLNode<Object> &itr==nullptr) {
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