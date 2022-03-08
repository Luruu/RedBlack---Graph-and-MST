#ifndef LINKED_LIST_H
#define LINKED_LIST_H


template <template<class> class NT, class T>
class LinkedList {
private:
    NT<T> *first;
    NT<T> *last;
public:
    LinkedList<NT, T>():first{nullptr},last{nullptr}{}
    ~LinkedList<NT, T>(){NT<T> *tmp = first , *t; while(tmp != nullptr)t = tmp, tmp->getNext(), delete []t;}
    NT<T> *addNode(T *data);
    NT<T> *getFirst(){return first;}
    NT<T> *getLast(){return last;}
};

template <template<class> class NT, class T>
NT<T> *LinkedList<NT, T>::addNode(T *data) {
    NT<T> *tmp = new NT<T>(data);
    if (first == nullptr) 
        first = tmp; 
    else 
        last->setNext(tmp);
    last = tmp;
    
    return tmp; 
}
#endif