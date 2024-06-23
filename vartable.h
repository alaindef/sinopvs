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
                               {"BankAngle", 0},
                               {"PitchAngle", 0},
                               {"a", -10},
                               {"b", 10}};

    int getIndex(string name);
    // look for name in the table and return the storage index
    // if not found create a new entry and return the new index

    float getValue(int index);
    // get value at index. error if index > size of vartable
    // if index < 3 returns value from flightsimulator

    int setVar(string name, float value);
    // if name found modify the value, if not store value in new entry. returns index

    int setVar(int index, float value);
    // returns index

    void printVarTable();

    // I think png's should be 128x128 pixels

    string pings[7] = {"adfscrambled-128.png", "spriteTest.png", "nin.png", "adfscrambled-256.png", "needle.png",
                       "G1000_1_scale_rotating-128.png", "carthesius-128.png"};

    CTexture tex[7];

    bool gUseXPData;
};

#endif // VARTABLE_H
