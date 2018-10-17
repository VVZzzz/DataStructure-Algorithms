#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "MySort.h"
int main() {
  std::vector<int> res = {31, 41, 59, 26, 53, 58, 97, 88,
                          65, 76, 45, 76, 34, 23, 45};
  std::vector<int> temp = {31, 41, 59, 26, 53, 58, 97, 88};
  std::vector<int> temp2 = {3};
  std::vector<int> temp3 = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
  std::vector<int> temp4 = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
  // MySort::heapSort(res);
  // MySort::insertionSort(res);
  // MySort::shellSort(res);
  // MySort::mergeSort(res);
  // MySort::quickSort(res);
  // MySort::quickSelect(res, 0, res.size()-1, 2);
  int mid =
      MySort::mid_AUB(temp3, 0, temp3.size() - 1, temp4, 0, temp4.size() - 1);
  std::cout << mid << std::endl;
  /*
  MySort::quickSort2(res);
  for (auto i : res) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  */
  system("pause");
  return 0;
}