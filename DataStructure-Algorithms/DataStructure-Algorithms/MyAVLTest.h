#pragma once
//此文件测试二叉平衡树(AVL)类
#include <iostream>
#include <vector>
#include "MyAVL.h"
void avl_test() {
  //测试AVL默认构造函数
  std::cout << "测试AVL默认构造函数" << std::endl;
  AVLTree<int> avl_tree;
  std::cout << "树的高度为: " << avl_tree.getHeight() << std::endl;
  avl_tree.print_tree();

  //测试insert函数
  std::vector<int> ivec = {2, 1, 4, 5, 9, 3, 6, 7};
  std::cout << "\n测试insert函数" << std::endl;
  for (auto i : ivec) {
    avl_tree.insert(i);
    std::cout << "\n\n树的高度为: " << avl_tree.getHeight() << std::endl;
    avl_tree.print_tree();
  }

  //测试remove函数,remove {5,1,2,3}
  std::cout << "\n测试remove函数" << std::endl;
  std::vector<int> remove_ivec = {5, 1, 2, 3};
  for (auto i : remove_ivec) {
    avl_tree.remove(i);
    std::cout << "\n\n树的高度为: " << avl_tree.getHeight() << std::endl;
    avl_tree.print_tree();
  }
  /*
  在即将删除3时
     4
   3   7
      6  9
  对于这种情况,可以对4的节点进行右单旋或者右双旋,在rightBalance()函数中,我们采取右双旋.
  */

  //测试insert_iteration函数
  std::vector<int> ivec1 = {2, 1, 4, 5, 9, 3, 6, 7};
  AVLTree<int> avl_tree1;
  std::cout << "\n测试insert_iteration函数" << std::endl;
  for (auto i : ivec1) {
    avl_tree1.insert_iteration(i);
    std::cout << "\n\n树的高度为: " << avl_tree1.getHeight() << std::endl;
    avl_tree1.print_tree();
  }

  //测试isBalanced()函数
  std::cout << "\n测试isBalanced()函数" << std::endl;
  std::cout << "是否为AVL树: " << std::boolalpha << avl_tree1.isBalanced()
            << std::noboolalpha << std::endl;

  //测试generate_min_H()函数
  std::cout << "\n测试generate_min_H()函数" << std::endl;
  for (int i = 1; i < 10; i++) {
    std::cout << "\n\n生成高度为" << i << "的树: \n" << std::endl;
    avl_tree1.generate_min_H(i);
  }
}
