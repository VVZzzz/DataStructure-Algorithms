#ifndef DATASTRUCTURE_ALGORITHM_LIBRARY_H
#define DATASTRUCTURE_ALGORITHM_LIBRARY_H

template <typename Comparable>
class BinarySeachTree{
public:
    BinarySeachTree();
    BinarySeachTree(const BinarySeachTree &rhs);
    ~BinarySeachTree();

    bool contains(const Comparable &x) const ;

private:
    struct BinaryNode{
        Comparable element;
        BinaryNode *lchild;
        BinaryNode *rchild;

        BinaryNode(const Comparable &value,BinaryNode *l,BinaryNode *r):
                element(value),lchild(l),rchild(r) { }
    };

    BinaryNode *root;

    bool contains(const Comparable &x,BinaryNode *t) const ;

};

#endif