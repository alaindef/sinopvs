#pragma once
#ifndef tokengenerator_H
#define tokengenerator_H

#include "vartable.h"
#include <string>
#include <vector>
#include <map>

enum class OC
{
    NUM,
    VAR,
    MUL,
    DIV,
    ADD,
    SUB,
    PAS,
    CHS,
    LT,
    LE,

    GT,
    GE,
    EQ,
    NE,
    ASS,
    QU,
    COL,
    PAR_L,
    PAR_R,
    COMMA,

    FIRSTFUN,
    pushm,
    popm,
    trnsm,
    drawm,
    alti,
    dif,
    NIL,
};
// pretty print opcodes
const std::string ppOC[28] = {"NUM", "VAR", "MUL", "DIV", "ADD", "SUB", "PAS", "CHS", "LT", "LE",
                              "GT", "GE", "EQ", "NE", "ASS", "QU", "COL", "PAR_L", "PAR_R", "COMMA",
                              "FIRSTFUN", "pushm", "popm", "trnsm", "drawm", "alti", "dif", "NIL"};

struct Token
{
    OC opcode;
    int arity;
    int precedence;
    float value;
};

const map<std::string, Token> keywords = {
    // symbol {opcode, arity, precedence, value}
    {"NUM", {OC::NUM, 0, 0, 0}},
    {"VAR", {OC::VAR, 0, 0, 0}},
    {"*", {OC::MUL, 2, 3, 0}},
    {"/", {OC::DIV, 2, 3, 0}},
    {"+", {OC::ADD, 2, 4, 0}},
    {"-", {OC::SUB, 2, 4, 0}},
    {"<", {OC::LT, 2, 6, 0}},
    {"<=", {OC::LE, 2, 6, 0}},
    {">", {OC::GT, 2, 6, 0}},
    {">=", {OC::GE, 2, 6, 0}},

    {"==", {OC::EQ, 2, 7, 0}},
    {"!=", {OC::NE, 2, 7, 0}},
    {"?", {OC::QU, -1, 13, 0}},
    {":", {OC::COL, 3, 13, 0}},
    {"=", {OC::ASS, 2, 14, 0}},
    {"(", {OC::PAR_L, -1, -1, 0}},
    {")", {OC::PAR_R, -1, -1, 0}},
    {",", {OC::COMMA, -1, -1, 0}},
    {"FIRSTFUN", {OC::FIRSTFUN, 0, 0, 0}},
    {"pushm", {OC::pushm, 0, 0, 0}},
    {"popm", {OC::popm, 0, 0, 0}},
    {"trnsm", {OC::trnsm, 0, 0, 0}},
    {"drawm", {OC::drawm, 0, 0, 0}},
    {"alti", {OC::alti, 0, 0, 15}},
    {"dif", {OC::dif, 0, 0, 15}},
    {"NIL", {OC::NIL, -1, 0, 0}}};

vector<Token> makeTokenList(string textIn,
                            const map<std::string, Token> &keywords,
                            VarTable &vartabel, int report);

#endif // tokengenerator_H
