#include <iostream>
#include "binsearchtree.h"

/*
 * 尾递归，也可写为迭代
 */
template <typename Comparable>
bool BinarySeachTree::contains(const Comparable &x, BinarySeachTree::BinaryNode *t) const {
    if(t== nullptr)
        return false;
    else if(x < t->element)
        return contains(x,t->lchild);
    else if(x > t->element)
        return contains(x,t->rchild);
    else
        return true;
}

template <typename Comparable>
bool BinarySeachTree::contains(const Comparable &x) const {
    return contains(x,root);
}

/*
 * 尾递归
 */
template <typename Comparable>
BinaryNode* BinarySeachTree::findMin( BinarySeachTree::BinaryNode *t) const {
    if(t==nullptr)
        return nullptr;
    if(t->lchild== nullptr)
        return t;
    else
        return findMin(t->lchild);
}
/*
 * 迭代
 */
/*
template <typename Comparable>
BinaryNode* BinarySeachTree::findMin(const Comparable &x, BinarySeachTree::BinaryNode *t) const {
    if(t){
        while(t->lchild)
            t=t->lchild;
    }
    return t;
}
*/
template <typename Comparable>
const Comparable & BinarySeachTree::findMax() const {

}
template <typename Comparable>
BinaryNode* BinarySeachTree::findMax( BinarySeachTree::BinaryNode *t ) const {
    if(t==nullptr)
        return nullptr;
    if(t->rchild== nullptr)
        return t;
    else
        return findMin(t->rchild);
}


