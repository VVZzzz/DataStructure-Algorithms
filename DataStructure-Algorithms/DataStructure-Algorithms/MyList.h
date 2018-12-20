#ifndef MYLIST_H_
#define MYLIST_H_
#include <iostream>
#include <string>
template <typename Object>
class MyList {
 private:
  struct Node {
    Object data;
    Node *prev;
    Node *next;
    bool isactive;
    bool istodel;
    Node(const Object &object = Object(), Node *p = nullptr, Node *n = nullptr)
        : data(object), prev(p), next(n), isactive(true), istodel(false) {}
  };

 public:
  class const_iterator {
    friend class MyList<Object>;

   public:
    const_iterator() : current(nullptr) {}

    const Object &operator*() const { return retrieve(); }

    /*ǰ���������������,������������ص��Ǹ���ֵ*/
    /*ǰ���������Ҫ�����Ч��(�˴�û��),���������������Ҫ*/
    /*3.18��ʵ�ַ���ΪNULL,����Ӧ��ÿ�������м��current->isactive
    �Ƿ�Ϊfalse,һ��Ϊfalse��ͽ�this��Ϊnullptr���ɡ����ô�����ûд��*/
    const_iterator &operator++() {
      current = current->next;
      return *this;
    }

    const_iterator &operator--() {
      current = current->prev;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator old_p(*this);
      ++(*this);
      //����current = current->next;
      return old_p;
    }

    const_iterator operator--(int) {
      const_iterator old_p(*this);
      --(*this);
      return old_p;
    }

    const_iterator &operator+(int k) const {
      const_iterator advanced = *this;
      for (size_t i = 0; i < k; i++) {
        //++advanced;
        advanced.current = advanced.current->next;
      }
      return advanced;
    }

    bool operator==(const const_iterator &rhs) const {
      return current == rhs.current;
    }

    bool operator!=(const const_iterator &rhs) const {
      return current != rhs.current;
    }

   protected:  //������List�����
    Node *current;
    Object &retrieve() const { return current->data; }  //���ߺ���
    const_iterator(Node *p) : current(p->isactive ? p : nullptr) {}
  };

  class iterator : public const_iterator {
    friend class MyList<Object>;

   public:
    iterator() {}
    Object &operator*() { return retrieve(); }

    iterator &operator++() {
      current = current->next;
      return *this;
    }

    iterator &operator--() {
      current = current->prev;
      return *this;
    }

    iterator operator++(int) {
      iterator old_p(*this);
      ++(*this);
      //����current = current->next;
      return old_p;
    }

    iterator operator--(int) {
      iterator old_p(*this);
      --(*this);
      return old_p;
    }

   protected:
    iterator(Node *p) : const_iterator(p) {}
  };

  class const_reverse_iterator {
    friend class MyList<Object>;

   public:
    const_reverse_iterator() : current(nullptr) {}

    const Object &operator*() const { return retrieve(); }

    /*ǰ���������������,������������ص��Ǹ���ֵ*/
    /*ǰ���������Ҫ�����Ч��(�˴�û��),���������������Ҫ*/
    const_reverse_iterator &operator++() {
      current = current->prev;
      return *this;
    }

    const_reverse_iterator &operator--() {
      current = current->next;
      return *this;
    }

    const_reverse_iterator operator++(int) {
      const_reverse_iterator old_p(*this);
      ++(*this);
      //����current = current->next;
      return old_p;
    }

    const_reverse_iterator operator--(int) {
      const_reverse_iterator old_p(*this);
      --(*this);
      return old_p;
    }

    const_reverse_iterator &operator+(int k) const {
      const_reverse_iterator advanced = *this;
      for (size_t i = 0; i < k; i++) {
        //++advanced;
        advanced.current = advanced.current->prev;
      }
      return advanced;
    }

    bool operator==(const const_reverse_iterator &rhs) const {
      return current == rhs.current;
    }

    bool operator!=(const const_reverse_iterator &rhs) const {
      return current != rhs.current;
    }

   protected:
    Node *current;
    Object &retrieve() const { return current->data; }  //���ߺ���
    const_reverse_iterator(Node *p) : current(p->isactive ? p : nullptr) {}
  };

  class reverse_iterator : public const_reverse_iterator {
    friend class MyList<Object>;

   public:
    reverse_iterator() {}
    Object &operator*() { return retrieve(); }

    reverse_iterator &operator++() {
      current = current->prev;
      return *this;
    }

    reverse_iterator &operator--() {
      current = current->next;
      return *this;
    }

    reverse_iterator operator++(int) {
      reverse_iterator old_p(*this);
      ++(*this);
      //����current = current->next;
      return old_p;
    }

    reverse_iterator operator--(int) {
      reverse_iterator old_p(*this);
      --(*this);
      return old_p;
    }

   protected:
    reverse_iterator(Node *p) : const_reverse_iterator(p) {}
  };

