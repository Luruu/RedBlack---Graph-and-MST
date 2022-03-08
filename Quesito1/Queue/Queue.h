#ifndef QUEUE_H
#define QUEUE_H

template <template<class> class NT, class T>
class Queue {
    private:
        NT<T> *top;
        NT<T> *bottom;
    public:
        Queue<NT,T>():top{nullptr},bottom{nullptr}{}
        ~Queue<NT,T>();

        T *dequeue();
        void enqueue(T *element);

        bool isEmpty(){return top == nullptr;}
};

template <template<class> class NT, class T>
void Queue<NT,T>::enqueue(T *element){
    NT<T> *tmp = new NT<T>();
    tmp->setElement(element);
    if (isEmpty())
        top = tmp;
    else
        bottom->setNext(tmp);
    bottom = tmp;
}

template <template<class> class NT, class T>
T *Queue<NT,T>::dequeue(){
    T *out = nullptr;
    NT<T> *tmp = nullptr;
    
    if(!isEmpty()){
        out = top->getElement();
        tmp = top;
        top = top->getNext();
        
        delete tmp;

        if(top == nullptr)
            bottom = nullptr;
    }
    return out;
}

template <template<class> class NT, class T>
Queue<NT,T>::~Queue<NT,T>(){
    while(!isEmpty())
        dequeue();
}

#endif
