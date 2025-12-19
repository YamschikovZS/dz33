#ifndef LAB09_LAB_H
#define LAB09_LAB_H

#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "lab.h"

inline std::regex num_reg(R"(\d+\.?\d*|\.\d+)");
inline std::regex op_reg(R"(\+|\-|\*|\/)");
inline std::regex func_reg(R"(sin|cos|tg|ctg|exp)");
inline std::regex const_reg(R"(E|PI)");
inline std::regex stap_reg(R"(\(|\))");
inline std::regex var_reg(R"(x)");

struct Token
{
    std::string type;
    std::string value;
    int position;
};


int getPriority(const Token& token);

void detectMinus(std::vector<Token>& tokens);

std::vector<std::string> findNums(std::string exp);

std::vector<std::string> findOps(std::string exp);

std::vector<std::string> findFuncs(std::string exp);

std::vector<std::string> findConst(std::string exp);

std::vector<std::string> findStaples(std::string exp);

std::vector<Token> findTokens(const std::string& exp, const std::regex& REGEX, const std::string& type);

std::vector<Token> Convert(const std::vector<Token>& tokens);

double calculate(const std::vector<Token>& postfix, double x_value);

#endif //LAB09_LAB_H