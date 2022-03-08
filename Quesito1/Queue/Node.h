#ifndef NODE_H
#define NODE_H

template <class NT>
class Node{
    private:
        Node<NT> *next;
        NT *element;
    public:
        Node<NT>():next{nullptr}{}
        virtual ~Node<NT>(){}
        void setNext(Node<NT> * next) { this->next = next;}
        Node<NT> *getNext(){return next;}
        void setElement(NT *element){this->element = element;}
        NT *getElement(){return element;}
};

#endif 
