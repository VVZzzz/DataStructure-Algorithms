#ifndef DATASTRUCTURE_ALGORITHM_LIBRARY_H
#define DATASTRUCTURE_ALGORITHM_LIBRARY_H

template< typename Comparable >
class BinarySeachTree {
public:
	BinarySeachTree();
	BinarySeachTree( const BinarySeachTree &rhs );
	~BinarySeachTree();
	const Comparable &findMin() const;
	const Comparable &findMax() const;
	bool contains( const Comparable &x ) const;
	bool isEmpty() const;
	void printTree() const;
	
	void makeEmpty();
	void insert( const Comparable &x );
	void remove( const Comparable &x );
	
	const BinarySeachTree &operator=( const Comparable &rhs );

private:
	struct BinaryNode {
		Comparable element;
		BinaryNode *lchild;
		BinaryNode *rchild;
		
		BinaryNode( const Comparable &value, BinaryNode *l, BinaryNode *r ) :
				element( value ), lchild( l ), rchild( r ) {}
	};
	
	BinaryNode *root;
	
	void insert( const Comparable &x, BinaryNode *&t ) const;
	void remove( const Comparable &x, BinaryNode *&t ) const;
	BinaryNode *findMin( BinaryNode *t ) const;
	BinaryNode *findMax( BinaryNode *t ) const;
	bool contains( const Comparable &x, BinaryNode *t ) const;
	void makeEmpty( BinaryNode *&t );
	void printTree( BinaryNode *t );
	BinaryNode *clone( BinaryNode *t ) const;
};

#endif