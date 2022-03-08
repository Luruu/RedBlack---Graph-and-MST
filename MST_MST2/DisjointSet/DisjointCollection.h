#ifndef COLLECTION_DISJOINT_H
#define COLLECTION_DISJOINT_H

#include "Tree.h"
#include "../DoublyLinkedList.h"
#include <iostream>

template <class NT>
class DisjointCollection {
private:
    DoublyLinkedList<Tree,NT> *disjointForest;
    Tree<NT> *findTreebyNode(NT *x);
    void link(NT *x,NT *y);
public:
    DisjointCollection<NT>(){disjointForest = new DoublyLinkedList<Tree,NT>();}
    ~DisjointCollection<NT>(){delete disjointForest;}
    
    void makeSet(NT *x);
    NT *findSet(NT *x);
    
    void union_xy(NT *x,NT *y); //"union" is a keyword

    DoublyLinkedList<Tree,NT> *getForest(){return disjointForest;}
};

template <class NT>
void DisjointCollection<NT>::makeSet(NT *x){
    disjointForest->addNode(x);
}


template <class NT>
Tree<NT> *DisjointCollection<NT>::findTreebyNode(NT *x){
    NT *root = findSet(x);
    auto tree = disjointForest->getFirst();
    while(tree !=nullptr){
        if(tree->getRoot() == root)
            return tree;
        tree = tree->getNext();
    }
    return nullptr;
}

template <class NT>
NT *DisjointCollection<NT>::findSet(NT *x){ 
    if (x != x->getParent())
        x->setParent(findSet(x->getParent()));
    return x->getParent();
}

template <class NT>
void DisjointCollection<NT>::link(NT *x,NT *y){ 
    Tree<NT> *treeToRemove; 
    auto rank_x = x->getRank();
    auto rank_y = y->getRank(); 
    if (rank_x > rank_y){
        y->setParent(x);
        treeToRemove = findTreebyNode(y);
    }
    else{
        x->setParent(y);
        if (rank_x == rank_y)
            y->setRank(rank_y+1);
        treeToRemove = findTreebyNode(x);
    }

    disjointForest->removeNode(treeToRemove);
}

template <class NT> 
void DisjointCollection<NT>::union_xy(NT *x,NT *y){
    link(findSet(x),findSet(y));
}


#endif