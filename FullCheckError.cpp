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
bool checkPrecedence(string tmp,int counter, bool& a, int& temp)
{
    if (tmp[counter] == ')') temp = 0;
    if (OpPrec(tmp[counter]) == 2)
    {
        if (temp == 0) a = false;
        if (a == true) return true;
        a = true;
        temp++;
    }
    if (OpPrec(tmp[counter]) == 1)
    {
        if (OpPrec(tmp[counter + 1]) == 1) return false;
        else if (tmp[counter + 1] == ' ')
        {
            while (tmp[++counter] == ' ') continue;
            if (OpPrec(tmp[counter + 1]) == 1) return false;
        }
        else
        {
            if (temp == 0) a = true;
            if (a == false) return true;
            a = false;
            temp++;
        }
    }
    return false;
}
bool checkBlank(string str)
{
    bool check = false;
    for (int i = 0; i <= str.size(); i++)
    {
        if (isdigit(str[i])) check = true;
        if (str[i] == ' ')
        {
            if (check == true)
            {
                if (isdigit(str[i + 1]))
                    return true;
                if (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^')
                    check = false;
            }
        }
    }
    return false;
}
int main()
{
    //driver code
    string tmp = "(  (( 1 +- 2 ))  -()2*   (9 ^  3))";
    bool check = true;
    int temp = 0;
    int counter = 0;
    while (tmp[counter] != '\0')
    {
        if (counter == 0)
        {
            if (!bracesIsBalanced(tmp))
            {
                cout << "Parenthesis error";
                break;
            }
            if (checkBlank(tmp))
            {
                cout << "Blank error";
                break;
            }
        }
        if (checkPrecedence(tmp,counter, check, temp))
        {
            cout << "Precedence Error";
            break;
        }
        if (OpPrec(tmp[counter]) >= 2) // only need to check if op = * or / of ^
        {
            if (checkConsecutiveOp(OpPrec(tmp[counter]), OpPrec(tmp[counter + 1])))
            {
                cout << "Invalid Input Error";
                break;
            }
        }
        if (tmp[counter] == '.')
        {
            if (checkFloatingPoint(tmp[counter], tmp[counter + 1]))
            {
                cout << "FLoating Point Error";
                break;
            }
        }
        counter++;
    }
    if (tmp[counter] == '\0') cout << "No Error" << endl;
    return 0;
}