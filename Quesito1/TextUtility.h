#ifndef TEXTUTILITY_H
#define TEXTUTILITY_H

#include <iostream>
#include <fstream>
using std::cout, std::endl, std::ifstream, std::string;

void clearTerminal();

void waitKeypress();

template <class TYPE>   //Non è stato possibile separare la definizione dall'implementazione.
void convertStringIntoType(string &word, TYPE &out){
    const char *typeOut = typeid(TYPE).name();
    if (typeOut == typeid(int).name())
        out = stoi(word);
    else if (typeOut == typeid(long long).name())
        out = stoll(word);
    else if (typeOut == typeid(char).name())
        out = *word.c_str();
    else if (typeOut == typeid(float).name())
        out = std::stof(word);
    else if (typeOut == typeid(double).name())
        out = std::stod(word);
    else if (typeOut == typeid(long double).name())
        out = std::stold(word);
}

template <class TYPE> 
short readTwoWordsbyFile(ifstream &file, TYPE &out1, TYPE &out2){
    const string strBLANK = " ", strEMPTY = "";
    string str_in;
    if (!file.good()){ //Se il file non esiste..
        cout << "File input inesistente!" << endl;
        return -5;
    }
    std::getline(file,str_in);
    if(str_in != strEMPTY){
        auto blankPosition = str_in.find(strBLANK);
        if (blankPosition == string::npos) //caso: strBLANK mancante
            return -1;
            
        string word1 = str_in.substr(0,blankPosition);
        string word2 = str_in.substr(blankPosition+1);
                                                        //.. != npos --> la posizione esiste (npos = no position)
                                                        //caso: caratteri mancanti o stringhe con dentro il carattere strBLANK.
        if (word1 == strEMPTY || word2 == strEMPTY || (word1.find(strBLANK) != string::npos) || (word2.find(strBLANK) != string::npos)){
            cout << "Una delle due stringhe e' formalmente errata: word1: '" << word1 << "'" << endl << "word2: '" << word2 << "'" << endl;
            return -2;
        } 

        convertStringIntoType(word1,out1);
        convertStringIntoType(word2,out2);
        return 1;
    }
    return 0;
}

#endif