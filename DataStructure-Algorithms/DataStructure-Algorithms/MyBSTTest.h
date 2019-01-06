#pragma once
//此文件用来测试BinarySearchTree类
#include <iostream>
#include <vector>
#include "MyTree.h"

void bst_test() {
  //测试BST默认构造函数
  std::cout << "测试BST默认构造函数" << std::endl;
  BinarySearchTree<int> bst;
  bst.printTree();
  std::cout << std::endl;

  //测试insert函数
  std::cout << "\n测试BST::insert()" << std::endl;
  std::cout << "after insert(5,3,1,4,6,2,7,8)" << std::endl;
  /**
   *    5
   *  3   6
   * 1  4    7
   *  2       8
   */
  std::vector<int> insert_item{5, 3, 1, 4, 6, 2, 7, 8};
  for (auto i : insert_item) bst.insert(i);
  bst.printTree();
  std::cout << std::endl;

  //测试findMax(),findMin(),contains()函数
  std::cout << "\n测试findMax(),findMin(),contains()" << std::endl;
  std::cout << "findMax()'s result: " << bst.findMax() << std::endl;
  std::cout << "findMin()'s result: " << bst.findMin() << std::endl;
  std::cout << "contains(10)'s result: " << std::boolalpha << bst.contains(10)
            << std::noboolalpha << std::endl;
  std::cout << "contains(5)'s result: " << std::boolalpha << bst.contains(5)
            << std::noboolalpha << std::endl;

  //测试remove,remove_leaves函数
  std::cout << "\n测试remove(),remove_leaves()" << std::endl;
  std::cout << "after remove(5): " << std::endl;
  /**
   *    6
   *  3   7
   * 1  4    8
   *  2
   */
  BinarySearchTree<int> bst_temp1(bst);
  bst_temp1.remove(5);
  bst_temp1.printTree();
  std::cout << std::endl;
  std::cout << "after remove_leaves()" << std::endl;
  /**
   *    6
   *  3   7
   *   4    
   *  
   */
  BinarySearchTree<int> bst_temp2(bst);
  //此处的remove_leaves的参数需要(BinarySearchTree *&t)
  //即指针的引用,否则再每次递归时仍是指针的拷贝,而无法置为nullptr
  bst_temp2.remove_leaves();
  bst_temp2.printTree();

  //测试拷贝构造(clone())函数
  std::cout << "\n测试BST::BST(const BST &)" << std::endl;
  BinarySearchTree<int> bst_temp3(bst);
  bst_temp3.printTree();
  std::cout << std::endl;

  //测试makeEmpty()函数
  std::cout << "\n测试BST::makeEmpty()" << std::endl;
  bst_temp3.makeEmpty();
  bst_temp3.printTree();
  std::cout << std::endl;

  //测试countNodes(),countLeaves(),countFullNodes()函数
  std::cout << "\n测试countNodes(),countLeaves(),countFullNodes()" << std::endl;
  bst.printTree();
  std::cout << "\ncountNodes()'s result: " << bst.countNodes() << std::endl;
  std::cout << "countLeaves()'s result: " << bst.countLeaves() << std::endl;
  std::cout << "countFullNodes()'s result: " << bst.countFullNodes()
            << std::endl
            << std::endl;

  //测试printRange(const T &low, const T &up);
  std::cout << "\n测试printRange(low,up)" << std::endl;
  bst.printRange(3, 7);

  //测试层序遍历
  std::cout << "\n测试levelOrder" << std::endl;
  bst.levelOrder();

  //测试懒惰版本的insert remove contains findMin findMax
  //测试lazy_insert()
  std::cout << "\n测试lazy_insert()" << std::endl;
  BinarySearchTree<int> lazy_bst;
  std::vector<int> ivec{5, 2, 3, 4, 1, 7};
  for (int i : ivec) lazy_bst.lazy_insert(i);
  lazy_bst.printTree();

}