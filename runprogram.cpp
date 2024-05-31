
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

void prog(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, vector<string> &source, bool prt, bool condition);

void ifstatement(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, vector<string> &source, bool prt, bool condition)
{
    float res = 0.0;
    line.erase(line.begin());
    res = calc(line, vartabel);
    if (res > 0.1)
    {
        prog(line, lineList, vartabel, source, prt, condition);
        if (line.front().opcode == OC::delse)
            prog(line, lineList, vartabel, source, prt, false);
    }
    else
    {
        prog(line, lineList, vartabel, source, prt, false);
        if (line.front().opcode == OC::delse)
            prog(line, lineList, vartabel, source, prt, condition);
    }
    if (line.front().opcode == OC::delse)
        prog(line, lineList, vartabel, source, prt, condition);
};

void action(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor) // not used
{
    cout << "action opcode is " << endl;
    cursor++;
};

void prog(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, vector<string> &source, bool prt, bool condition)
{
    float res = 0.0;
    line = lineList.pop();
    OC opcode = line.front().opcode;
    int lineNbr = lineList.cursor - 1;
    string run = condition ? "    " : "SKIP";
    cout << setw(2) << lineNbr << " " << setw(50) << left << source[lineNbr]
         << ppOC[(int)opcode] << "\t" << run << endl;

    switch (opcode)
    {
    case OC::dif:
        ifstatement(line, lineList, vartabel, source, prt, condition);
        break;
    case OC::delse:
        return;
    case OC::fi:
        return;
    case OC::endp:
        return;
    default:
        // calcandprint(line, vartabel, false, condition);
        if (condition)
            res = calc(line, vartabel);
        break;
    }

    prog(line, lineList, vartabel, source, prt, condition);
}

void exec(vector<vector<RPNToken> > &RPNProgram, VarTable &vartabel, vector<string> &source, bool prt)
{
    Lines lineList;
    lineList.RPNList = RPNProgram;
    vector<RPNToken> line = {{}};
    cout << "\n parse:" << endl;
    prog(line, lineList, vartabel, source, prt, true);
    // exec(line, lineList, vartabel, prt, true);
    return;
}