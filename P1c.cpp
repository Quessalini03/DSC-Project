#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <limits>

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
			else 
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
				switch (char(temp[0]))
				{
					case '*':
						dStack.push(op1*op2);
						break;
					case '/':
						if (!op2) 
						{
							cerr << "Divide by 0 error!\n";
							exit(1);
						}
						dStack.push(op1/op2);
						break;
					case '+':
						dStack.push(op1+op2);
						break;
					case '-':
						dStack.push(op1-op2);
						break;
					case '^':
						if (op1 != 0.0 && op2 != 0.0) dStack.push( pow(op1, op2) );
						else 
						{
							cerr << "Undefined error!\n";
							exit(1);
						} 
						break;
					default:
						cout << "Illegal operator \"" << temp << "\"\n";
						break;
					
				}
			}
		}
		else dStack.push( stod(temp) );
	}
	if ( !dStack.empty() ) return dStack.top();
	else 
	{
		cerr << "Expression error!\n";
		exit(1);
	}
}
