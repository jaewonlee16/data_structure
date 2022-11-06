#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "stack.hpp"

using namespace std;

bool checkParentheses(const string& line, const vector<pair<char,char>>& pairs){
    //TODO
    Stack<char> parentheses;
    for (int i = 0; i < line.size(); i++){
        char x = (char)line[i];
        for (auto it = pairs.begin(); it != pairs.end(); it++){
            if (x == it->first){
                parentheses.push(x);
                break;
            }
            if (x == it->second){
                if (parentheses.top() != it->first)
                    return false;
                else{
                    parentheses.pop();
                    break;
                }
            }
        }
    }

    if (parentheses.isEmpty())
        return true;
    return false;
}

bool isDigit(char current, char previous){
    if (current == '(' || current == ')')
        return false;
    else if (current == '*' || current == '/'){
        return false;
    }
    else if (current == '+' || current == '-'){
        if (previous == '(')
            return true;
        else
            return false;
    }

    return true;
}

bool isDigit_i_is_zero(const char& current){
    if (current == '(')
        return false;
    
    return true;
}

int priority(const char& _operator){
    int priority;
    if (_operator == '(' || _operator == ')')
        priority = 3;
    else if (_operator == '*' || _operator == '/')
        priority = 2;
    else
        priority = 1;
    
    return priority;
}

float calculate_in_stack(float _first, float _second, char _operator){
    float value;
    if (_operator == '*')
        value = _first * _second;
    else if (_operator == '/')
        value = _first / _second;
    else if (_operator == '+')
        value = _first + _second;
    else if (_operator == '-')
        value = _first - _second;

    return value;
}

void addOperator_to_stack(const char& input_operator, Stack<float>& _numbers, Stack<char>& _operators){
    if (_operators.isEmpty())
        _operators.push(input_operator);
    else if (input_operator == '(')
        _operators.push(input_operator);
    else if (input_operator == ')'){
        // do later
        while (1){
            if (_operators.top() == '('){
                _operators.pop();
                break;
            }
            
            float second = _numbers.pop();
            float first = _numbers.pop();
            _numbers.push(calculate_in_stack(first, second, _operators.pop()));
        }
    }
    else if (priority(input_operator) > priority(_operators.top()))
        _operators.push(input_operator);
    else{
        while (1){
            if (_operators.isEmpty() || _operators.top() == '(' || _operators.top() == ')')
                break;
            if (priority(input_operator) > priority(_operators.top()))
                break;
            
            float second = _numbers.pop();
            float first = _numbers.pop();
            _numbers.push(calculate_in_stack(first, second, _operators.pop()));
        }
        _operators.push(input_operator);
    }
}

float calculate(const string& line){
    //TODO
    Stack<float> numbers;
    Stack<char> operators;

    int start_index;

    for (int i = 0; i < line.size(); i++){
        if (i == 0){
            if (isDigit_i_is_zero(line[i])){
                start_index = i;
                i++;
                while (isDigit(line[i], line[i - 1])){
                    i++;
                }
                string tmp = line.substr(start_index, i);
                float tmp_number = stof(tmp);
                i--;
                numbers.push(tmp_number);
                //cout << "push" << tmp_number << endl;
            }
            else{
                operators.push(line[i]);
                //cout << "sucessfully pushed ( when i is 0" << endl;
            }
        }
        else{
            if (isDigit(line[i], line[i - 1])){
                start_index = i;
                i++;
                while (isDigit(line[i], line[i - 1])){
                    i++;
                }
                string tmp = line.substr(start_index, i);
                float tmp_number = stof(tmp);
                i--;
                numbers.push(tmp_number);
                //cout << "push" << tmp_number << endl;
            }
            else{
                //cout << "try to push: " << line[i] << endl;
                addOperator_to_stack(line[i], numbers, operators);
                //cout << "finieshed addOperator_to_stack" << endl;
            }
        }
    }

    while (!operators.isEmpty()){
        float second = numbers.pop();
        float first = numbers.pop();
        numbers.push(calculate_in_stack(first, second, operators.pop()));
    }

    return numbers.pop();
}