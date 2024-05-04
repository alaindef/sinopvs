#include "tokengenerator.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

void printtokengenerator(const vector<Token> &RPNTokens,
                         VarTable &vartabel, string &out, int report)
{
    if (!report)
        return;
    cout << "\n******************** tokenList ********************\nout=\t" << out << endl;
    cout << "opcode : ";
    for (const Token &element : RPNTokens)
        // std::cout << "\t"  << element.value << " ";
        cout << "\t" << ppOC[static_cast<int>(element.opcode)] << " ";
    cout << endl;
    cout << "opcode: ";
    for (const Token &element : RPNTokens)
        cout << "\t" << static_cast<int>(element.opcode) << " "; // todo convert to string
    cout << endl;
    cout << "arity : ";
    for (const Token &element : RPNTokens)
        cout << "\t" << element.arity << " ";
    cout << endl;
    cout << "preced: ";
    for (const Token &element : RPNTokens)
        cout << "\t" << element.precedence << " ";
    cout << endl;
    cout << "value : ";
    for (const Token &element : RPNTokens)
        cout << "\t" << element.value << " ";
    cout << endl;
}

bool findKeyword(const map<string, Token> &keys,
                 const string &s,
                 pair<string, Token> &result)
{
    // ordered Map stores "==" always after "=", "==" would never be found. so we loop through the map in reverse
    for (auto entry = keys.rbegin(); entry != keys.rend(); ++entry)
    {
        const string &key = entry->first;
        if (s.compare(0, key.size(), key) == 0)
        {
            result = {entry->first, entry->second};
            return true;
        }
    }
    return false;
}

void storeValueOrIndex(string param,
                       Token &token,
                       VarTable &vartabel)
{
    if (isNumeric(param))
    {
        token.value = stof(param);
        token.opcode = OC::NUM;
    }
    else
    {
        token.value = vartabel.getIndex(param);
        token.opcode = OC::VAR;
    }
}

vector<Token> makeTokenList(string textIn,
                            const map<std::string, Token> &keywords,
                            VarTable &vartabel,
                            int report) // provisional, for debug and reporting
{
    string out = "\tNIL"; // only for reporting
    int cursor = 0;
    string operand = "";
    pair<string, Token> keyPairFound;
    int moveCursor;

    vector<Token> tokens;
    Token token;
    // start with a nil token. that way we can check the token before the first one without crash
    tokens.push_back({OC::NIL, 0, 0, 0});
    while (cursor < textIn.size())
    {
        if (textIn[cursor] == ' ') // skip blanks
        {
            cursor++;
            continue;
        }
        if (findKeyword(keywords, textIn.substr(cursor), keyPairFound))
        {
            // we have a keyword, but in the else section we were building an OPERAND
            // the operand has finished building, so we can now store it in a token and push it
            if (operand.size() > 0)
            { 
                // operand is a num or var
                // if num store it in token, if var reserve an index for it in var array
                storeValueOrIndex(operand, token, vartabel);
                tokens.push_back(token);
                out += "\t{" + operand + "}";
            }
            operand = "";                       // operand has been treated, reset it to empty string
            // store the keyword in a token and push it
            token = keyPairFound.second;
            tokens.push_back(token);
            moveCursor = keyPairFound.first.size();
            out += "\t|" + keyPairFound.first + "|";    // for 
        }
        else
        {
            // operand is a digit or variable because the text at cursor does not start with a keyword
            operand += textIn[cursor]; // collect coming chars in operand
            moveCursor = 1;
            token.arity = 0;
            token.precedence = 0; // opcode NUM or VAR follows later
        }
        cursor += moveCursor;
    }
    if (operand.size() > 0)
    { // operand is a num or var
        storeValueOrIndex(operand, token, vartabel);
        tokens.push_back(token);
        out += "\t{" + operand + "} ";
    }
    tokens.push_back({OC::NIL, 0, 0, 0});
    out += "\t{";
    out += "ETX";
    out += "} ";

    printtokengenerator(tokens, vartabel, out, report); // does nothing if report != 0

    return tokens;
}
