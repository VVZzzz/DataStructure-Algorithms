#pragma once
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <iterator>
#include "MyList.h"

template <typename Object = int>
struct T_Node {
  Object m_data;
  T_Node *prev;
  T_Node *next;
  T_Node(Object object = Object(), T_Node *p = nullptr, T_Node *n = nullptr)
      : m_data(object), prev(p), next(n) {}
};

// 3.1
template <typename Object>
void printLots(std::list<Object> L, std::list<int> P) {
  typename std::list<int>::const_iterator P_itr;
  typename std::list<Object>::const_iterator L_itr;
  int start = 0;
  L_itr = L.cbegin();
  for (P_itr itr = P.cbegin(); itr != P.cend(); itr++) {
    while (start < *itr && L_itr != L.cend()) {
      start++;
      L_itr++;
    }
    if () {
    }
    std::cout << *L_itr << std::endl;
  }
}

// 3.2 a
template <typename Object>
void swapWithNext(T_Node<Object> *beforep) {
  T_Node<Object> *prvp = beforep->next, *nextp = beforep->next;
  prvp->next = nextp->next;
  nextp->next = prvp;
  beforep->next = nextp;
}

// 3.2 b
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

// 3.3
template <typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object &x) {
  for (auto itr = start; itr != end; itr++)
    if (*itr == x) break;
  return itr;
}

// 3.4
template <typename Object>
MyList<Object> instersection(const MyList<Object> &L1,
                             const MyList<Object> &L2) {
  MyList<Object> intersect;
  MyList<Object>::const_iterator iterL1 = L1.begin();
  MyList<Object>::const_iterator iterL2 = L2.begin();
  while (iterL1 != L1.end() && iterL2 != L2.end()) {
    if (*iterL1 == *iterL2) {
      intersect.push_back(*iterL1);
      iterL1++;
      iterL2++;
    } else if (*iterL1 < *iterL2) {
      iterL1++;
    } else {
      iterL2++;
    }
  }
  return intersect;
}

// 3.5
template <typename T>
MyList<T> instersect(const MyList<T> &L1, const MyList<T> &L2) {
  MyList<T> intersect;
  MyList<T>::const_iterator iterL1 = L1.begin();
  MyList<T>::const_iterator iterL2 = L2.begin();
  while (iterL1 != L1.end() && iterL2 != L2.end()) {
    if (*iterL1 < *iterL2) {
      intersect.push_back(*iterL1);
      iterL1++;
    } else if (*iterL1 > *iterL2) {
      intersect.push_back(*iterL2);
      iterL2++;
    } else {
      intersect.push_back(*iterL2);
      iterL1++;
      iterL2++;
    }
  }
  return intersect;
}

// 3.11
template <typename Object>
struct SLNode {
  Object data;
  SLNode *next;
  SLNode(const Object &d = Object(), SLNode *n = nullptr) : data(d), next(n) {}
};

