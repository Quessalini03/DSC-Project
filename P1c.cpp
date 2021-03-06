#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

enum EvalOption
{
    prefix,
    postfix,
};

double expressionEval(string str, EvalOption opt);
string reverse(string str);

int main()
{
    int opt;
    bool valid = 0;
    cout << "Input expression:\n";
    string str;
    getline(cin, str);
    while (!valid)
    {
        cout << "Option (0 for prefix, 1 for postfix): ";
        int temp;
        cin >> temp;
        if (!cin)
        {
            cout << "Invalid option!\n";
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (temp == 0 || temp == 1) 
        {
            opt = temp;
            valid = 1;
        }
        else
        {
            cout << "Invalid option!\n";
            valid = 0;
        }
    }
    double res = expressionEval(str, EvalOption(opt));
    cout << "Result: " << fixed << setprecision(4) << res << '\n';    
    return 0;
}

string reverse(string str)
{
    stringstream ssin(str);
    stack<string> sStack;
    string temp;
    while ( !ssin.eof() )
    {
        ssin >> temp;
        sStack.push(temp); 
    }
    
    string retStr;
    retStr += sStack.top();
    sStack.pop();
    while ( !sStack.empty() )
    {
        retStr += ' ' + sStack.top();
        sStack.pop();
    }
    
    return retStr;
}

bool isOperator(char c)
{
    return (   (c == '+') || (c == '-')
            || (c == '*') || (c == '/')
            || (c == '^')              );

}

bool isNumber(char c)
{
    return ((c >= '0') && (c <= '9'));
}

void count(string str, int& leavesCount,int& internalNodesCount,int& minusSignCount)
{
    for (int i = 0; str[i]; ++i)
    {
        if (isOperator(str[i]))
        {
            ++internalNodesCount;
            if (str[i] == '-')
            ++minusSignCount;
        }
        else if (isNumber(str[i]))
        {
            ++leavesCount;
            while (str[i] != ' ' && str[i+1])
                ++i;
        }
    }
}

bool processing(string str)
{
    int leavesCount = 0;
    int internalNodeCount = 0;
    int minusSignCount = 0;
    count(str, leavesCount, internalNodeCount, minusSignCount);
    // A full binary tree -> internal nodes = (leaves - 1)/(2-1) = leaves - 1
    if ((leavesCount - 1) == internalNodeCount)
        return 1;
    // If all "-" are used to change sign, remove them from the tree
    // will give back the full binary tree again
    else if ((internalNodeCount - minusSignCount) == (leavesCount - 1))
        return 0;
    else
    {
        cerr    << "Ambiguous \"-\" detected:\nSome are used to substract, some are used to change sign\n"
                << "Solution: Add '0' before the number you want to change sign\n"
                << "Example: from prefix \"- - 10 5\" to \"- - 0 10 5\" (original infix: \"-10 - 5\")";
        exit(1);
    }
}

bool approxEqual(double a, double b, double absEpsilon = 1e-12, double relEpsilon = 1e-8)
{
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    double diff{ abs(a - b) };
    if (diff <= absEpsilon)
        return true;

    // Otherwise use Knuth's algorithm
    return (diff <= (max(abs(a), abs(b)) * relEpsilon));
}

double expressionEval(string str, EvalOption opt)
{
    switch (opt)
    {
        case prefix:
            str = reverse(str);
            break;
        case postfix:
            break;
    }
    // 1 means all minus sign are used to do subtraction, 0 means used to change sign
    bool areAllMinus = processing(str);
    stringstream sstr(str);
    stack<double> dStack;
    string temp;
    while ( !sstr.eof() )
    {
        sstr >> temp;
        if ( temp.size() == 1)
        {
            if (temp[0] >= '0' && temp[0] <= '9') 
            {
                dStack.push( stod(temp) );
                continue;    
            }
            else if (temp[0] != '-')
            {
                double op1;
                double op2;
                // the popping order is important because in the stack of postorder, the first operand is below
                // the second operand, while it is the opposite for preorder stack
                if (opt == prefix)
                {
                    op1 = dStack.top();
                    dStack.pop();
                    op2 = dStack.top();
                    dStack.pop();
                }
                else 
                {
                    op2 = dStack.top();
                    dStack.pop();
                    op1 = dStack.top();
                    dStack.pop();
                }
                switch (char(temp[0]))
                {
                    case '*':
                        dStack.push(op1 * op2);
                        break;
                    case '/':
                        if (approxEqual(op2, 0.0)) // if the 2nd operand is 0.0
                        {
                            cerr << "Divide by 0 error!\n";
                            exit(1);
                        }
                        dStack.push(op1 / op2);
                        break;
                    case '+':
                        dStack.push(op1 + op2);
                        break;
                    case '^':
                        if ( !(approxEqual(op1, 0.0) && approxEqual(op2, 0.0)) )
                            dStack.push( pow(op1, op2) );
                        else // 1st operand and 2nd operand are both 0.0
                        {
                            cerr << "Undefined error!\n";
                            exit(1);
                        } 
                        break;
                    default:
                        cout << "Illegal operator \"" << temp << "\"!\n";
                        exit(1);

                }
            }
            else
            {
                if (areAllMinus)
                {
                    double op1;
                    double op2;
                    if (opt == prefix)
                    {
                        op1 = dStack.top();
                        dStack.pop();
                        op2 = dStack.top();
                        dStack.pop();
                    }
                    else 
                    {
                        op2 = dStack.top();
                        dStack.pop();
                        op1 = dStack.top();
                        dStack.pop();
                    }
                    dStack.push(op1 - op2);
                }
                else
                {
                    double op = dStack.top();
                    dStack.pop();
                    dStack.push(-op);
                }
            }
        }
        else dStack.push( stod(temp) );
    }
    return dStack.top();
}
