#ifndef REDBLACK_H
#define REDBLACK_H

#include"RBNode.h"
#include"BinarySearchTree/BST.h"

// [NT<T>] type node  --  [T] type sentry
template <template<class> class NT, class T>
class RBTree : public BST<NT,T> {
    private:
        RBNode<NT<T>> * NIL;

        void leftRotate(RBNode<NT<T>> * x);
        void rightRotate(RBNode<NT<T>> * x);

        void RB_Transplant(RBNode<NT<T>> *u, RBNode<NT<T>> *v);
        void RB_DELETE_FIXUP(RBNode<NT<T>> *x);

        enum RBNodeColors:bool{BLACK, RED};
    public:
        RBTree():BST<NT,T>(){NIL = (RBNode<NT<T>> *) BST<NT,T>::NIL;  NIL->setColor(BLACK);}
        virtual ~RBTree(){BST<NT,T>::~BST();}

        RBNode<NT<T>> *getRoot(){return (RBNode<NT<T>> *) BST<NT,T>::getRoot();}
        RBNode<NT<T>> *getNIL(){return (RBNode<NT<T>> *) BST<NT,T>::getNIL();}
        void inorderWithParent(RBNode<NT<T>> *x);
        void inorder(RBNode<NT<T>> *x);
        void preorder(RBNode<NT<T>> *x);
        void postorder(RBNode<NT<T>> *x);

        bool insertNode(NT<T> *key); 
        void deleteNode(RBNode<NT<T>> * z);
}; 


template <template<class> class NT, class T>
void RBTree<NT,T>::leftRotate(RBNode<NT<T>> * x){
    RBNode<NT<T>> *y = x->getRight();
    RBNode<NT<T>> *ly = y->getLeft();
    RBNode<NT<T>> *px = x->getParent();

    x->setRight(ly);
    if(ly != NIL)
        ly->setParent(x);
    y->setParent(px);
    if(px == NIL)
        this->setRoot(y);
    else if(x == px->getLeft()) //if x is left child
        px->setLeft(y);
    else
        px->setRight(y);
    y->setLeft(x);
    x->setParent(y);
}
template <template<class> class NT, class T>
void RBTree<NT,T>::rightRotate(RBNode<NT<T>> * x){
    RBNode<NT<T>> *y = x->getLeft();
    RBNode<NT<T>> *ry = y->getRight();
    RBNode<NT<T>> *px = x->getParent();

    x->setLeft(ry);
    if(ry != NIL)
        ry->setParent(x);
    y->setParent(px);
    if(px == NIL)
        this->setRoot(y);
    else if(x == px->getLeft()) //if x is left child
        px->setLeft(y); 
    else
        px->setRight(y); 
    y->setRight(x);
    x->setParent(y);
}

template <template<class> class NT, class T> //CLRS IMPLEMENTATION
bool RBTree<NT,T>::insertNode(NT<T> *key){
    if (BST<NT,T>::searchNode(getRoot(), key->getData()) != NIL) 
        return false; 

    RBNode<NT<T>> *x = (RBNode<NT<T>> *) BST<NT,T>::insertNode(key);
    x->setColor(RED);
    
    RBNode<NT<T>> *y, *px = x->getParent(), *ppx;
  
  
    while(x != getRoot() && px->getColor()==RED){
        px  = x->getParent(); 
        ppx = px->getParent();
        if(px == ppx->getLeft()){ 
            y = ppx->getRight();
            if(y->getColor() == RED){ //[CASE 1]
                px->setColor(BLACK);
                y->setColor(BLACK);
                ppx->setColor(RED);
                x = ppx;
            }
            else {
                if(x==px->getRight()){ //[CASE 2]
                    x = px;
                    leftRotate(x);
                    px = x->getParent(); 
                    ppx = px->getParent();
                } 
                px->setColor(BLACK); //[CASE 3]
            	ppx->setColor(RED);
            	rightRotate(ppx);
            }
        }
        else{  
            y = ppx->getLeft();
            if(y->getColor() == RED){ //[CASE 1]
                px->setColor(BLACK);
                y->setColor(BLACK);
                ppx->setColor(RED);
                x = ppx;
            }
            else {
                if(x==px->getLeft()){ //[CASE 3]
                    x = px;
                    rightRotate(x);
                    px = x->getParent(); 
                    ppx = px->getParent(); 
                }
                px->setColor(BLACK); //[CASE 2]
            	ppx->setColor(RED);
            	leftRotate(ppx);
            }
        }
    }
    getRoot()->setColor(BLACK); 
    return true;
}


