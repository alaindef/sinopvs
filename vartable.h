#ifndef VARTABLE_H
#define VARTABLE_H
#include <string>
#include <vector>
#include "Renderer.h"

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

    // I think png's should be 128x128 pixels

    string pings[4] = {"adfscrambled10b.png", "spriteTest.png", "nin.png", "krokus.png"};

    CTexture tex[4];
};

#endif // VARTABLE_H
