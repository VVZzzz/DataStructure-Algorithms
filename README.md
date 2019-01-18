# DataStructure-Algorithms
# 数据结构与算法分析 C++描述 Ed3
cpp  

Learn DataStructrue-Algorithms.

## 课后习题解析
- [第三章](https://github.com/VVZzzz/DataStructure-Algorithms/blob/master/ch3_test.md)
- [第四章](https://github.com/VVZzzz/DataStructure-Algorithms/blob/master/ch4_test.md)
- [第五章](https://github.com/VVZzzz/DataStructure-Algorithms/blob/master/ch4_test.md)
- [第六章](https://github.com/VVZzzz/DataStructure-Algorithms/blob/master/ch4_test.md)
- [第七章](https://github.com/VVZzzz/DataStructure-Algorithms/blob/master/ch4_test.md)
- [第八章](https://github.com/VVZzzz/DataStructure-Algorithms/blob/master/ch4_test.md)
- [第九章](https://github.com/VVZzzz/DataStructure-Algorithms/blob/master/ch4_test.md)

## 实现数据结构类
1. 数组MyVector
   - 构造,拷贝,析构
   - operator [ ] = 
   - pop_back
   - push_back
   - 迭代器与迭代器操作:begin(), end(), back(), erase(), insert(), resize()等
2. (双向)链表MyList
   - 构造,拷贝,析构
   - operator =
   - push_back
   - push_front
   - insert
   - erase
   - pop_back()
   - pop_front()
   - 迭代器:back front() 反向迭代器
   - 懒惰操作:lazy_erase,懒惰删除.
3. 二叉查找树BinarySearchTree
   - 构造,拷贝,析构
   - insert(),remove()
   - findMax(),findMin(),contains()
   - remove(),remove_leaves(),makeEmpty()
   - countNodes(),countLeaves(),countFullNodes()
   - 前中后递归遍历
   - 前中后非递归遍历
   - 层序遍历
   - 懒惰操作:lazy_insert(),lazy_remove(),lazy_findMin...
   - 判断是否为BST函数