#pragma once
//���ļ���������BinarySearchTree��
#include <iostream>
#include <vector>
#include "MyTree.h"

void bst_test() {
  //����BSTĬ�Ϲ��캯��
  std::cout << "����BSTĬ�Ϲ��캯��" << std::endl;
  BinarySearchTree<int> bst;
  bst.printTree();
  std::cout << std::endl;

  //����insert����
  std::cout << "\n����BST::insert()" << std::endl;
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

  //����findMax(),findMin(),contains()����
  std::cout << "\n����findMax(),findMin(),contains()" << std::endl;
  std::cout << "findMax()'s result: " << bst.findMax() << std::endl;
  std::cout << "findMin()'s result: " << bst.findMin() << std::endl;
  std::cout << "contains(10)'s result: " << std::boolalpha << bst.contains(10)
            << std::noboolalpha << std::endl;
  std::cout << "contains(5)'s result: " << std::boolalpha << bst.contains(5)
            << std::noboolalpha << std::endl;

  //����remove,remove_leaves����
  std::cout << "\n����remove(),remove_leaves()" << std::endl;
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
  //�˴���remove_leaves�Ĳ�����Ҫ(BinarySearchTree *&t)
  //��ָ�������,������ÿ�εݹ�ʱ����ָ��Ŀ���,���޷���Ϊnullptr
  bst_temp2.remove_leaves();
  bst_temp2.printTree();

  //���Կ�������(clone())����
  std::cout << "\n����BST::BST(const BST &)" << std::endl;
  BinarySearchTree<int> bst_temp3(bst);
  bst_temp3.printTree();
  std::cout << std::endl;

  //����makeEmpty()����
  std::cout << "\n����BST::makeEmpty()" << std::endl;
  bst_temp3.makeEmpty();
  bst_temp3.printTree();
  std::cout << std::endl;

  //����countNodes(),countLeaves(),countFullNodes()����
  std::cout << "\n����countNodes(),countLeaves(),countFullNodes()" << std::endl;
  bst.printTree();
  std::cout << "\ncountNodes()'s result: " << bst.countNodes() << std::endl;
  std::cout << "countLeaves()'s result: " << bst.countLeaves() << std::endl;
  std::cout << "countFullNodes()'s result: " << bst.countFullNodes()
            << std::endl
            << std::endl;

  //����printRange(const T &low, const T &up);
  std::cout << "\n����printRange(low,up)" << std::endl;
  bst.printRange(3, 7);

  //����ǰ�к�ݹ����
  std::cout << "\n����PreOrder" << std::endl;
  bst.preOrder();
  std::cout << "\n����InOrder" << std::endl;
  bst.inOrder();
  std::cout << "\n����PostOrder" << std::endl;
  bst.postOrder();

  //����ǰ�к�ǵݹ����
  std::cout << "\n����PreOrderNoRecur" << std::endl;
  bst.preOrderNoRecur();
  std::cout << "\n����InOrderNoRecur" << std::endl;
  bst.inOrderNoRecur();
  std::cout << "\n����PostOrderNoRecur" << std::endl;
  bst.postOrderNoRecur();

  //���Բ������
  std::cout << "\n����levelOrder" << std::endl;
  bst.levelOrder();

  //��������汾��insert remove contains findMin findMax
  //����lazy_insert()
  std::cout << "\n����lazy_insert()" << std::endl;
  BinarySearchTree<int> lazy_bst;
  std::vector<int> ivec{5, 2, 3, 4, 1, 7};
  for (int i : ivec) lazy_bst.lazy_insert(i);
  lazy_bst.printTree();
  //����lazy_remove()
  std::cout << "\n����lazy_remove()" << std::endl;
  //lazy_bst.lazy_remove(5);
  //lazy_bst.lazy_remove(1);
  //lazy_bst.lazy_findMax();
  //lazy_bst.lazy_findMin();
  for (int i = 0; i < ivec.size() / 2; i++) lazy_bst.lazy_remove(ivec[i]);
  //lazy_bst.lazy_remove(2);
  //lazy_bst.lazy_remove(3);
  //lazy_bst.lazy_remove(4);
  lazy_bst.printTree();
}