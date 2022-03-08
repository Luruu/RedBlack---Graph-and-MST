#ifndef RBNODE_H
#define RBNODE_H

#include"BinarySearchTree/BSTNode.h"

template <class NT>
class RBNode : public BSTNode<NT> {
    private:
        bool color;
    public:
        RBNode(NT *key):BSTNode<NT>(key){}
        virtual ~RBNode(){}    

        bool getColor(){return color;}
        void setColor(bool color){this->color = color;}
        RBNode<NT> *getParent(){return (RBNode<NT> *) this->getParent();}
        RBNode<NT> *getRight(){return (RBNode<NT> *)  this->getRight();}
        RBNode<NT> *getLeft(){return (RBNode<NT> *)   this->getLeft();}     
};

#endif // RBNODE_H
