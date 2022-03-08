#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <iostream>
#include <fstream>
#include <vector>

using std::cout, std::endl, std::vector;

template <class NT>
void Merge(vector<NT *> &A, typename vector<NT*>::iterator &p, typename vector<NT*>::iterator &q, typename vector<NT*>::iterator &r){
	auto n1 = q-p+1, n2 = r-q;
	NT *L[n1+1], *R[n1+1];
	int i,j;

	auto k = p;
    for(i=0; i < n1; i++)
        L[i] = *(k++);
    k = q;
    for(j=0; j < n2; j++)
        R[j] = *(k++ +1);

    NT *NT_MAX = new NT(); //sentry node
    L[n1] = R[n2] = NT_MAX;
    i = j = 0;
    for(k=p;k<=r;k++) //Overload operator in Enode
        *k = (*L[i] <= *R[j]) ? L[i++] : R[j++];
}

template <class NT>
void MergeSort(vector<NT*> &A, typename vector<NT*>::iterator p, typename vector<NT*>::iterator r){
    if(p<r){
        auto q = p+((r-p)/2);
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    } 
}
#endif