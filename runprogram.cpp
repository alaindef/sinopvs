
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

void ifstatement(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor);   // not used

void action(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor);        // not used

void exec(vector<RPNToken> &line, Lines &lineList, VarTable &vartabel, bool prt, bool condition)
{
    if (lineList.done())
        return;
    while (true)
    {
        if (lineList.done())
            return;
        line = lineList.pop();
        cout << "\nat line " << lineList.cursor-1 << " " << ppOC[(int)line.front().opcode] << " " << line.front().value;
        switch (line.front().opcode)
        {
        case OC::dif:
            line.erase(line.begin());
            if (condition)
            {
                if (calc(line, vartabel))
                    exec(line, lineList, vartabel, prt, true);
                else
                    exec(line, lineList, vartabel, prt, false);
            }
            else
            {
                cout << " ------------SKIP";
                exec(line, lineList, vartabel, prt, false);
            }
            break;
        case OC::end:
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

void exec(vector<vector<RPNToken> > &RPNProgram, VarTable &vartabel, bool prt)
{
    Lines lineList;
    lineList.RPNList = RPNProgram;
    vector<RPNToken> line = {{}};
    exec(line, lineList, vartabel, prt, true);
    return;
}

void ifstatement(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor)   // not used
{
    cout << "ifstatement opcode is " << endl;
    cursor++;
};

void action(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor)   // not used
{
    cout << "action opcode is " << endl;
    cursor++;
};