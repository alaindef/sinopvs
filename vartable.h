#ifndef VARTABLE_H
#define VARTABLE_H
#include <string>
#include <vector>

using namespace std;

struct VarTable
{
    struct VarValue
    {
        string name;
        float value;
    };

    vector<VarValue> vartab = {{"Altitude", 300},
                               {"EngineRPM", 0},
                               {"FlapPosition", 0},
                               {"a", -10},
                               {"b", 10}};

    int getIndex(string name);
    // look for name in the table and return the storage index
    // if not found create a new entry and return the new index

    float getValue(int index);
    // get value at index. error if index > size of vartable

    int setVar(string name, float value);
    // if name found modify the value, if not store value in new entry. returns index

    int setVar(int index, float value);
    // returns index

    void printVarTable();
};

#endif // VARTABLE_H
