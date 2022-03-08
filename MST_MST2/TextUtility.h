#ifndef TEXTUTILITY_H
#define TEXTUTILITY_H

#include <iostream>
#include <fstream>
using std::cout, std::endl, 
std::ifstream, std::string;

void clearTerminal();

void waitKeypress();

template <class TYPE>   
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
    if (!file.good()){ //if file does not exsists
        cout << "File input does not exists!" << endl;
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
            cout << "wrong string: word1: '" << word1 << "'" << endl << "word2: '" << word2 << "'" << endl;
            return -2;
        } 

        convertStringIntoType(word1,out1);
        convertStringIntoType(word2,out2);
        return 1;
    }
    return 0;
}

template <class TYPE> 
short readThreeWordsbyFile(ifstream &file, TYPE &out1, TYPE &out2, TYPE &out3){
    const string strBLANK = " ", strEMPTY = "";
    string str_in;
    if (!file.good()){ //Se il file non esiste..
        cout << "File does not exists!" << endl;
        return -5;
    }
    std::getline(file,str_in);
    if(str_in != strEMPTY){
        auto blankPosition = str_in.find(strBLANK);
        if (blankPosition == string::npos) //caso: strBLANK mancante dopo word1
            return -1;
            
        string word1 = str_in.substr(0,blankPosition);

        auto secondblankPosition = str_in.find(strBLANK,blankPosition+1);
        if (secondblankPosition == string::npos) //caso 2: strBLANK mancante dopo word2
            return -1;

        string word2 = str_in.substr(blankPosition+1,secondblankPosition-(blankPosition+1));
        string word3 = str_in.substr(secondblankPosition+1);
                                                        //.. != npos --> la posizione esiste (npos = no position)
                                                        //caso: caratteri mancanti o stringhe con dentro il carattere strBLANK.
        if (word1 == strEMPTY || word2 == strEMPTY || word3 == strEMPTY || 
        (word1.find(strBLANK) != string::npos) || (word2.find(strBLANK) != string::npos) || (word3.find(strBLANK) != string::npos)){
            cout << "wrong string: word1: '" << word1 << "'\t"<< "word2: '" << word2 << "'\t"<< "word3: '" << word3 << "'" << endl;
            return -2;
        } 
        convertStringIntoType(word1,out1);
        convertStringIntoType(word2,out2);
        convertStringIntoType(word3,out3);

        return 1;
    }
    return 0;
}

#endif