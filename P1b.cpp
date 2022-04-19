#include <iostream>
#include <stack>
#include <string>

using namespace std;


bool bracesIsBalanced(string str);

int main()
{
	string str;
	getline(cin, str);
	// ...
	return 0;
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
				else cStack.push( char(str[i]) );
			}
			else 
			{
				if (str[i] == ')') cStack.pop();
				else cStack.push( char(str[i]) );
			}
		}
	}
	if (cStack.size() == 0) return 1;
	else return 0;
}

