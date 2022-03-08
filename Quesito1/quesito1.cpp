#include <iostream>
#include <fstream>
using std::cout, std::cin, std::endl, std::string;

#include "RBGraph/RBGraph.h"

#include "TextUtility.h"

#define TYPE long long 
void execCommand(RBGraph<TYPE> *, short);
template <class T>  short readOrientedGraphbyFile(RBGraph<T> *, string &);
template <class T>  void setGraph(RBGraph<T> *Graph, string &pathfile);


//compile with -std=c++17

int main(int argc, char *argv[]){ 
    RBGraph<TYPE> *OrientedGraph = new RBGraph<TYPE>();
    auto error = false; 
    auto command = 1; //=1 for starting while loop
    string path_file = (argc == 2) ? argv[1] : "input0_3_1.txt"; //"input_grande.txt"; //input0_3_1.txt is default input

    setGraph(OrientedGraph, path_file); //Set nodes and edges graph with by input file
    string Vnodes = OrientedGraph->getAllV();

    while(command){
        clearTerminal();
        if (argc != 2)   cout << "N.B: input file path: " << path_file << " (argc!=2) " << endl << endl;
        cout<<"\tRBGRAPH - Luca Rubino [0124001934]\n";
        cout << "Graph nodes: " << Vnodes << endl << endl;

        cout << "1) AddEdge(i,j)\n" << "2) RemoveEdge(i,j)\n" << "3) FindEdge(i,j)\n" << "4) BFS(s)\n" << "0) Quit\n\n";
        
        if (error)  
            cout << "\t\t\tINVALID COMMAND!" << endl;
        
        cout << "Command: ";
        cin >> command;
        
        if( !(error = command<0 || command>4) && command != 0 ) //error: <0 o >4     quit: =0
            clearTerminal(),
            execCommand(OrientedGraph, command);
    }
    cout << "... EXIT RBGRAPH!" << endl;
    return 0;
}






void execCommand(RBGraph<TYPE> *OrientedGraph, short command){
    TYPE i,j; string strOut = "";
    if (command!=4){
        cout<<"Insert first node: ";    cin >> i;
        cout<<"Insert second node: ";    cin >> j;
    }
    switch(command){
        case 1:
			strOut = (OrientedGraph->addEdge(i,j)) ? 
                "Edge added!\n" : "Edge not added! (node does not exist or arch already exists)\n";
            break;
        case 2:
            strOut = (OrientedGraph->removeEdge(i,j)) ?
                "Edge removed!\n" : "Arco not removed! (does not exists)\n";
            break;
        case 3:
            strOut = (OrientedGraph->findEdge(i,j)) ? 
                "Edge exists!\n" : "edge does not exsists!\n";
            break;
        case 4:
            TYPE s;
            cout<<"[BFS]\tInsert source node for BFS VISIT: ";
            cin >> s;
            OrientedGraph->BFS(s);
            break;
    }
	cout << strOut << endl;
    waitKeypress();
}

template <class T>
void setGraph(RBGraph<T> *Graph, string &pathfile){
    short returnedValue; 
    if ((returnedValue = readOrientedGraphbyFile(Graph, pathfile)) <= 0){
        cout << "READING FAILED.\tError Code: " << returnedValue << endl;
        cout << "Try again.";
        exit(returnedValue);
    }
}

template <class T>
short readOrientedGraphbyFile(RBGraph<T> *Graph, string &path_file){
    int N,M;
    short getReturnValue;
    ifstream file(path_file); //L'esistenza del file viene controllata in readTwoWordsbyFile(..)

    if ((getReturnValue = readTwoWordsbyFile(file,N,M)) < 0)
        return getReturnValue;
    cout << "'" << N << "'     '" << M << "'" << endl;
    if ((N<0 || N>1000) || (M<0 || M>1000)){
        file.close();
        return -3;
    }
    T u,v;
    unsigned int counterM = 0;//,counterN = 0;
    while(!file.eof() && (getReturnValue = readTwoWordsbyFile(file,u,v) != 0)){
        if (getReturnValue < 0) return getReturnValue; //Errore
        /*if*/ (Graph->addV(u));         /*counterN++;*/ 
        /*if*/ (Graph->addV(v));         /*counterN++;*/
        if (Graph->addEdge(u,v))   counterM++;
    }
    if (/*counterN != N || */counterM != M){
        cout /*<< "counterN: " << counterN << "\t"*/ << "counterM: " << counterM << endl;
        file.close();
        return -4;
    }   
    file.close();
    return 1;
}

