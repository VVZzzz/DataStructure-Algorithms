#pragma once
//此文件测试Hash散列表类,数据为Employee类.
#define HASH_PROBING_TEST
#define SQUARE_DETECT_HASH
#include <time.h>
#include <ostream>
#include <random>
#include <string>
#include <vector>
#include "MyHashProbing.h"
#include "MyHashSeparateChain.h"
class Employee {
  friend std::ostream& operator<<(std::ostream& os, const Employee& rhs);

 public:
  Employee() : name(), salary(0) {}
  Employee(const std::string& sname, double ds = 0) : name(sname), salary(ds) {}
  bool operator==(const Employee& rhs) { return rhs.name == name; }
  bool operator!=(const Employee& rhs) { return !(*this == rhs); }
  const std::string& getName() { return name; }

 private:
  std::string name;
  double salary;
};
std::ostream& operator<<(std::ostream& os, const Employee& rhs) {
  os << rhs.name << " " << rhs.salary;
  return os;
}

void hash_test() {
  //测试构造函数
#ifdef HASH_SEPERATE_CHAIN_TEST
  std::cout << "\n测试MyHashSeperate默认构造函数" << std::endl;
  MyHashSeparate<int> int_hash;
  // MyHashSeparate<std::string> str_hash;
#endif
#ifdef HASH_PROBING_TEST
  std::cout << "\n测试MyProbingHash默认构造函数" << std::endl;
  MyProbingHash<int> int_hash;
#else
  std::cout << "\n测试MyHashSeperate默认构造函数" << std::endl;
  MyHashSeparate<int> int_hash;
#endif
  // str_hash.printInfo();
  int_hash.printInfo();

  //测试insert函数,包含rehash()函数.
  /*
  std::vector<std::string> s_vec{"Hash", "seperate", "Chain", ".h", "cpp"};
  for (auto& c : s_vec) str_hash.insert(c);
  str_hash.printInfo();
  std::cout << std::endl;
  */
  std::cout << "\n测试insert函数" << std::endl;
  //先生成随机数数据[0,500]的随机数
  std::random_device rd;

  //若用time(nullptr)作为随机数种子,只能精确到秒级,故用random_device
  // std::default_random_engine random(time(nullptr));
  std::default_random_engine random(rd());
  std::uniform_int_distribution<int> num(1, 500);
  for (int i = 0; i < int_hash.getTableSize(); i++) {
    int_hash.insert(num(random));
  }
  int_hash.printInfo();

  //测试rehash()函数,当currentSize>tableSize时进行rehash()
  std::cout << "\n测试rehash()函数" << std::endl;
  for (int i = 0; i < 200; i++) {
    int_hash.insert(num(random));
  }
  int_hash.printInfo();

  //测试contains()函数
  std::cout << "\n测试contains()函数" << std::endl;
  int tmp = num(random);
  std::cout << tmp << " contains " << std::boolalpha << int_hash.contains(tmp)
            << std::noboolalpha << std::endl;

  //测试remove()函数
  std::cout << "\n测试remove()函数" << std::endl;
  int tmp2 = num(random);
  std::cout << tmp2 << " reomve " << std::boolalpha << int_hash.remove(tmp2)
            << std::noboolalpha << std::endl;
}
