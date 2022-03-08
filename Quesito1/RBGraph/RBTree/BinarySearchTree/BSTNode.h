#ifndef TREENODE_H
#define TREENODE_H

template <class NT>
class BSTNode {
    private:
        NT *key;
        BSTNode<NT> *parent;
        BSTNode<NT> *left;
        BSTNode<NT> *right;
    public:
        BSTNode():parent{nullptr}, left{nullptr},right{nullptr}{this->key = new NT();} //used for NIL node
        BSTNode(NT *key):parent{nullptr},left{nullptr},right{nullptr} {this->key=key;}
        virtual ~BSTNode(){}

        NT *getKey(){return key;} 
        void setkey(NT *key){this->key = key;}

        void setParent(BSTNode<NT> *p){parent=p;}
        virtual BSTNode<NT> *getParent(){return parent;}

        void setLeft(BSTNode<NT> *l){left=l;}
        virtual BSTNode<NT> *getLeft(){return left;}

        void setRight(BSTNode<NT> *r){right=r;}
        virtual BSTNode<NT> *getRight(){return right;}

};

#endif
