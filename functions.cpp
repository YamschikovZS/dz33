#include <string>
#include <regex>
#include <vector>
#include <stack>
#include <cmath>
#include <map>
#include "lab.h"


int getPriority(const Token& token)
{
    if (token.type == "UNARY_MINUS") return 4;
    if (token.type == "FUNCTION" || token.value == "^") return 3;
    if (token.value == "*" || token.value == "/") return 2;
    if (token.value == "+" || token.value == "-") return 1;
    return 0;
}

void detectMinus(std::vector<Token>& tokens)
{
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].value == "-")
        {
            bool isUnary = false;

            if (i == 0) isUnary = true;
            else if (tokens[i - 1].value == "(") isUnary = true;
            else if (tokens[i - 1].type == "OPERATOR") isUnary = true;
            else if (tokens[i - 1].type == "FUNCTION") isUnary = true;

            if (isUnary)
            {
                tokens[i].type = "UNARY_MINUS";
                tokens[i].value = "~";
            }
        }
    }
}

std::vector<std::string> findNums(std::string exp)
{
    std::vector<std::string> result;
    auto begin = std::sregex_iterator(exp.begin(), exp.end(), num_reg);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        result.push_back(it->str());
    }
    return result;
}

std::vector<std::string> findOps(std::string exp)
{
    std::vector<std::string> result;
    auto begin = std::sregex_iterator(exp.begin(), exp.end(), op_reg);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        result.push_back(it->str());
    }
    return result;
}

std::vector<std::string> findFuncs(std::string exp)
{
    std::vector<std::string> result;
    auto begin = std::sregex_iterator(exp.begin(), exp.end(), func_reg);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        result.push_back(it->str());
    }
    return result;
}

std::vector<std::string> findConst(std::string exp)
{
    std::vector<std::string> result;
    auto begin = std::sregex_iterator(exp.begin(), exp.end(), const_reg);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        result.push_back(it->str());
    }
    return result;
}

std::vector<std::string> findStaples(std::string exp)
{
    std::vector<std::string> result;
    const auto begin = std::sregex_iterator(exp.begin(), exp.end(), stap_reg);
    const auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        result.push_back(it->str());
    }
    return result;
}

std::vector<Token> findTokens(const std::string& exp, const std::regex& REGEX, const std::string& type)
{
    std::vector<Token> result;

    const auto begin = std::sregex_iterator(exp.begin(), exp.end(), REGEX);
    const auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        result.push_back({type, it->str(), (int)it->position()});
    }
    return result;
}

std::vector<Token> Convert(const std::vector<Token>& tokens)
{
    std::vector<Token> output;
    std::stack<Token> stack;

    for (const Token& token : tokens)
    {
        if (token.type == "NUMBER" || token.type == "CONSTANT")
        {
            output.push_back(token);
        }

        else if (token.type == "UNARY_MINUS")
        {
            stack.push(token);
        }

        else if (token.type == "FUNCTION")
        {
            stack.push(token);
        }

        else if (token.value == "(")
        {
            stack.push(token);
        }

        else if (token.value == ")")
        {
            while (!stack.empty() && stack.top().value != "(")
            {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        }
        else if (token.type == "OPERATOR")
        {
            while (!stack.empty() && stack.top().value != "(" && getPriority(stack.top()) >= getPriority(token))
            {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
        }
        else if (token.type == "VARIABLE")
        {
            output.push_back(token);
        }
    }

    while (!stack.empty() )
    {
        output.push_back(stack.top());
        stack.pop();
    }

    return output;
}

double calculate(const std::vector<Token>& postfix, double x_value)
{
    std::stack<double> stack;
    std::map<std::string, double> constants = {
        {"PI", 3.141592653589793},
        {"E", 2.718281828459045}
    };

    for (const Token& token : postfix)
    {
        if (token.type == "NUMBER")
        {
            stack.push(std::stod(token.value));
        }
        else if (token.type == "CONSTANT")
        {
            stack.push(constants[token.value]);
        }
        else if (token.type == "UNARY_MINUS")
        {
            double a = stack.top(); stack.pop();
            stack.push(-a);
        }
        else if (token.type == "VARIABLE")
        {
            stack.push(x_value);
        }
        else if (token.type == "OPERATOR")
        {
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();

            if (token.value == "+") stack.push(a + b);
            else if (token.value == "-") stack.push(a - b);
            else if (token.value == "*") stack.push(a * b);
            else if (token.value == "/") stack.push(a / b);
            else if (token.value == "^") stack.push(pow(a, b));
        }
        else if (token.type == "FUNCTION")
        {
            double a = stack.top(); stack.pop();

            if (token.value == "sin") stack.push(sin(a));
            else if (token.value == "cos") stack.push(cos(a));
            else if (token.value == "tg") stack.push(tan(a));
            else if (token.value == "ctg") stack.push(1.0 / tan(a));
            else if (token.value == "exp") stack.push(exp(a));
        }
    }
    return stack.top();
}