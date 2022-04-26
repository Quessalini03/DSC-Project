#include <bits/stdc++.h>
using namespace std;

// ham tre ve thu tu thuc hien cua toan tu, gia tri tra ve cang lon thi cang uu tien
int OpPrec(char c)
{
    if (c == '^') return 3;
    if (c == '/' || c == '*') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}
// cac ham check Error 
bool checkConsecutiveOp(int current, int next)
{
    if ((current == 2 || current == 3) & (next == 2 || next == 3)) return true;
    return false;
}
bool checkFloatingPoint(char current, char next)
{
    if (current == '.' & ('0' > next || next > '9')) return true;
    return false;
}
bool bracesIsBalanced(string str) //  )((
{
    stack<char> cStack;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(' || str[i] == ')')
        {
            if (cStack.empty())
            {
                if (str[i] == ')') return 0;
                else cStack.push(char(str[i]));
            }
            else
            {
                if (str[i] == ')') cStack.pop();
                else cStack.push(char(str[i]));
            }
        }
    }
    if (cStack.size() == 0) return 1;
    else return 0;
}
bool checkPrecedence(string tmp, int counter, bool& check, int& temp)
{
    if (tmp[counter] == ')')
        if (tmp[counter - 1] != '(') temp = 0;
    if (OpPrec(tmp[counter]) == 2)
    {
        if (temp == 0) check = false;
        if (check == true) return true;
        check = true;
        temp++;
    }
    if (OpPrec(tmp[counter]) == 1)
    {
        if (OpPrec(tmp[counter]) == 1)
        {
            if (OpPrec(tmp[counter + 1]) == 1) return false;
            while (tmp[counter + 1] == ' ') counter++;
            if (OpPrec(tmp[counter + 1]) == 1) return false;
            if (temp == 0) check = true;
            if (check == false) return true;
            check = false;
            temp++;
        }
    }
    return false;
}
bool checkBlank(string str)
{
    bool check = false;
    for (int i = 0; str[i]; i++)
    {
        if (isdigit(str[i])) check = true;
        if (OpPrec(str[i]) == 1 || OpPrec(str[i]) == 2 || OpPrec(str[i]) == 3 || (str[i]) == '.') check = false;
        if (str[i] == ' ')
            if (check == true)
                if (isdigit(str[i + 1])) return true;
    }
    return false;
}
void errorCheck(string input)//function will cerr error name and exit(1) if there is an error
{
    bool check = true;
    int temp = 0;
    int counter = 0;
    while (input[counter] != '\0')
    {
        if (counter == 0)
        {
            if (!bracesIsBalanced(input))
            {
                cerr << "Parenthesis error";
                exit(1);
            }
            if (checkBlank(input))
            {
                cerr << "Blank error";
                exit(1);
            }
        }
        if (checkPrecedence(input, counter, check, temp))
        {
            cerr << "Precedence Error";
            exit(1);
        }
        if (OpPrec(input[counter]) >= 2) // only need to check if op = * or / of ^
        {
            if (checkConsecutiveOp(OpPrec(input[counter]), OpPrec(input[counter + 1])))
            {
                cerr << "Invalid Input Error";
                exit(1);
            }
        }
        if (input[counter] == '.')
        {
            if (checkFloatingPoint(input[counter], input[counter + 1]))
            {
                cerr << "FLoating Point Error";
                exit(1);
            }
        }
        counter++;
    }
}
int main()
{
    //driver code
    string tmp = "((1.2 () + 1 / 2 () + 2) - 2.3)";
    errorCheck(tmp);
    cout << "do something" << endl;
    return 0;
}