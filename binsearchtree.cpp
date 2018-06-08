#include <iostream>
#include "binsearchtree.h"

template <typename Comparable>
bool BinarySeachTree::contains(const Comparable &x, BinarySeachTree::BinaryNode *t) const {
    if(t==NULL)
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
