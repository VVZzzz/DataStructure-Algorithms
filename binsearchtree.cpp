#include <iostream>
#include "binsearchtree.h"

BinarySeachTree::~BinarySeachTree() {
	makeEmpty();
}

const BinarySeachTree &BinarySeachTree::operator=( const Comparable &rhs ) {
	makeEmpty();
	root = clone( rhs.root );
	return *this;
}

void BinarySeachTree::makeEmpty( BinarySeachTree::BinaryNode *&t ) {
	if ( t != nullptr ) {
		makeEmpty( t->lchild );
		makeEmpty( t->rchild );
		delete t;
	}
	t = nullptr;
}

void BinarySeachTree::makeEmpty() {
	makeEmpty( root );
}

BinarySeachTree::BinaryNode *BinarySeachTree::clone( BinarySeachTree::BinaryNode *t ) const {
	if ( t != nullptr ) {
		return nullptr;
	}
	return new BinaryNode( t->element, clone( t->lchild ), clone( t->rchild ));
}

/*
 * 尾递归，也可写为迭代
 */
template< typename Comparable >
bool BinarySeachTree::contains( const Comparable &x, BinarySeachTree::BinaryNode *t ) const {
	if ( t == nullptr )
		return false;
	else if ( x < t->element )
		return contains( x, t->lchild );
	else if ( x > t->element )
		return contains( x, t->rchild );
	else
		return true;
}

template< typename Comparable >
bool BinarySeachTree::contains( const Comparable &x ) const {
	return contains( x, root );
}

/*
 * 尾递归
 */
template< typename Comparable >
BinaryNode *BinarySeachTree::findMin( BinarySeachTree::BinaryNode *t ) const {
	if ( t == nullptr )
		return nullptr;
	if ( t->lchild == nullptr )
		return t;
	else
		return findMin( t->lchild );
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

template< typename Comparable >
BinaryNode *BinarySeachTree::findMax( BinarySeachTree::BinaryNode *t ) const {
	if ( t ) {
		while ( t->rchild )
			t = t->rchild;
	}
	return t;
	
}
*/


template< typename Comparable >
const Comparable &BinarySeachTree::findMin() const {
	findMin( root );
}

template< typename Comparable >
BinaryNode *BinarySeachTree::findMax( BinarySeachTree::BinaryNode *t ) const {
	if ( t == nullptr )
		return nullptr;
	if ( t->rchild == nullptr )
		return t;
	else
		return findMax( t->rchild );
}

template< typename Comparable >
const Comparable &BinarySeachTree::findMax() const {
	findMax( root );
}

template< typename Comparable >
void BinarySeachTree::insert( const Comparable &x, BinarySeachTree::BinaryNode *&t ) const {
	if ( t == nullptr )
		t = new BinaryNode( x, nullptr, nullptr );
	else if ( x < t->element )
		insert( x, t->lchild );
	else if ( x > t->element )
		insert( x, t->rchild );
	else;
}

template< typename Comparable >
void BinarySeachTree::insert( const Comparable &x ) {
	insert( x, root );
}

template< typename Comparable >
/*
 * 此删除函数效率不高，是因为要两次搜索树得到最小的结点，并删除。
 * 可以将写一个removemin，将这两步骤合起来提高效率*/
void BinarySeachTree::remove( const Comparable &x, BinarySeachTree::BinaryNode *&t ) const {
	if ( t == nullptr )
		return;
	else if ( x < t->element ) {
		remove( x, t->lchild );
	} else if ( x > t->element ) {
		remove( x, t->rchild );
	} else if ( t->lchild && t->rchild ) {
		t->element = findMin( t->rchild )->element;
		remove( t->element, t->rchild );
	} else {
		BinaryNode *oldNode = t;
		t = t->lchild != nullptr ? t->lchild : t->rchild;
		delete oldNode;
	}
}

template< typename Comparable >
void BinarySeachTree::remove( const Comparable &x ) {
	remove( x, root );
}
