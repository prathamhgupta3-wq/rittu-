// Converts an infix expression to postfix and prefix using a stack
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

char operators[200];
int top = -1;

int priority(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

bool toPostfix(string infix, string &postfix)
{
    top = -1;
    postfix = "";
    bool needOperand = true;
    for (int i = 0; i < (int)infix.length(); i++)
    {
        char ch = infix[i];
        if (isspace((unsigned char)ch))
            continue;
        if (isalnum((unsigned char)ch))
        {
            if (!needOperand)
                return false;
            postfix += ch;
            needOperand = false;
        }
        else if (ch == '(')
        {
            if (!needOperand)
                return false;
            operators[++top] = ch;
        }
        else if (ch == ')')
        {
            if (needOperand)
                return false;
            while (top != -1 && operators[top] != '(')
                postfix += operators[top--];
            if (top == -1)
                return false;
            top--;
            needOperand = false;
        }
        else if (priority(ch) != 0)
        {
            if (needOperand)
                return false;
            while (top != -1 && operators[top] != '(' &&
                   (priority(operators[top]) > priority(ch) ||
                    (priority(operators[top]) == priority(ch) && ch != '^')))
                postfix += operators[top--];
            operators[++top] = ch;
            needOperand = true;
        }
        else
            return false;
    }
    if (needOperand)
        return false;
    while (top != -1)
    {
        if (operators[top] == '(')
            return false;
        postfix += operators[top--];
    }
    return true;
}

string toPrefix(string postfix)
{
    string values[200];
    int t = -1;
    for (int i = 0; i < (int)postfix.length(); i++)
    {
        char ch = postfix[i];
        if (isalnum((unsigned char)ch))
            values[++t] = string(1, ch);
        else
        {
            string right = values[t--];
            string left = values[t--];
            values[++t] = string(1, ch) + left + right;
        }
    }
    return values[t];
}

int main()
{
    string infix, postfix;
    cout << "------------ EXPRESSION CONVERSION ------------\n";
    cout << "Use single-letter or single-digit operands.\n";
    cout << "Operators: + - * / % ^ and parentheses.\n";
    cout << "Enter infix expression (maximum 199 characters): ";
    getline(cin, infix);
    if (infix.length() > 199 || !toPostfix(infix, postfix))
    {
        cout << "Invalid expression.\n";
        return 0;
    }
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << toPrefix(postfix) << endl;
    return 0;
}