template <template<class> class NT, class T>
void RBTree<NT,T>::deleteNode(RBNode<NT<T>> * z) {
    RBNode<NT<T>> *rz = z->getRight();
    RBNode<NT<T>> *lz = z->getLeft();
    RBNode<NT<T>> *x;

    RBNode<NT<T>> *y = z;

    bool y_orig_color = y->getColor();
    
    if(lz == NIL){
        x = rz;
        RB_Transplant(z, rz);
    }
    else if(rz == NIL){
        x = lz;
        RB_Transplant(z, lz);
    }
    else{
        y = (RBNode<NT<T>> *) BST<NT,T>::minimum(rz);
        y_orig_color = y->getColor();
        x = y->getRight();
        if(y->getParent() == z)
            x->setParent(y); 
        else{
            RB_Transplant(y,y->getRight());
            y->setRight(rz);
            y->getRight()->setParent(y);
        }
        RB_Transplant(z,y);
        y->setLeft(lz);
        y->getLeft()->setParent(y);
        y->setColor(z->getColor());
    }
    if(y_orig_color == BLACK) 
        RB_DELETE_FIXUP(x); 
    delete z;
}

template <template<class> class NT, class T>
void RBTree<NT,T>::RB_Transplant(RBNode<NT<T>> *u, RBNode<NT<T>> *v){
    RBNode<NT<T>> *pu = u->getParent();
    if(pu == NIL)
        this->setRoot(v);
    else if (u == pu->getLeft())
        pu->setLeft(v); 
    else
        pu->setRight(v); 
    
    v->setParent(pu); 
}

template <template<class> class NT, class T> 
void RBTree<NT,T>::RB_DELETE_FIXUP(RBNode<NT<T>> *x){ //CLRS IMPLEMENTATION
    
    RBNode<NT<T>> *px  = x->getParent();
    RBNode<NT<T>> *lpx = px->getLeft();  
    RBNode<NT<T>> *rpx = px->getRight(); 
    
    RBNode<NT<T>> *w;
    
    while(x != getRoot() && x->getColor() == BLACK){
        if(x == lpx){ 
            w = rpx; 
            if(w->getColor() == RED){ //[CASE 1]
                w->setColor(BLACK);
                px->setColor(RED);
                leftRotate(px);
                w = rpx;
            }
            if(w->getLeft()->getColor() == BLACK && w->getRight()->getColor() == BLACK){ //[CASE 2]
                w->setColor(RED);
                x = px;
            }
            else{
                if(w->getRight()->getColor() == BLACK){ //[CASE 3]
                    w->getLeft()->setColor(BLACK);
                    w->setColor(RED);
                    rightRotate(w);
                    w = rpx;
                }
                w->setColor(px->getColor()); //[CASE 4]
                px->setColor(BLACK);
                w->getRight()->setColor(BLACK);
                leftRotate(px);
                x = getRoot();
            }
        } 
        else { 
            w = lpx; 
            if(w->getColor() == RED){ //[CASE 1]
                w->setColor(BLACK);
                px->setColor(RED);
                rightRotate(px);
                w = lpx;
            }
            if(w->getLeft()->getColor() == BLACK && w->getRight()->getColor() == BLACK){ //[CASE 2]
                w->setColor(RED);
                x = px;
            }
            else{
                if(w->getLeft()->getColor() == BLACK){ //[CASE 4]
                    w->getRight()->setColor(BLACK);
                    w->setColor(RED);
                    leftRotate(w);
                    w = lpx;
                }
                w->setColor(px->getColor()); //[CASE 3]
                px->setColor(BLACK);
                w->getLeft()->setColor(BLACK);
                rightRotate(px);
                x = getRoot();
            }
        }
    }
    x->setColor(BLACK);
}

template <template<class> class NT, class T>
void RBTree<NT,T>::inorder(RBNode<NT<T>> *x){
    if(x!=NIL){ 
        inorder(x->getLeft());
        string colore = (x->getColor() == 0) ? "BLACK" : "RED";
        cout<<x->getKey()->getData()<<"(" << colore << ")  ";
        inorder(x->getRight());
    }
}

template <template<class> class NT, class T>
void RBTree<NT,T>::inorderWithParent(RBNode<NT<T>> *x){
    if(x!=NIL){ 
        inorderWithParent(x->getLeft());
        string colore = (x->getColor() == 0) ? "BLACK" : "RED";
        if(x->getParent() != NIL)
            cout<<x->getKey()->getData()<<"[" << colore << "]" << "\tparent: " << x->getParent()->getKey()->getData() << endl;
        else
            cout<<x->getKey()->getData()<<"[" << colore << "]" << "\tparent: NULLPTR " << endl;
        inorderWithParent(x->getRight());
    }
}

template <template<class> class NT, class T>
void RBTree<NT,T>::preorder(RBNode<NT<T>> *x){
    if(x!=NIL){
        string colore = (x->getColor() == 0) ? "BLACK" : "RED";
        cout<<x->getKey()->getData()<<"(" << colore << ")  ";
        preorder(x->getLeft());
        preorder(x->getRight());
    }
}

template <template<class> class NT, class T>
void RBTree<NT,T>::postorder(RBNode<NT<T>> *x){
    if(x!=NIL){
        postorder(x->getLeft());
        postorder(x->getRight());
        string colore = (x->getColor() == 0) ? "BLACK" : "RED";
        cout<<x->Data()<<"(" << colore << ")  ";
    }
}

#endif 
