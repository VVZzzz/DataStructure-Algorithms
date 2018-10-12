#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "MySort.h"
int main() {
  std::vector<int> res = {31, 41, 59, 26, 53, 58, 97};
  //MySort::heapSort(res);
  //MySort::insertionSort(res);
  //MySort::shellSort(res);
  MySort::mergeSort(res);
  for (auto i : res) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  system("pause");
  return 0;
}