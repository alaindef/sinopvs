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
                               {"Heading", 0},
                               {"RollRate", 0},
                               {"GroundSpeed", 0},
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

    string pings[9] = {"pings/adfscrambled-128.png", "pings/spriteTest.png", "pings/nin.png", "pings/alt_HM.png", "pings/alt_GA_dig-2.png", 
                       "pings/G1000_1_scale_rotating-128.png", "pings/carthesius-128.png", "pings/VOR_1-3-convert.png", "pings/VOR_1-1-convert.png"};
                       // for the warnings on VOR pngs, see https://stackoverflow.com/questions/22745076/libpng-warning-iccp-known-incorrect-srgb-profile

    CTexture tex[9];

    bool gUseXPData;
};
 
#endif // VARTABLE_H
