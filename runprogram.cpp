
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

void ifstatement(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor); // not used

void action(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor); // not used

void exec(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, bool prt, bool condition)
{
    while (true)
    {
        if (lineList.done())
            return;
        line = lineList.pop();
        cout << "\nat line " << lineList.cursor - 1 << " " << ppOC[(int)line.front().opcode] << " " << line.front().value;
        switch (line.front().opcode)
        {
        case OC::dif:
            line.erase(line.begin());
            if (condition)
            {
                if (calc(line, vartabel))
                {
                    exec(line, lineList, vartabel, prt, true);
                    if (line.front().opcode == OC::delse)
                    {
                        line = lineList.pop();
                        exec(line, lineList, vartabel, prt, false);
                        cout << "\ndelse 65" << endl;
                    }
                }
                else
                {
                    exec(line, lineList, vartabel, prt, false);
                    if (line.front().opcode == OC::delse)
                    {
                        exec(line, lineList, vartabel, prt, true);
                        cout << "\ndelse 74" << endl;
                    }
                }
            }
            else
            {
                cout << " ------------SKIP";
                exec(line, lineList, vartabel, prt, false);
            }
            break;
        case OC::delse:
            if (lineList.done())
                return;
            // if (!condition)
            //     cout << " ------------SKIP";
            return;
        case OC::fi:
            if (lineList.done())
                return;
            if (!condition)
                cout << " ------------SKIP";
            return;
        default:
            if (!condition)
                cout << " ------------SKIP";
            else
                calcandprint(line, vartabel, true, false);
            break;
        }
    }
}

void prog(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, vector<string> &source, bool prt, bool condition);

void ifstatement(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor) // not used
{
    cout << "ifstatement opcode is " << endl;
    cursor++;
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
    OC opcode = line.back().opcode;
    int lineNbr = lineList.cursor - 1;
    cout << setw(2) << lineNbr << " " << setw(20) << left << source[lineNbr] << ppOC[(int)opcode] << endl;

    switch (opcode)
    {
    case OC::dif:
        line.erase(line.begin());
        res = calc(line, vartabel);
        prog(line, lineList, vartabel, source, prt, condition);
    case OC::delse:
        prog(line, lineList, vartabel, source, prt, condition);
        break;
    case OC::fi:
        prog(line, lineList, vartabel, source, prt, condition);
        break;
    case OC::endp:
        return;
    case OC::VAR:
        break;
    default:
        prog(line, lineList, vartabel, source, prt, true);
        break;
    }
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