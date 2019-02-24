#pragma once
//此文件测试二叉平衡树(AVL)类
#include <iostream>
#include "MyAVL.h"
void avl_test() {
	//测试AVL默认构造函数
    std::cout << "测试AVL默认构造函数" << std::endl;
    AVLTree<int> avl_tree;
    std::cout << "树的高度为: " << avl_tree.getHeight() <<std::endl;
    avl_tree.print_tree();

	//测试insert函数
    std::cout << "\n测试insert函数" << std::endl;
    avl_tree.insert(2);
    std::cout << "树的高度为: " << avl_tree.getHeight() <<std::endl;
    avl_tree.print_tree();
}
