#pragma once
//���ļ����Զ���ƽ����(AVL)��
#include <iostream>
#include "MyAVL.h"
void avl_test() {
	//����AVLĬ�Ϲ��캯��
    std::cout << "����AVLĬ�Ϲ��캯��" << std::endl;
    AVLTree<int> avl_tree;
    std::cout << "���ĸ߶�Ϊ: " << avl_tree.getHeight() <<std::endl;
    avl_tree.print_tree();

	//����insert����
    std::cout << "\n����insert����" << std::endl;
    avl_tree.insert(2);
    std::cout << "���ĸ߶�Ϊ: " << avl_tree.getHeight() <<std::endl;
    avl_tree.print_tree();
}
