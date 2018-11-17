#ifndef MYVECTOR_H_
#define MYVECTOR_H_

template <typename Object>
class MyVector;
//没有适配范围for
template <typename Object>
class const_Iterator {
  friend class MyVector<Object>;

 public:
  const Object &operator*() const { return retrieve(); }
  const_Iterator &operator++() {
    current++;
    return *this;
  }
  const_Iterator &operator++(int) {
    const_Iterator old = *this;
    ++(*this);
    return old;
  }
  const_Iterator &operator+(int k) {
    const_Iterator advanced = *this;
    for (size_t i = 0; i < k; i++) {
      ++advanced;
    }
    return advanced;
  }

  bool operator==(const const_Iterator &rhs) const {
    return current == rhs.current;
  }
  bool operator!=(const const_Iterator &rhs) const {
    return !(current == rhs.current);
  }

 protected:
  Object *current;
  const MyVector<Object> *theVect;
  Object &retrieve() const {
    assertIsValid();
    return *current;
  }
  // protect保护构造函数
  const_Iterator(const MyVector<Object> *vect, Object *p)
      : theVect(vect), current(p) {}

  void assertIsValid() const {
    if (theVect == nullptr || current == nullptr) {
      throw std::invalid_argument("pointer is nullptr.");
    }
  }
};

template <typename Object>
class Iterator : public const_Iterator<Object> {
  friend class MyVector<Object>;

 public:
  Object &operator*() { return retrieve(); }
  const Object &operator*() const { return const_Iterator::retrieve(); }
  Iterator &operator++() {
    // std::cout << "old " << *current << " ";
    current++;
    return *this;
  }
  Iterator operator++(int) {
    Iterator old = *this;
    ++(*this);
    return old;
  }

 protected:
  Iterator(const MyVector<Object> *vect, Object *p) : const_Iterator(vect, p) {}
};

template <typename Object>
class MyVector {
  // typedef Object * Iterator;
  // typedef const Object * const_Iterator;
 public:
  explicit MyVector(int initsize = 0)
      : m_Size(initsize),
        m_Capacity(initsize + SPARE_CAPACITY),
        m_pobjects(new Object[m_Capacity]()) {
#ifdef TEST_VECTOR
    printInfo();
#endif
  }

  MyVector(const MyVector &rhs) : m_pobjects(NULL) { operator=(rhs); }

  MyVector &operator=(const MyVector &rhs) {
    if (&rhs != this) {
      delete[] m_pobjects;
      m_Size = rhs.m_Size;
      m_Capacity = rhs.m_Capacity;
      m_pobjects = new Object[m_Capacity];
      auto temp = m_pobjects;
      auto temp_rhs = rhs.m_pobjects;
      for (int i = 0; i != m_Size; i++) {
        *temp++ = *temp_rhs++;
      }
    }
    return *this;
  }

  void resize(int resz) {
    if (resz > m_Size) reserve(2 * resz + 1);
    m_Size = resz;
  }

  void reserve(int recapacity) {
    if (recapacity < m_Capacity)  //不允许保留空间小于旧的空间
      return;
    Object *newpobjects = new Object[recapacity];
    auto temp_new = newpobjects;
    auto temp = m_pobjects;
    for (int i = 0; i != m_Size; i++) {
      *temp_new++ = *temp++;
    }
    delete[] m_pobjects;
    m_pobjects = newpobjects;
    m_Capacity = recapacity;
  }

  Object &operator[](unsigned int i) {
    if (i < m_Size)
      return *(m_pobjects + i);
    else
      throw std::out_of_range("out of range!");
  }

  const Object &operator[](unsigned int i) const {
    if (i < m_Size)
      return *(m_pobjects + i);
    else
      throw std::out_of_range("out of range!");
  }

  bool empty() const { return m_Size == 0; }
  int size() const  //无需返回const,只需后置const即可
  {
    return m_Size;
  }
  int capacity() const { return m_Capacity; }

  void push_back(Object obj) {
    if (m_Size + 1 > m_Capacity) reserve(2 * m_Size + 1);
    m_pobjects[m_Size++] = obj;
  }
  void pop_back() { --m_Size; }
  Iterator<Object> insert(Iterator<Object> pos, const Object &x) {
    // Object *iter = &m_pobjects[0];
    Iterator<Object> iter = this->begin();
    Object *oldArray = m_pobjects;
    m_Size++;
    int i = 0;
    if (m_Capacity < m_Size) {
      m_Capacity = m_Size;
    }
    m_pobjects = new Object[m_Capacity];
    while (iter != pos) {
      m_pobjects[i] = oldArray[i];
      iter++;
      i++;
    }
    m_pobjects[i] = x;
    for (int k = i + 1; k < m_Size; k++) {
      m_pobjects[k] = oldArray[k - 1];
    }
    delete[] oldArray;
    return Iterator<Object>(this, m_pobjects + i);
  }
  Iterator<Object> erase(Iterator<Object> pos) {
    if (begin() == end() || pos == end()) {
      return end();
    }
    // Object *iter = pos, *niter = pos + 1;
    // Object *res = pos;
    Iterator<Object> iter = pos, res = pos, niter = ++pos;
    while (niter != end()) {
      *iter = *niter;
      iter++;
      niter++;
    }
    // delete	niter;
    // erase和clear不回收内存
    m_Size--;
    return res;
  }
  const Object &back() const { return m_pobjects[m_Size - 1]; }

  /*
  Iterator begin()
  {
          return &m_pobjects[0];
  }
     const const_Iterator begin() const
  {
          return const &m_pobjects[0];
  }

  Iterator end()
  {
          return &m_pobjects[m_Size-1];
  }

  const const_Iterator end() const
  //此处无需前置的const，只需后置const是this指针为const即可
  {
          return &m_pobjects[m_Size-1];
  }
  */
  Iterator<Object> begin() { return Iterator<Object>(this, &m_pobjects[0]); }
  const_Iterator<Object> begin() const {
    return const_Iterator(this, &m_pobjects[0]);
  }
  Iterator<Object> end() { return Iterator<Object>(this, &m_pobjects[size()]); }
  const_Iterator<Object> end() const {
    return const_Iterator<Object>(this, &m_pobjects[size()]);
  }

  const enum { SPARE_CAPACITY = 16 };

  void printInfo() {
    std::cout << "m_Size: " << m_Size << std::endl;
    std::cout << "m_Capacity: " << m_Capacity << std::endl;
    std::cout << std::boolalpha
              << "m_pobjects is nullptr? : " << (m_pobjects == nullptr)
              << std::noboolalpha << std::endl;
    std::cout << "current elements is :" << std::endl;
    for (int i = 0; i < m_Size; i++) std::cout << *(m_pobjects + i) << " ";
    std::cout << std::endl;
  }

 private:
  int m_Size;
  int m_Capacity;
  Object *m_pobjects;
};
#endif  // !MYVECTOR_H_
