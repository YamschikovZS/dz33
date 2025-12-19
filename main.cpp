#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "lab.h"


int main()
{
    std::cout << "Enter expression: ";
    std::string exp;
    std::cin >> exp;

    std::vector<Token> allTokens;
    const auto numbers = findTokens(exp, num_reg, "NUMBER");
    const auto operators = findTokens(exp, op_reg, "OPERATOR");
    const auto functions = findTokens(exp, func_reg, "FUNCTION");
    const auto constants = findTokens(exp, const_reg, "CONSTANT");
    const auto staples = findTokens(exp, stap_reg, "STAPLE");

    for (const auto& i : numbers) allTokens.push_back(i);
    for (const auto& i : operators) allTokens.push_back(i);
    for (const auto& i : functions) allTokens.push_back(i);
    for (const auto& i : constants) allTokens.push_back(i);
    for (const auto& i : staples) allTokens.push_back(i);

    for (const auto variables = findTokens(exp, var_reg, "VARIABLE"); const auto& i : variables) allTokens.push_back(i);

    std::sort(allTokens.begin(), allTokens.end(), [](const Token& a, const Token& b) -> bool { return a.position < b.position; });

    bool x = false;
    for (const auto& token : allTokens)
    {
        if (token.type == "VARIABLE")
        {
            x = true;
            break;
        }
    }

    double x_val = 0;
    if (x)
    {
        std::cout << "x = ";
        std::cin >> x_val;
    }

    detectMinus(allTokens);
    const std::vector<Token> postfix = Convert(allTokens);

    std::cout << "Result: " << calculate(postfix, x_val) << std::endl;


    return 0;
}