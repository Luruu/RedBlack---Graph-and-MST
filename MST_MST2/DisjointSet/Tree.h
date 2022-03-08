#ifndef TREE_H
#define TREE_H
template <class NT>
class Tree {
    private:
        NT *root;
        Tree<NT> *next; //next tree
        Tree<NT> *before; //before tree
    public:
        Tree<NT>(NT *root):next{nullptr},before{nullptr}{setRoot(root); root->setParent(root);}
        virtual ~Tree<NT>(){}
        void setRoot(NT *root){this->root = root;}
        NT *getRoot(){return root;}

        void setNext(Tree<NT> *next){this->next = next;}
        Tree<NT> *getNext(){return next;}
        void setBefore(Tree<NT> *before){this->before = before;}
        Tree<NT> *getBefore(){return before;}
};

#endif 
