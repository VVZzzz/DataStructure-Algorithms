#pragma once
//���ļ�����Hashɢ�б���,����ΪEmployee��.
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
  //���Թ��캯��
  std::cout << "\n����MyHashSeperateĬ�Ϲ��캯��" << std::endl;
  //MyHashSeparate<std::string> str_hash;
  MyHashSeparate<int> int_hash;
  //str_hash.printInfo();
  int_hash.printInfo();
  //����insert����,����rehash()����.
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
