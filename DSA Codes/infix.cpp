#include <iostream>
#include <stack>

using namespace std;

//  to get the precedence of an operator
int Precedence(char op) {
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}

// Function to convert infix expression to postfix
string infixToPostfix(const string& infixExpression) {
    string postfix = "";
    stack<char> operatorStack;

    for (char c : infixExpression) {
        if (isspace(c)) {
            continue;  // Ignore spaces
        }
        else if (c == '(') {
            operatorStack.push(c);
        }
        else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '(') {
                operatorStack.pop(); // Pop the '('
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operatorStack.empty() && Precedence(c) <= Precedence(operatorStack.top())) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
        else {
            // Assume it's an operand
            postfix += c;
        }
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

// Function to evaluate a postfix expression
int evaluatePostfix(const string& postfix) {
    stack<int> operandStack;

    for (char c : postfix) {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            int operand2 = operandStack.top();
            operandStack.pop();
            int operand1 = operandStack.top();
            operandStack.pop();

            int result;
            if (c == '+') {
                result = operand1 + operand2;
            }
            else if (c == '-') {
                result = operand1 - operand2;
            }
            else if (c == '*') {
                result = operand1 * operand2;
            }
            else if (c == '/') {
                result = operand1 / operand2;
            }

            operandStack.push(result);
        }
        else {
            // Assume it's an operand
            operandStack.push(c - '0');
        }
    }

    return operandStack.top();
}

int main() {
    string infixExp;
    cout << "Enter an infix expression: ";
    getline(cin, infixExp);

    string postfixExp = infixToPostfix(infixExp);
    cout << "Postfix exp: " << postfixExp << endl;

    int Answer = evaluatePostfix(postfixExp);
    cout << "Answer: " << Answer << endl;

    return 0;
}