template <typename Object>
class SingleList {
 public:
  SingleList() { init(); }
  ~SingleList() {}
  int Size() {
    std::cout << m_size << endl;
    return m_size;
  }
  void print() {
    SLNode<Object> *p = m_phead->next;
    while (p != nullptr) {
      std::cout << p->data << " " << std::endl;
    }
  }
  bool isContainX(const Object &x, SLNode<Object> &itr = nullptr) {
    SLNode<Object> *p = m_phead->next;
    while (p != nullptr) {
      if (p->data == x) {
        itr = p;
        return true;
      }
    }
    return false;
  }
  void ins_delX(const Object &x) {
    SLNode<Object> *pos = nullptr;
    if (isContainX(x, pos)) {
      auto p = m_phead->next;
      while (p != nullptr && p->next != pos) p = p->next;
      p->next = pos->next;
      delete pos;
      m_size--;
    } else {
      auto p = new SLNode<Object>(x, nullptr);
      auto itr = m_phead;
      while (itr != nullptr && itr->next != nullptr) {
        if (itr->next >= x) {
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
    while (ptr != nullptr) {
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

// 3.13
// 3.14
// 3.15
// 3.16
// 3.17��
// 3.21TODO

// 3.22
/*ʹ�ú�׺���ʽ���� + -* / ^������=���� */
double evalPostFix() {
  std::string token;
  std::stack<double> s;
  double temp = 0.0;
  while (std::cin >> token && token[0] != '=') {
    if (std::isdigit(token[0])) {
      s.push(std::atof(token.c_str()));
    } else {
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
          std::cout << "��֧�ֵ�����" << std::endl;
          break;
      }
      s.pop();
      s.push(temp);
    }
  }
  return s.top();
}

// 3.23(a,b)
/*����׺���ʽ����׺���ʽ��ת��,�����Ϊ+ - * / ( ) ^ */
//ע������^������Ǵ��������ϣ�2^2^3=2^(2^3)����4^3��
//������������溯����ȷ
std::string inToPostFix() {
  std::string token;
  std::stack<char> s;
  std::string ret;
  double temp = 0.0;
  while (std::cin >> token && token[0] != '=') {
    switch (token[0]) {
      case '+':
      case '-':
        while (!s.empty() && s.top() != '(') {
          ret.push_back(s.top());
          s.pop();
        }
        s.push(token[0]);
        break;
      case '*':
      case '/':
        while (!s.empty() && s.top() != '(') {
          if (s.top() == '^' || s.top() == '*' || s.top() == '/') {
            ret.push_back(s.top());
            s.pop();
            continue;
          } else
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
        //���Ͼͳ�Ϊ�������ҽ��
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

// 3.23 c
std::string postToinFix() {
  std::string token;
  std::stack<std::string> s;
  std::string temp;
  while (std::cin >> token && token[0] != '=') {
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

// 3.24
//�μ��ĵ�

// 3.25
/*
a.�μ��ĵ�
b.�μ��ĵ�
*/

// 3.27 TODO
// 3.28 �μ�MyDeque.h

// 3.29
//�ڵ�ʹ��SLNode,��ͷβ���
//����1.��ת���� �ǵݹ� ʱ��O(n)
template <typename T>
SLNode<T> *reverseSL1(SLNode<T> *first) {
  SLNode *prev = nullptr, *curr = first, *nextp;
  = curr->next;
  while (curr != nullptr) {
    curr->next = prev;
    prev = curr;
    curr = nextp;
    nextp = nextp->next;
  }
  return prev;
}

//����2.ֻ�������ת���� �ݹ�ռ�ΪO(n)
template <typename T>
void reverseprintSL2(SLNode<T> *first) {
  if (first == nullptr) return;
  reverseprintSL2(first->next);
  std::cout << first->val << std::endl;
}

//����3. �ǵݹ����ջ�ռ�ΪO(n)
template <typename T>
void reverseprintSL3(SLNode<T> *first) {
  stack<T> s;
  while (first != nullptr) {
    s.push(first->val);
  }
  while (!s.empty()) {
    std::cout << s.top() << std::endl;
    s.pop();
  }
}

//����4.�ݹ鷭ת����
template <typename T>
SLNode<T> *reverseSL4(SLNode<T> *first) {
  if (first == nullptr || first->next == nullptr)
    return first;
  else {
    SLNode *newhead = reverseSL4(first->next);
    first->next->next = first;
    first->next = nullptr;
    return newhead;
  }
}

// 3.30 ���������find��������,�˴�д�������
// a.����ʵ��
template <typename T>
class SAVector {
 public:
  SAVector() : m_vec(std::vector<T>()) {}
  SAVector(std::vector<T> vec) : m_vec(vec.begin(), vec.end()) {}
  void push(const T &t) { m_vec.insert(m_vec.begin(), t); }
  std::iterator<std::bidirectional_iterator_tag,std::vector<T>> find(const T &t) {
    auto itr = std::find(m_vec.begin(), m_vec.end(), t);
    m_vec.erase(itr);
    push(t);
    return m_vec.begin();
  }
  T &find(size_t i) {
    auto temp = m_vec[i];
    m_vec.erase(m_vec.begin() + i);
    push(temp);
    return m_vec[0];
  }

 private:
  std::vector<T> m_vec;
};

// b.����listʵ��
template <typename T>
class SAList {
 public:
  SAList() : m_list(list<T>()) {}
  SAList(std::list<T> l) : m_list(l.begin(), l.end()) {}
  void push(const T &t) { m_list.push_front(t); }
  auto find(const T &t) {
    m_list.erase(std::find(m_list.begin(), m_list.end(), t));
    push(t);
    return m_list.begin();
  }
  T &find(size_t i) {
    T temp = *(m_list.begin() + i);
    m_list.erase(m_list.begin() + i);
    push(temp);
    return *m_list.begin();
  }

 private:
  std::list<T> m_list;
};

// 3.31������ʵ��ջ.�ޱ�ͷ��β���
template <typename T>
struct StackNode {
  StackNode() : next(nullptr) {}
  StackNode(T &obj) : data(obj) {}
  StackNode(T &obj, StackNode *ptr) : data(obj), next(ptr) {}
  T data;
  StackNode *next;
};

template <typename T>
class MyStack {
 public:
  MyStack() : head(nullptr) {}
  ~MyStack() {
    while (head) pop();
  }
  void push(T obj) { head = new StackNode<T>(obj, head); }
  T top() { return head->data; }
  void pop() {
    auto temp = head->next;
    delete head;
    head = temp;
  }

 private:
  StackNode<T> *head;
};

// 3.32��������ʵ�ֶ���,���������StackNode
template <typename T>
class MyQueue {
 public:
  MyQueue() : front(nullptr), rear(nullptr) {}
  ~MyQueue() {
    while (front) Deque();
  }
  //���
  void enqueue(T obj) {
    auto ptr = new StackNode<T>(obj, nullptr);
    if (rear)
      rear = rear->next = ptr;
    else {
      front = rear = ptr;
    }
  }
  //����
  T Deque() {
    T res = front->data;
    auto temp = front;
    if (front->next == nullptr)
      front = rear = nullptr;
    else
      front = front->next;
    delete temp;
    return res;
  }

 private:
  StackNode<T> *front;  //����ͷ
  StackNode<T> *rear;   //����β
};

// 3.33ѭ������ʵ�ֶ���,��vector
template <typename T>
class LoopArrayQueue {
 public:
  LoopArrayQueue(size_t s) : maxsize(s), front(0), rear(0) {}
  LoopArrayQueue() : maxsize(100), front(0), rear(0) {}
  ~LoopArrayQueue() {
    while (front != rear) deque();
  }
  bool empty() { return front == rear; }
  bool full() { return (rear + 1) % maxsize == front; }
  void enqueue(T obj) {
    if (!full()) {
      m_array[rear] = obj;
      rear = (rear + 1) % maxsize;
    }
  }
  T deque() {
    T res;
    if (!empty()) {
      res = m_array[front];
      front = (front + 1) % maxsize;
    }
    return res;
  }

 private:
  std::vector<T> m_array;
  size_t maxsize;
  size_t front, rear;
};

//3.36���ΪSLNode
template <typename T>
void deletecurr(SLNode<T> *p) {
  p->data = p->next->data;
  p->next = p->next->next;
}