#ifndef VNODE_H
#define VNODE_H

#include "RBTree/RBTree.h"
template <class T>
class VNode
{
    private: 
        T data;
        RBTree<VNode,T> *AdjTree;
        VNode<T> *next;

        void setMinimum(T &data);
        
        //for BFS visit
        unsigned short distance;
        unsigned short color; 
        VNode<T> *parent;
    public:
        VNode<T>():distance{0},color{0},parent{nullptr},next{nullptr}{AdjTree = nullptr; setMinimum(data);} //Constructor for NIL[T]!!
        VNode<T>(T data):distance{0},color{0},parent{nullptr},next{nullptr}{this->data = data; AdjTree = new RBTree<VNode,T>();}
        virtual ~VNode<T>(){delete AdjTree;}
        unsigned short int getDistance(){return distance;}
        void setDistance(unsigned short int distance){this->distance = distance;}

        unsigned short getColor(){return color;}
        void setColor(unsigned short color){this->color = color;}

        VNode<T> *getParent(){return parent;}
        void setParent(VNode<T> *parent){this->parent = parent;}

        T &getData(){return data;}
        void setData(T &data){this->data = data;}

        RBTree<VNode,T> *getAdjTree(){return AdjTree;}

        VNode<T> *getNext(){return next;}
        void setNext(VNode<T> *next){this->next = next;}
};

template <class T>
void VNode<T>::setMinimum(T &data){
    data = std::numeric_limits<T>::min();
}

#endif 
