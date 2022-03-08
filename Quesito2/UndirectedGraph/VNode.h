#ifndef VNODE_H
#define VNODE_H

template <class T>
class VNode {
    private: 
        T *data;
        VNode<T> *next;

        //for disjoint set
        VNode<T> *parent;
        unsigned short rank;
    public:
        VNode<T>(T *data):next{nullptr},parent{nullptr},rank{0}{this->data = data;}
        virtual ~VNode<T>(){}

        T getData(){return *data;}
        void setData(T *data){this->data = data;}

        VNode<T> *getNext(){return next;}
        void setNext(VNode<T> *next){this->next = next;}

        void setParent(VNode<T> *parent){this->parent = parent;}
        VNode<T> *getParent(){return parent;}
    
        unsigned short getRank(){return rank;}
        void setRank(unsigned short rank){this->rank = rank;}
};


#endif 
