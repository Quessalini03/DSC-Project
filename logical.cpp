/*
-------------------------------------

bool isOp(char c);
Input: a char variable
Output: true if "c" is an operator, otherwise false
Description:
	Function will return true if "c" is '+', '!', '&', '|', or '>',
	otherwise false.

-------------------------------------

bool checkConsecutiveOp(char current, char next);
Input: two char variables
Output: true if there is a consecutive operator error, otherwise false
Description:
	- If "next" is '!', function will return false.
	- If "current" and "next" are operators, function will return true,
	otherwise false.

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

bool checkPrecedence(string str, int count, char& check);
Input: a string, an integer, and a reference of a char variable
Output: true if there is a precedence error, otherwise false
Description:
	- "check" acts as a reminder of previous operators.
	- If str[count] is an opening bracket, "check" will be set to '\0'.
	- If str[count] is '&' while check is '|', function will return true, otherwise "check" will be set to '&'.
	- If str[count] is '|' while check is '&', function will return true, otherwise "check" will be set to '|'.
	- Function will return false at the end of the function.

-------------------------------------

bool checkBlank(string str);
Input: a string
Output: True if there is a blank error, otherwise false
Description:
	- Function loops from the beginning to the end of str.
	- If an alphabetic letter is encountered, the bool variable "check" will be set to true. If an operator is encountered, "check" will be set to false.
	- If a space ' ' is encountered and "check" is true, function will check the next character. If it is an alphabetic letter, function will return true.
	- After the loop, function will return false as there are no blank errors.
*/