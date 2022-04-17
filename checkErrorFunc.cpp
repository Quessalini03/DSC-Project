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
    if ((current == 2 || current == 3) & (next== 2 || next== 3)) return true;
    return false;
}

bool checkFloatingPoint(char current, char next)
{
    if (current == '.' & ('0' > next || next > '9')) return true;
    return false;
}

bool checkParenthesis(bool startBlock, bool stopBlock)
{
    //startBlock va stopBlock lay tu ham thuat toan
    //chuyen startBlock = true sau khi co dau "(" va chuyen stopBlock = true sau khi co dau ")"
    //sau khi kiem tra tre ca startBlock va stopBlock ve false
    if (startBlock == true & stopBlock == false)
    { 
        startBlock = false;
        stopBlock == false;
        return true;
    }
    if (startBlock == false & stopBlock == true) 
    { 
        startBlock = false;
        stopBlock == false;
        return true;
    }
    startBlock = false;
    stopBlock == false;
    return false;
}
int main()
{
    //driver code
    string tmp = "2.4++(6/(2*3))";
    bool startBlock = false;
    bool stopBlock = false;
    int counter = 0;
    while (tmp[counter] != '\0')
    {
        if (OpPrec(tmp[counter]) >= 2) // only need to check if op = * or / of ^
        {
            if (checkConsecutiveOp(OpPrec(tmp[counter]) , OpPrec(tmp[counter+1])))
            {
                cout << "Invalid Input Error";
                break;
            }
        }
        if (tmp[counter] == '.')
        {
            if (checkFloatingPoint( tmp[counter] , tmp[counter+1]))
            {
                cout << "FLoating Point Error";
                break;
            }
        }
        counter++;
    }
    if (tmp[counter] == '\0' ) cout << "No Error" << endl;
    return 0;
}