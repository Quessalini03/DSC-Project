#include <bits/stdc++.h>
using namespace std;
bool isOp(char c)
{
    if (c == '+' || c == '!' || c == '&' || c == '|' || c == '>') return true;
    return false;
}
// cac ham check Error 
bool checkConsecutiveOp(char current, char next)
{
    if (next == '!') return false;
    if (isOp(current) && isOp(next)) return true;
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
bool checkPrecedence(string str, int count, char& check)
{
    if (str[count] == '(') check = '\0';
    if (str[count] == '&')
    {
        if (check == '|') return true;
        else check = '&';
    }
    if (str[count] == '|')
    {
        if (check == '&') return true;
        else check = '|';
    }
    return false;
}
bool checkBlank(string str)
{
    bool check = false;
    for (int i = 0; str[i]; i++)
    {
        if (isalpha(str[i])) check = true;
        if (isOp(str[i])) check = false;
        if (str[i] == ' ')
            if (check == true)
                if (isalpha(str[i + 1])) return true;
    }
    return false;
}
void errorCheck(string input)//function will cerr error name and exit(1) if there is an error
{
    int counter = 0;
    char check = '\0';
    while (input[counter] != '\0')
    {
        if (counter == 0)
        {
            if (!bracesIsBalanced(input))
            {
                cerr << "syntax error";
                exit(1);
            }
            if (checkBlank(input))
            {
                cerr << "syntax error";
                exit(1);
            }
        }      
        if (checkConsecutiveOp(input[counter], input[counter + 1]))
        {
            cerr << "undefined error";
            exit(1);
        }
        if (checkPrecedence(input, counter, check))
        {
            cerr << "multi-output error";
            exit(1);
        }        
        counter++;
    }
}
int main()
{
    //driver code
    string tmp = "!!  p & q &( !  pc|! ! ! ra|r)|!! !(q>  r()+  e +s+!(!(!t )))";
    errorCheck(tmp);
    cout << "do something" << endl;
    return 0;
}