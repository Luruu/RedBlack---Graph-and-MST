#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


template <template<class> class NT, class T>
class DoublyLinkedList {
private:
    NT<T> *first;
    NT<T> *last;
public:
    DoublyLinkedList<NT, T>():first{nullptr},last{nullptr}{}
    ~DoublyLinkedList<NT, T>(){NT<T> *tmp = first , *t; while(tmp != nullptr)t = tmp, tmp->getNext(), delete []t;}
    NT<T> *addNode(T *data);
    bool removeNode(NT<T> *nodeToDelete);
    NT<T> *getFirst(){return first;}
    NT<T> *getLast(){return last;}
};

template <template<class> class NT, class T>
NT<T> *DoublyLinkedList<NT, T>::addNode(T *data) {
    NT<T> *tmp = new NT<T>(data);
    if (first == nullptr) 
        first = tmp; 
    else 
        last->setNext(tmp),
        tmp->setBefore(last);
    last = tmp;
    return tmp; 
}

template <template<class> class NT, class T>
bool DoublyLinkedList<NT, T>::removeNode(NT<T> *nodeToDelete) {
    if(nodeToDelete != nullptr){
        if (first == nodeToDelete)
            first = first->getNext();
        else{  
            auto prev = nodeToDelete->getBefore();
            auto next = nodeToDelete->getNext();
            if(last == nodeToDelete) 
                last = prev;
            else 
                prev->setNext(nodeToDelete->getNext()),
                next->setBefore(nodeToDelete->getBefore());
        }
        delete nodeToDelete;
        return true;
    }
    return false; 
}

#endif