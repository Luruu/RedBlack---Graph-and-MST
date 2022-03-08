#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include"BSTNode.h"

// [NT<T>] Node type  --  [T] sentry type
template <template<class> class NT, class T>
class BST{
    private:
        BSTNode<NT<T>> *root;
    protected: 
        BSTNode<NT<T>> *NIL;
        void transplant(BSTNode<NT<T>> *u, BSTNode<NT<T>> *v); 
    public:
        BST(){NIL = new BSTNode<NT<T>>(); root = NIL;}
        virtual ~BST(){deleteBinarySearchTree(root);}
        void deleteBinarySearchTree(BSTNode<NT<T>> * node);

        virtual BSTNode<NT<T>> *getRoot(){return root;}
        void setRoot(BSTNode<NT<T>> * new_root){root = new_root;}
        virtual BSTNode<NT<T>> *getNIL(){return NIL;}

        BSTNode<NT<T>> *insertNode(NT<T> *key);
        void deleteNode(NT<T> *key);
        virtual void deleteNode(BSTNode<NT<T>> *x); 

        virtual void inorder(BSTNode<NT<T>> *x);   
        virtual void preorder(BSTNode<NT<T>> *x);          
        virtual void postorder(BSTNode<NT<T>> *x);         

        BSTNode<NT<T>> *minimum(BSTNode<NT<T>> *x);
        BSTNode<NT<T>> *maximum(BSTNode<NT<T>> *x);

        BSTNode<NT<T>> *searchNode(BSTNode<NT<T>> *x, T data);
        BSTNode<NT<T>> *searchNodeIterative(BSTNode<NT<T>> *x, T data); 
        BSTNode<NT<T>> *predecessor(BSTNode<NT<T>> *x); 
        BSTNode<NT<T>> *successor(BSTNode<NT<T>> *x);
};

template <template<class> class NT, class T>
BSTNode<NT<T>> * BST<NT,T>::insertNode(NT<T> *key){
    BSTNode<NT<T>> *z=new BSTNode<NT<T>>(key);

    z->setParent(NIL);
    z->setLeft(NIL);
    z->setRight(NIL);

    BSTNode<NT<T>> *y=NIL;
    BSTNode<NT<T>> *x=root;

    while(x!=NIL){
        y=x;
        if(z->getKey()->getData() < x->getKey()->getData())
            x=x->getLeft();
        else
            x=x->getRight();
    }
    
    z->setParent(y);
    if(y==NIL)
        root=z;
    else if(z->getKey()->getData() < y->getKey()->getData())
        y->setLeft(z);
    else
        y->setRight(z);
    return z;
}

template <template<class> class NT, class T>
void BST<NT,T>::inorder(BSTNode<NT<T>> *x){
    if(x!=NIL){
        inorder(x->getLeft());
        cout<<x->getKey()->getData()<<" ";
        inorder(x->getRight());
    }
}
template <template<class> class NT, class T>
void BST<NT,T>::preorder(BSTNode<NT<T>> *x){
    if(x!=NIL){
        cout<<x->getKey()->getData()<<" ";
        inorder(x->getLeft());
        inorder(x->getRight());
    }
}

template <template<class> class NT, class T>
void BST<NT,T>::postorder(BSTNode<NT<T>> *x){
    if(x!=NIL){
        inorder(x->getLeft());
        inorder(x->getRight());
        cout<<x->getKey()->getData()<<" ";
    }
}

template <template<class> class NT, class T>
BSTNode<NT<T>> *BST<NT,T>::minimum(BSTNode<NT<T>> *x){
    while(x->getLeft() != NIL)
        x=x->getLeft();
	return x;
}

template <template<class> class NT, class T>
BSTNode<NT<T>> *BST<NT,T>::maximum(BSTNode<NT<T>> *x){
    while(x->getRight() != NIL)
        x=x->getRight();
	return x;
}
//x: nodo di partenza
template <template<class> class NT, class T>
BSTNode<NT<T>> *BST<NT,T>::searchNode(BSTNode<NT<T>> *x, T data){
    if(x == NIL || data == x->getKey()->getData())
        return x;
    if(data < x->getKey()->getData())
        return searchNode(x->getLeft(), data);
    else
        return searchNode(x->getRight(), data);
}

template <template<class> class NT, class T>
BSTNode<NT<T>> *BST<NT,T>::searchNodeIterative(BSTNode<NT<T>> *x, T data){
    while(x != NIL || data!= x->getKey()->getData())
        if(data < x->getKey()->getData())
            x = x->getLeft();
        else
            x = x->getRight();
    return x;
}

template <template<class> class NT, class T>
BSTNode<NT<T>> *BST<NT,T>::successor(BSTNode<NT<T>> *x){
    if (x->getRight() != NIL)
        return minimum(x->getRight());
    BSTNode<NT<T>> * y = x->getParent();
    while(y != NIL && x == y->getRight()){
        x = y;
        y = y->getParent();
    }
    return y;
}

template <template<class> class NT, class T>
BSTNode<NT<T>> *BST<NT,T>::predecessor(BSTNode<NT<T>> *x){
    if (x->getLeft() != NIL)
        return maximum(x->getLeft());
    
    BSTNode<NT<T>> * y = x->getParent();
    while(y != NIL && x == x->getLeft()){
        x = y;
        y = y->getParent();
    }
    return y;
}

template <template<class> class NT, class T>
void  BST<NT,T>::transplant(BSTNode<NT<T>> *u,BSTNode<NT<T>> *v){
    if (u->getParent() == NIL)
        root = v;
    else if (u == u->getParent()->getLeft()) //if u is left child 
        u->getParent()->setLeft(v);     // left[p[u]] = v
    else
        u->getParent()->setRight(v);    // right[p[u]] = v
    if(v != NIL)
        v->setParent(u->getParent());    //p[v] = p[u]
}

template <template<class> class NT, class T>
void  BST<NT,T>::deleteNode(NT<T> *key){
    BSTNode<NT<T>> * z = searchNode(root, key); //if z is the node to delete
    if(z != NIL) //if node (with key) is not found 
        deleteNode(z);
}

template <template<class> class NT, class T>
void  BST<NT,T>::deleteNode(BSTNode<NT<T>> *z){
    if (z->getLeft() == NIL)
        transplant(z,z->getRight());
    else if (z->getRight() == NIL)
        transplant(z,z->getLeft());
    else{
        BSTNode<NT<T>> * y = minimum(z->getRight());
        if(y->getParent() != z){ //if parent of y is not z
            transplant(y, y->getRight());
            y->setRight(z->getRight());     //right[y] = right[z]
            y->getRight()->setParent(y);    //p[right[y]] = y
        }
        transplant(z,y);
        y->setLeft(z->getLeft());       //left[y] = left[z]
        y->getLeft()->setParent(y);     //p[left[y]] = y
    }
    delete z;
}

template <template<class> class NT, class T>
void BST<NT,T>::deleteBinarySearchTree(BSTNode<NT<T>> * node){
    if(node!=nullptr){
        deleteBinarySearchTree(node->getLeft());
        deleteBinarySearchTree(node->getRight());
        delete node;
    }
}

#endif 