  MyList() { init(); }
  ~MyList() {
    clear();
    delete head;
    delete tail;
  }

  const MyList operator=(const MyList &rhs) {
    if (this != rhs) {
      clear();
      for (const_iterator i = rhs.begin(); i != rhs.end(); ++i) {
        push_back(*i);
      }
    }
    return *this;
  }

  iterator begin()  //���ص�һ����㣨�Ǳ�ͷ��㣩
  {
    return iterator(head->next);
  }

  const_iterator begin() const { return const_iterator(head->next); }

  iterator end()  //����β���
  {
    return iterator(tail);
  }

  const_iterator end() const { return const_iterator(tail); }

  reverse_iterator rbegin() { return reverse_iterator(tail->prev); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(tail->prev);
  }

  reverse_iterator rend() { return reverse_iterator(head); }

  const_reverse_iterator rend() const { return const_reverse_iterator(head); }

  int size() const { return theSize; }

  bool empty() const { return theSize == 0; }

  void clear()  //ֻɾ������ͷ β�����������
  {
    while (!empty()) pop_front();
  }

  Object &
  front()  //�����汾��Object,�ǳ����汾���ڵ��ö���Ϊ��const,���뺯����thisָ��Ϊ��const�ͻ���÷�const�汾��begin()
  {
    return *begin();
  }

  const Object &front()
      const  //�����汾���ڵ��ö���Ϊconst,���뺯����thisָ��Ϊconst�ͻ����const�汾��begin()
  {
    return *begin();
  }

  Object &back()  //�������һ����㣨��β�ڵ㣩
  {
    return *--end();
  }

  const Object &back() const { return *--end(); }

  void push_front(const Object &object) { insert(begin(), object); }

  void push_back(const Object &object) { insert(end(), object); }

  void pop_front() { erase(begin()); }

  void pop_back() { erase(--end()); }

  iterator insert(iterator itr,
                  const Object &x)  //��itr֮ǰ��λ�ò���,���ز���֮���itr
  {
    Node *p = itr.current;
    theSize++;  //ע���ȸ�ֵ,���޸�
    return iterator(p->prev = p->prev->next = new Node(x, p->prev, p));
  }

  iterator erase(iterator itr)  //ɾ��itrλ�õĽ��,����itr֮��ĵ�����
  {
    Node *p = itr.current;
    iterator retVal = p->next;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->isactive = false;
    delete p;
    theSize--;
    return retVal;
  }

  iterator erase(iterator start, iterator to) {
    for (iterator i = start; i != to; i = erase(i))
      ;
    return to;
  }

  void lazy_full_erase() {
    auto itr = begin();
    while (itr != end()) {
      if (itr.current->istodel) {
        itr = erase(itr);
        del_num--;
      } else
        itr++;
    }
  }

  iterator lazy_erase(iterator itr) {
    iterator retitr = itr.current->next;
    //����ע��Ҫ����istodelΪtrue�Ľ��
    while ((retitr.current != nullptr) && retitr.current->istodel) retitr++;
    itr.current->istodel = true;
    if (++del_num >= size() / 2) {
      //���
      lazy_full_erase();
    }
    return retitr;
  }

  iterator lazy_erase(iterator start, iterator to) {
    for (iterator i = start; i != to; i = lazy_erase(i))
      ;
    return to;
  }

  void splice(iterator itr, MyList<Object> &lst) {
    Node *p = itr.current;
    theSize += lst.size();
    lst.head->next->prev = p->prev;
    p->prev->next = lst.head->next;
    lst.tail->prev->next = p;
    p->prev = lst.tail->prev;
    lst.head->next = nullptr;
    lst.init();
  }

  void printInfo() {
    std::cout << "the Size: " << theSize << std::endl;
    Node *p = head;
    while (p) {
      printinfo(p);
      p = p->next;
    }
  }

 private:
  int theSize;
  Node *head;   //��ͷ���
  Node *tail;   //β���
  int del_num;  //Ҫɾ���Ľ�����

  void init()  //��ʼ�����ߺ���
  {
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
    del_num = 0;
  }

  void printinfo(Node *t) {
    if (t) {
      std::cout << "current node's address is " << (int)(t) << std::endl;
      std::cout << "curr->data is " << t->data << std::endl;
      std::cout << "curr->prev is "
                << ((t->prev == nullptr) ? "nullptr"
                                         : std::to_string(t->prev->data))
                << std::endl;
      std::cout << "curr->next is "
                << ((t->next == nullptr) ? "nullptr"
                                         : std::to_string(t->next->data))
                << std::endl;
      std::cout << "curr->isactive is " << std::boolalpha << t->isactive
                << std::noboolalpha << std::endl;
      std::cout << "curr->istodel is " << std::boolalpha << t->istodel
                << std::noboolalpha << std::endl;
    } else {
      std::cout << "current node is nullptr!" << std::endl;
    }
  }
};
#endif  // !MYLIST_H_
