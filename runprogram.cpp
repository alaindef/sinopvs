
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

    // Create a vector to store the lines
    vector<string> lines;

    // Read the file line by line
    string line;
    while (getline(file, line))
    {
        if (line[0] != '#')
            lines.push_back(line);
    }

    // Close the file
    file.close();
    return lines;
}

void ifstatement(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor);

void action(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor);

void exec(vector<string> &program, int &startLine, VarTable &vartabel, bool prt)
{
    if (startLine >= program.size())
        return;
    // cout << "startLine= " << startLine << "  line= " << program[startLine] << endl;
    if (program[startLine] == "end")
        cout << "end at " << startLine << endl;
    cout << "executing line " << startLine << endl;
    startLine++;
    exec(program, startLine, vartabel, prt);
}

void runP(vector<string> &program, VarTable &vartabel, bool prt)
{
    int startLine = 0;
    exec(program, startLine, vartabel, prt);
}

void exec(Lines &lineList, VarTable &vartabel, bool prt)
{
    if (lineList.done()) return;
    vector<RPNToken> line = lineList.pop();
    switch (line.front().opcode)
    {
    case OC::dif:
        cout << "at line " << lineList.cursor << " dif " << endl;
        // lineList.pop();
        exec(lineList, vartabel, prt);
        break;
    case OC::end:
        cout << "at line " << lineList.cursor << " end " << endl;
        exec(lineList, vartabel, prt);
        // lineList.pop();
        return;
    default:
        calcandprint(line, vartabel, prt);
        exec(lineList, vartabel, prt);
        break;
    }
}

void exec(vector<vector<RPNToken> > &RPNProgram, VarTable &vartabel, bool prt)
{
    Lines lineList;
    lineList.RPNList = RPNProgram;
    exec(lineList, vartabel, prt);
    return;
}

void ifstatement(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor)
{
    cout << "ifstatement opcode is " << endl;
    cursor++;
};

void action(vector<RPNToken> &RPN, vector<vector<RPNToken> > &program, int &cursor)
{
    cout << "action opcode is " << endl;
    cursor++;
};