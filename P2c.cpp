#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include <map>


using namespace std;

enum EvalOption
{
	prefix,
	postfix,
};

bool expressionEval(string str, EvalOption opt, map<string, bool> m);

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
	map<string, bool> m {{"p", 1}, {"q", 0}};
	bool res = expressionEval(str, EvalOption(opt), m);
	cout << "Result: " << res << '\n';	
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

bool expressionEval(string str, EvalOption opt, map<string, bool> m)
{
	switch (opt)
	{
		case prefix:
			str = reverse(str);
			break;
		case postfix:
			break;
	}
	
	stringstream sstr(str);
	stack<bool> bStack;
	string temp;
	while ( !sstr.eof() )
	{
		sstr >> temp;
		if ( temp.size() == 1)
		{
			if (temp[0] >= 'a' && temp[0] <= 'z' || (temp[0] >= 'A' && temp[0] <= 'Z')) 
			{
				bStack.push( m[temp] );
				continue;	
			}
			else if (temp[0] != '!')
			{
				bool op1;
				bool op2;
				if (opt == prefix)
				{
					op1 = bStack.top();
					bStack.pop();
					op2 = bStack.top();
					bStack.pop();
				}
				else 
				{
					op2 = bStack.top();
					bStack.pop();
					op1 = bStack.top();
					bStack.pop();
				}
				
				switch (char(temp[0]))
				{
					case '&':
						bStack.push(op1&op2);
						break;
					case '|':
						bStack.push(op1|op2);
						break;
					case '>':
						bStack.push((!op1)|op2);
						break;
					case '+':
						bStack.push(op1^op2);
						break;
					default:
						cout << "Illegal operator \"" << temp << "\"\n";
						break;
					
				}
			}
			else
			{
				bool op = bStack.top();
				bStack.pop();
				bStack.push(!op);
			}
		}
		else bStack.push( m[temp] );
	}
	if ( !bStack.empty() ) return bStack.top();
	else 
	{
		cerr << "Expression error!\n";
		exit(1);
	}
}
