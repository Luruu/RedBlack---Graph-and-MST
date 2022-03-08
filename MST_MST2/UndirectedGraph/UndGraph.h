#ifndef UND_GRAPH_H
#define UND_GRAPH_H

#include "VNode.h"
#include "ENode.h"

#include "../LinkedList.h"
#include "../DisjointSet/DisjointCollection.h"

#include "../MergeSort.h"

#include "../TextUtility.h"

#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>

using std::ifstream;

template <class T>
class UndGraph {
    private:
        LinkedList<VNode, T> *VList;
        vector<ENode<VNode<T>> *> Elist;
        VNode<T> *findV(T *u);
        
        auto MST_Kruskal();
        auto MST2(vector<ENode<VNode<T>> *>);
    public:
        UndGraph<T>():VList{new LinkedList<VNode, T>()}{}
        ~UndGraph<T>(){delete VList; for(auto &node:Elist) delete node;}

        bool addV(T *data);
        bool addEdge(T *u, T *v, unsigned short w);
        bool findEdge(T *u, T *v);
        bool removeEdge(T *u, T *v);

        void OUT_MST_MST2(string &A, string &B);
        
        string getAllV();
};

template <class T>
bool UndGraph<T>::addV(T *data){
    const bool NOT_EXISTS = (findV(data) == nullptr);
    if (NOT_EXISTS)
        VList->addNode(data);
    return NOT_EXISTS; 
}

template <class T>
VNode<T> *UndGraph<T>::findV(T *u){
    VNode<T> *tmp = this->VList->getFirst();
    while(tmp!=nullptr && tmp->getData() != *u)
        tmp = tmp->getNext();
    return tmp;
}

template <class T>
bool UndGraph<T>::addEdge(T *u, T *v, unsigned short w){
    VNode<T> *u_node = findV(u), *v_node = findV(v);
    if (u_node != nullptr && v_node != nullptr  && !findEdge(u,v)){
        ENode<VNode<T>> *new_node = new ENode<VNode<T>>(u_node, v_node, w);
        Elist.push_back(new_node);
        return true;
    }
    return false;
}


template <class T>
bool UndGraph<T>::findEdge(T *u, T *v){
    for (auto &E_node:Elist)
        if(E_node->getU()->getData() == *u && E_node->getV()->getData() == *v || E_node->getU()->getData() == *v && E_node->getV()->getData() == *u)
            return true;
    return false;
}

template <class T>
bool UndGraph<T>::removeEdge(T *u, T *v){
    for (auto &E_node:Elist)
        if(E_node->getU()->getData() == *u && E_node->getV()->getData() == *v || E_node->getU()->getData() == *v && E_node->getV()->getData() == *u){
            Elist.erase(E_node);
            return true;
        }
    return false; 
    
}


template <class T>
void UndGraph<T>::OUT_MST_MST2(string &A, string &B){
    auto outputKruskal = MST_Kruskal();
    for (auto &it:outputKruskal)
        A += std::to_string(it->getU()->getData()) + "-" +  std::to_string(it->getV()->getData()) +  
                    "->" +  std::to_string(it->getW()) + " ";
    auto outputMST2 = MST2(outputKruskal);
    for (auto &it:outputMST2)
        B += std::to_string(it->getU()->getData()) + "-" +  std::to_string(it->getV()->getData()) +  
                    "->" +  std::to_string(it->getW()) + " ";
}

template <class T>
auto UndGraph<T>::MST_Kruskal(){
    DisjointCollection<VNode<T>> *dSet = new DisjointCollection<VNode<T>>();
    vector<ENode<VNode<T>> *> A;

    
    auto tmpV = VList->getFirst();
    while(tmpV!=nullptr){
        dSet->makeSet(tmpV);
        tmpV = tmpV->getNext();
    }

    MergeSort(Elist,Elist.begin(),Elist.end()-1); 

    unsigned int sumW = 0;
    for(auto &it:Elist){
        auto Vnode_u = it->getU(), Vnode_v = it->getV(); auto w = it->getW();
        if(dSet->findSet(Vnode_u) != dSet->findSet(Vnode_v)){ 
            A.push_back(it);
            sumW+=w;
            dSet->union_xy(Vnode_u,Vnode_v);
        }
    } 
    cout << "peso MST: " << sumW << endl;
    return A;
}

template <class T> 
auto UndGraph<T>::MST2(vector<ENode<VNode<T>> *> A){
    DisjointCollection<VNode<T>> *dSet = new DisjointCollection<VNode<T>>();
    
    
    unsigned int sumW_min = std::numeric_limits<unsigned int>::max(), sumW;
    vector<ENode<VNode<T>> *> B_MIN, B;
    
    for (auto &itMST:A){  
            auto v = VList->getFirst();
            while(v!=nullptr) 
                dSet->makeSet(v),
                v = v->getNext();
        sumW = 0;               
        B.clear();    
        for(auto &it:Elist){
            if(*it != *itMST){ 
                auto Vnode_u = it->getU(), Vnode_v = it->getV(), w = it->getW();
                if(dSet->findSet(Vnode_u) != dSet->findSet(Vnode_v)){ 
                    B.push_back(it);
                    dSet->union_xy(Vnode_u,Vnode_v);
                    sumW += w;
                }
            }
        }
        if (sumW_min > sumW){ //find minimum
            sumW_min = sumW;
            B_MIN = B;
        }
    }
    cout << "peso MST2: " << sumW_min << endl;

    return B_MIN;
}

template <class T>
string UndGraph<T>::getAllV(){
    VNode<T> *tmp = VList->getFirst();
    string output = "";
    while(tmp!=nullptr){
        output += std::to_string(tmp->getData()) + "  ";
        tmp = tmp->getNext();
    }
    return output;
}

#endif