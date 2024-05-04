#include "vartable.h"
#include <iostream>

using namespace std;


int VarTable::getIndex(string name){
    for (int i=0; i < vartab.size(); i++)
        if (name == vartab[i].name)
            return i;
    vartab.push_back({name,0});               // new entry in table
    return vartab.size()-1;
}

float VarTable::getValue(int index){
    return vartab[index].value;
}

int VarTable::setVar(string name, float value){
    for (int i=0; i<vartab.size(); i++)
        if (name == vartab[i].name) {
            vartab[i].value = value;
            return i;
        }
    vartab.push_back({name,value});               // new entry in table
    return vartab.size()-1;
}

int VarTable::setVar(int index, float value){
    vartab[index].value = value;
    return index;
}

void VarTable::printVarTable(){
    cout << "\nvar:   "; for (const auto& element : vartab) cout << element.name << "\t" ;
    cout << "\nvar:   "; for (const auto& element : vartab) cout << element.value<< "\t";
    cout << endl;
    }

