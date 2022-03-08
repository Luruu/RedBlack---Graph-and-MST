#ifndef ENODE_H
#define ENODE_H

template <class T>
class ENode {
    private: 
        T *u;
        T *v;
        unsigned short w;
        unsigned short MaxValue;
    public:
        ENode<T>(T *u, T *v, unsigned short w){this->u = u; this->v = v; this->w = w; MaxValue = std::numeric_limits<unsigned short>::max();}
        ENode<T>(){MaxValue = std::numeric_limits<unsigned short>::max(); w = MaxValue;}
        virtual ~ENode<T>(){}

        T *getU(){return u;}
        void setU(T *u){this->u = u;}

        T *getV(){return v;}
        void setV(T *v){this->v = v;}

        unsigned short getW(){return w;}
        void setW(unsigned short w){this->w = w;}

        unsigned short getMaxValue(){return MaxValue;}

        bool operator<=(ENode<T> &b){return w <= b.getW();}

        bool operator!=(ENode<T> &b){return (w != b.getW() || getU() != b.getU() || getV() != b.getV());}
};

#endif 
