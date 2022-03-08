#ifndef RBGRAPH_H
#define RBGRAPH_H

#include <algorithm> 
#include <string>
#include "../Queue/Node.h"
#include "VNode.h"
#include "LinkedList.h"
#include "../Queue/Queue.h"

#include "../TextUtility.h"

#include <fstream>
#include <stdlib.h>

using std::ifstream;

template <class T>
class RBGraph {
    private:
        LinkedList<VNode, T> *VList;
        LinkedList<VNode, T> *getVList(){return VList;}

        enum BFSNodeColors:unsigned char{WHITE, GRAY, BLACK};

        T getMaximum();
        
        VNode<T> *findV(T &u);

        void adjVisit(RBNode<VNode<T>> * r,RBNode<VNode<T>> * NIL, VNode<T> *u, Queue<Node, VNode<T>> *Q);
        void print_allV_notVisited();
    public:
        RBGraph<T>():VList{new LinkedList<VNode, T>()}{}
        ~RBGraph<T>(){delete VList;}

        bool addV(T &data);
        bool addEdge(T &u, T &v);
        bool findEdge(T &u, T &v);
        bool removeEdge(T &u, T &v);

        void BFS(T &s_data);

        string getAllV();
};

template <class T>
bool RBGraph<T>::addV(T &data){
    const bool NOT_EXISTS = (findV(data) == nullptr);
    if (NOT_EXISTS)
        VList->addNode(data);
    return NOT_EXISTS; 
}

template <class T>
VNode<T> *RBGraph<T>::findV(T &u){
    VNode<T> *tmp = VList->getFirst();
    while(tmp!=nullptr && tmp->getData() != u)
        tmp = (VNode<T> *)tmp->getNext();
    return tmp;
}

template <class T>
bool RBGraph<T>::addEdge(T &u, T &v){
    VNode<T> *u_node = findV(u), *v_node = findV(v);
    
    return (u_node != nullptr && v_node != nullptr) && u_node->getAdjTree()->insertNode(v_node); 
}

template <class T>
bool RBGraph<T>::findEdge(T &u, T &v){
    VNode<T> *u_node = findV(u);
    RBTree<VNode,T> *RBTree_Unode;
    if(u_node != nullptr){
        RBTree_Unode = u_node->getAdjTree();
        if (RBTree_Unode->searchNode(RBTree_Unode->getRoot(), v) != RBTree_Unode->getNIL()) 
            return true; 
    }
    return false;
}

template <class T>
bool RBGraph<T>::removeEdge(T &u, T &v){
    VNode<T> *u_node = findV(u);
    RBTree<VNode,T> *RBTree_Unode;
    RBNode<VNode<T>> *adj; 
    if(u_node != nullptr){
        RBTree_Unode = u_node->getAdjTree();
        adj = (RBNode<VNode<T>> *)RBTree_Unode->searchNode(RBTree_Unode->getRoot(), v);
        if (adj != RBTree_Unode->getNIL()){
            RBTree_Unode->deleteNode(adj);
            return true;
        }
    }
    return false;
}

template <class T>
T RBGraph<T>::getMaximum(){
    return std::numeric_limits<T>::max();
}

template <class T>
void RBGraph<T>::BFS(T &s_data){
    VNode<T> *u = VList->getFirst();
    VNode<T> *s = findV(s_data);
    if (s == nullptr){ cout << "ERROR: S DOES NOT EXSISTS!" << endl; return;}
    while (u != nullptr){
        if(u->getData() != s_data){
            u->setColor(WHITE);
            u->setParent(nullptr);
            u->setDistance(getMaximum()); //d[u] = infinity
        }
        u = u->getNext();
    }
    s->setColor(GRAY);
    s->setDistance(0);
    s->setParent(nullptr);
    Queue<Node,VNode<T>> *Q = new Queue<Node,VNode<T>>();
    Q->enqueue(s);
    cout << endl << "\t    BFS VISIT" << endl;
    while(!Q->isEmpty()){
        u = Q->dequeue();
        cout << "V: " << u->getData() << "(d:" << u->getDistance() << ")\t" << "Adj: ";
        RBTree<VNode,T> *adj_u = u->getAdjTree();
        adjVisit(adj_u->getRoot(),adj_u->getNIL(),u,Q); //visit adj tree of u
        cout << endl;
        u->setColor(BLACK);
    }
    print_allV_notVisited(); 
}
template <class T> //a preorder visit
void RBGraph<T>::adjVisit(RBNode<VNode<T>> *r,RBNode<VNode<T>> *NIL, VNode<T> *u,Queue<Node, VNode<T>> *Q){
    if (r != NIL){
        VNode<T> *v = r->getKey();
        if(v->getColor() == WHITE){
            cout << v->getData() << "[WHITE]   ";
            v->setColor(GRAY);
            v->setParent(u);
            v->setDistance(u->getDistance()+1);
            Q->enqueue(v);
        }
        else if(v->getColor() == GRAY)
            cout << v->getData() << "[GRAY]   ";
        else
            cout << v->getData() << "[BLACK]   ";
        adjVisit(r->getLeft(), NIL,u,Q);
        adjVisit(r->getRight(),NIL,u,Q);
    }
}

template <class T>
void RBGraph<T>::print_allV_notVisited(){
    cout << endl << "NODE DOES NOT VISITED:   ";
    VNode<T> * tmpU = this->getVList()->getFirst();
    RBTree<VNode,T> * tmpV = nullptr;
    bool none = true;
    while(tmpU != nullptr){
        if (tmpU->getColor() == WHITE)
            none = false,
            cout << tmpU->getData() << "    ";
        tmpU = tmpU->getNext();
    } 
    if (none)
        cout << "NONE!";
    cout <<endl;
}

template <class T>
string RBGraph<T>::getAllV(){
    VNode<T> *tmp = VList->getFirst();
    string output = "";
    while(tmp!=nullptr){
        output += std::to_string(tmp->getData()) + "  ";
        tmp = tmp->getNext();
    }
    return output;
}

#endif