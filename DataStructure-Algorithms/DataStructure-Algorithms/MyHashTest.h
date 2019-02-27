#pragma once
//此文件测试Hash散列表类,数据为Employee类.
#include <ostream>
#include <string>
#include <vector>
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
  std::cout << "\n测试MyHashSeperate默认构造函数" << std::endl;
  //MyHashSeparate<std::string> str_hash;
  MyHashSeparate<int> int_hash;
  //str_hash.printInfo();
  int_hash.printInfo();
  //测试insert函数,包含rehash()函数.
  /*
  std::vector<std::string> s_vec{"Hash", "seperate", "Chain", ".h", "cpp"};
  for (auto& c : s_vec) str_hash.insert(c);
  str_hash.printInfo();
  std::cout << std::endl;
  */
  std::vector<int> i_vec(int_hash.getTableSize(),0);
  for (auto& i : i_vec) int_hash.insert(i);
  int_hash.printInfo();
}
