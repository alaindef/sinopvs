
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "runprogram.h"

vector<string> readProgram(std::string filename){

    // Open the file in read mode
    std::ifstream file(filename);

    // Check if the file opened successfully
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {""};
    }

    // Create a vector to store the lines
    std::vector<std::string> lines;

    // Read the file line by line
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    // Close the file
    file.close();
    return lines;
}

void runP(std::vector<std::string> &program, VarTable &vartabel, bool prt)
{

    cout << "from runP" << endl;
}