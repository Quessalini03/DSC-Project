#include<iostream>
#include<string.h>
#include<stack>
using namespace std;

string removeEmptyParen(const string & s)	// require remove blanks and errors first
{
	string str = s;
	stack<int> iStack;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '(') iStack.push(i);
		else if (str[i] == ')') 
		{ 
			int topOfStack = iStack.top();
			if ((i - topOfStack) == 1)
			{
				str.erase(topOfStack, 2);
				i = iStack.top()-1;
				iStack.pop();
			}
			else iStack.pop();
		}
	}
	return str;
}

int main()
{
	string str = "6((())96((33))(()))9";
	cout << "Before: " << str << '\n';
	str = removeEmptyParen(str);
	cout << "After: " << str << '\n';
	return 0;
}
