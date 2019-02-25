#pragma once
//���ļ����Զ���ƽ����(AVL)��
#include <iostream>
#include <vector>
#include "MyAVL.h"
void avl_test() {
  //����AVLĬ�Ϲ��캯��
  std::cout << "����AVLĬ�Ϲ��캯��" << std::endl;
  AVLTree<int> avl_tree;
  std::cout << "���ĸ߶�Ϊ: " << avl_tree.getHeight() << std::endl;
  avl_tree.print_tree();

  //����insert����
  std::vector<int> ivec = {2, 1, 4, 5, 9, 3, 6, 7};
  std::cout << "\n����insert����" << std::endl;
  for (auto i : ivec) {
    avl_tree.insert(i);
    std::cout << "\n\n���ĸ߶�Ϊ: " << avl_tree.getHeight() << std::endl;
    avl_tree.print_tree();
  }

  //����remove����,remove {5,1,2,3}
  std::cout << "\n����remove����" << std::endl;
  std::vector<int> remove_ivec = {5, 1, 2, 3};
  for (auto i : remove_ivec) {
    avl_tree.remove(i);
    std::cout << "\n\n���ĸ߶�Ϊ: " << avl_tree.getHeight() << std::endl;
    avl_tree.print_tree();
  }
  /*
  �ڼ���ɾ��3ʱ
     4
   3   7
      6  9
  �����������,���Զ�4�Ľڵ�����ҵ���������˫��,��rightBalance()������,���ǲ�ȡ��˫��.
  */

  //����insert_iteration����
  std::vector<int> ivec1 = {2, 1, 4, 5, 9, 3, 6, 7};
  AVLTree<int> avl_tree1;
  std::cout << "\n����insert_iteration����" << std::endl;
  for (auto i : ivec1) {
    avl_tree1.insert_iteration(i);
    std::cout << "\n\n���ĸ߶�Ϊ: " << avl_tree1.getHeight() << std::endl;
    avl_tree1.print_tree();
  }

  //����isBalanced()����
  std::cout << "\n����isBalanced()����" << std::endl;
  std::cout << "�Ƿ�ΪAVL��: " << std::boolalpha << avl_tree1.isBalanced()
            << std::noboolalpha << std::endl;

  //����generate_min_H()����
  std::cout << "\n����generate_min_H()����" << std::endl;
  for (int i = 1; i < 10; i++) {
    std::cout << "\n\n���ɸ߶�Ϊ" << i << "����: \n" << std::endl;
    avl_tree1.generate_min_H(i);
  }
}
