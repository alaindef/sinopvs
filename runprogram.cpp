
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "runprogram.h"
#include "rpngenerator.h"
#include "calculator.h"
// #include "vartable.h"

using namespace std;

vector<string> readProgram(std::string filename)
{
    // Open the file in read mode
    ifstream file(filename);

    // Check if the file opened successfully
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return {""};
    }

    vector<string> lines;

    string line;
    while (getline(file, line))
    {
        if (line[0] != '#')
            lines.push_back(line);
    }

    file.close();
    return lines;
}

void action(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor); // not used

void prog(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, bool prt, bool condition);

void ifstatement(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, bool prt, bool condition)
{
    float res = 0.0;
    line.erase(line.begin());
    res = calc(line, vartabel);
    if (res > 0.1)
    {
        prog(line, lineList, vartabel, prt, condition);
        if (line.front().opcode == OC::delse)
            prog(line, lineList, vartabel, prt, false);
    }
    else
    {
        prog(line, lineList, vartabel, prt, false);
        if (line.front().opcode == OC::delse)
            prog(line, lineList, vartabel, prt, condition);
    }
    if (line.front().opcode == OC::delse)
        prog(line, lineList, vartabel, prt, condition);
};

void prog(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, bool prt, bool condition)
{
    float res = 0.0;
    line = lineList.pop();
    // OC opcode = line.front().opcode;
    OC opcode;

    try
    {
        opcode = line.front().opcode;
    }
    catch (const exception &e)
    {
        cout << "\n\n=====> runprogramcpp opcode" << e.what() << endl
             << endl;
        ;
    };
    int lineNbr = lineList.cursor - 1;
    string run = condition ? "    " : "SKIP";
    cout << setw(2) << lineNbr << " " << setw(12) << left << ppOC[(int)opcode] << "\t" << run << endl;

    switch (opcode)
    {
    case OC::dif:
        ifstatement(line, lineList, vartabel, prt, condition);
        break;
    case OC::delse:
        return;
    case OC::fi:
        return;
    case OC::endp:
        return;
    default:
        // calcandprint(line, vartabel, prt, true);
        if (condition)
        {
            res = calc(line, vartabel);
            // vartabel.printVarTable();
        }
        break;
    }

    prog(line, lineList, vartabel, prt, condition);
}

void exec(vector<vector<RPNToken> > &RPNProgram, VarTable &vartabel, bool prt)
{
    Lines lineList;
    lineList.RPNList = RPNProgram;
    vector<RPNToken> line = {{}};
    // cout << "\n parse:" << endl;
    prog(line, lineList, vartabel, prt, true);
    return;
}

void prog0(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, bool condition);

void ifstatement0(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, bool condition)
{
    float res = 0.0;
    line.erase(line.begin());
    res = calc(line, vartabel);
    if (res > 0.1)
    {
        prog0(line, lineList, vartabel, condition);
        if (line.front().opcode == OC::delse)
            prog0(line, lineList, vartabel, false);
    }
    else
    {
        prog0(line, lineList, vartabel, false);
        if (line.front().opcode == OC::delse)
            prog0(line, lineList, vartabel, condition);
    }
    if (line.front().opcode == OC::delse)
        prog0(line, lineList, vartabel, condition);
};

void prog0(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, bool condition)
{
    float res = 0.0;
    line = lineList.pop();
    // OC opcode = line.front().opcode;
    OC opcode;
    try
    {
        opcode = line.front().opcode;
    }
    catch (const exception &e)
    {
        cout << "\n\n=====> runprogramcpp opcode" << e.what() << endl
             << endl;
        ;
    };



    int lineNbr = lineList.cursor - 1;
    string run = condition ? "    " : "SKIP";

    switch (opcode)
    {
    case OC::dif:
        ifstatement0(line, lineList, vartabel, condition);
        break;
    case OC::delse:
        return;
    case OC::fi:
        return;
    case OC::endp:
        return;
    default:
        if (condition)
        {
            res = calc(line, vartabel);
        }
        break;
    }

    prog0(line, lineList, vartabel, condition);
}

void exec0(vector<vector<RPNToken> > &RPNProgram, VarTable &vartabel)
{
    Lines lineList;
    lineList.RPNList = RPNProgram;
    vector<RPNToken> line = {{}};
    prog0(line, lineList, vartabel, true);
    return;
}
