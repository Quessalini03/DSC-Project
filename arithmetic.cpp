/*
-------------------------------------
int OpPrec(char c);
Input: a char variable.
Output: an integer representing the precedence of "c"
Description:
    Function will return:
    -  3 if "c" is '^'.
    -  2 if "c" is '/' or '*'.
    -  1 if "c" is '+' or '-'.
    - -1 if "c" is not an operator.

-------------------------------------

bool checkConsecutiveOp(int current, int next);


-------------------------------------

bool checkFloatingPoint(char current, char next);


------------------------------------- 

bool bracesIsBalanced(string str);
Input: a string
Output: whether braces in that string is balanced
Description:
    - Create a stack of char.
    - Traverse the string from left to right.
    - If see a opening brace "(", add it to stack. Else if see closing brace ")", check, if stack is empty, return false
    immediately, else pop the top of the stack.
    - Finally, count the number of elements in stack, return true if it is 0, return false otherwise.

-------------------------------------

bool checkPrecedence(string tmp, int counter, bool& condition, bool& check, bool& checkBrace, bool& firstOp, bool& firstOp2, bool& temp);
Input: a string, an integer, six references for six bool variables.
Output: true if there is a precedence error, otherwise false.
Description:
    -If tmp[counter] is '*' or '/' operator, "check" will be set to true. If it is '+' or '-' operator, "check" will be set to false 
    ("check" will act as a reminder)
    - If expressions having operators with the same level of order appear consecutively, meaning "check" will be set to the same 
    value twice, function will return true, else return false.
    - "temp" will be set to true if a bracket is met, and set to false if encounter a closing bracket. if tmp[counter] is an operator when "temp" is true, "checkBrace" will act
    in place of "check".

-------------------------------------

bool checkBlank(string str);
Input: a string
Output: true if there is a blank error, otherwise false
Description:
    - Function loops from the beginning to the end of str.
    - If a digit is encountered, the bool variable "check" will be set to true. If an operator or '.' is encountered, "check" will be set to false
    ("check" will act as a reminder). 
    - If a space ' ' is encountered and "check" is true, function will check the next character. If it is a digit, function will return true
    - After the loop, function will return false as there are no blank errors.
*/
