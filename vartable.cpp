#include "vartable.h"
#include <iostream>

#include "FlightSimulator.h"
#include "FSData.h"

extern CFlightSimulator gFlightSimulator;
extern CFSData gFSData;

bool gUseXPData = true;

using namespace std;

int VarTable::getIndex(string name)
{
    for (int i = 0; i < vartab.size(); i++)
        if (name == vartab[i].name)
            return i;
    vartab.push_back({name, 0}); // new entry in table
    return vartab.size() - 1;
}

float VarTable::getValue(int index)
{
    float val;
    if (index < 3)
    {
        if (gUseXPData)
            switch (index)
            {
            case 0:
                val = gFSData.GetAltitude();
                break;
            case 1:
                val = gFSData.GetBankAngle();
                break;
            case 2:
                val = gFSData.GetPitchangle();
                break;
            default: break;
            }
        else
            val = *gFlightSimulator.GetAddressOfNamedVariableFloat(vartab[index].name);
    }
    else
        val = vartab[index].value;

    return val;
}

int VarTable::setVar(string name, float value)
{
    for (int i = 0; i < vartab.size(); i++)
        if (name == vartab[i].name)
        {
            vartab[i].value = value;
            return i;
        }
    vartab.push_back({name, value}); // new entry in table
    return vartab.size() - 1;
}

int VarTable::setVar(int index, float value)
{
    vartab[index].value = value;
    return index;
}

void VarTable::printVarTable()
{
    cout << "var:   ";
    for (const auto &element : vartab)
        cout << element.name.substr(0, 4) << "\t";
    cout << "\nvar:   ";
    for (const auto &element : vartab)
    {
        printf("%.2f\t", element.value);
        // cout << element.value << "\t";
    }
    cout << endl;
}
