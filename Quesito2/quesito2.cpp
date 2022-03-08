#include <iostream>
#include <fstream>
using std::cout, std::cin, std::endl, std::string;

#include "TextUtility.h"
#include "UndirectedGraph/UndGraph.h"

template <class T>
void setGraph(UndGraph<T> *Graph, string &pathfile);
template <class T>
short readUndirectedGraphbyFile(UndGraph<T> *Graph, string &path_file);

#define TYPE long long 
//compile with -std=c++17
int main(int argc, char *argv[]){ 
    UndGraph<TYPE> *Graph = new UndGraph<TYPE>();
    string path_file = (argc == 2) ? argv[1] : "input0_3_2.txt";//"InputTraccia.txt";
    setGraph(Graph,path_file);

    clearTerminal();
    bool const COSTO_MINIMO = true;
    cout<<"\tLinee Notturne - Luca Rubino [0124001934]\n";
    cout << "Vertici letti in input: "  << Graph->getAllV()  << endl << endl;
    
    string A,B; //output di MST e MST2
    Graph->OUT_MST_MST2(A,B);

    cout << "Output MST:  ";
    cout << A << endl;
    cout << "Output MST2: ";
    cout << B << endl; 

    if (argc != 2) cout << endl <<  "N.B: input letto: " << path_file << " (argc!=2) " << endl;

    waitKeypress();
    cout << "... EXIT Linee Notturne!" << endl;
    return 0;
}

template <class T>
void setGraph(UndGraph<T> *Graph, string &pathfile){
    short returnedValue; 
    if ((returnedValue = readUndirectedGraphbyFile(Graph, pathfile)) <= 0){
        cout << "LETTURA FALLITA.\tCodice di errore: " << returnedValue << endl;
        cout << "Riprova.";
        exit(returnedValue);
    }
}

template <class T>
short readUndirectedGraphbyFile(UndGraph<T> *Graph, string &path_file){
    int N,P;
    short getReturnValue;
    ifstream file(path_file); 

    if ((getReturnValue = readTwoWordsbyFile(file,N,P)) < 0){
        file.close();
        return getReturnValue;
    }
    //cout << "'" << N << "'     '" << P << "'" << endl;
    if ((N<1 || N>1000) || (P<0 || P>10000)){
        file.close();
        return -3;
    }

    T u,v,w;
    unsigned int counterM = 0;//,counterN = 0;
    while(!file.eof() && (getReturnValue = readThreeWordsbyFile(file,u,v,w) != 0)){
        //cout << "u: '"  << u << "'\t"; cout << "v: '"  << v << "'\t"; cout << "w: '"  << w << "'\n";
        if (getReturnValue < 0){file.close(); return getReturnValue;}//Error
        if (w < 1 || w > 10000){
            file.close();
            return -3;
        }
        T *p_u = new T(u), *p_v = new T(v);
        /*if*/(Graph->addV(p_u));         /*counterN++;*/ 
        /*if*/(Graph->addV(p_v));        /*counterN++;*/
        if (Graph->addEdge(p_u, p_v, w))   counterM++; 
    }

    if (/*counterN != N || */counterM != P){
        cout /*<< "counterN: " << counterN << "\t"*/ << "counterM: " << counterM << endl;
        file.close();
        return -4;
    }  
    file.close();
    return 1;
}
