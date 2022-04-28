#include<iostream>
#include<string.h>
#include<stack>
#include<sstream>
#include<cmath>
using namespace std;

class node
{
	string val;
	node* left;
	node* right;

public:
	node(string val, node* left = nullptr, node* right = nullptr)
	{
		this->val = val;
		this->left = left;
		this->right = right;
	}

	node* getLeft() { return left; }
	node* getRight() { return right; }
	string getVal() { return val; }

	void setLeft(node* node) { left = node; }
	void setRight(node* node) { right = node; }

	void showNode()
	{
		cout << "(";
		if (left != nullptr)
			left->showNode();

		cout << val;

		if (right != nullptr)
			right->showNode();
		cout << ")";
	}
};

node* GenerateGraph(string, int);
string preOrder(node*);
string postOrder(node*);
double postOrderEval(string);

int main()
{
	// string s = "485.25*253.45--25.698*(7/526.85-+-+-(85*--25/2578++25^(24-85+-25)))";

	// string s = "p&q&(!p|!!!r|r)|!!!(q+r+e+s+!(!(!t)))";
	// string s = "24/(6+2)-3";
	string s = "(69/3)+7-3*8";
	// Type: 1. Mathematic Version	2. Logical Version
	node* Head = GenerateGraph(s, 1);
	cout << "Original: " << s << '\n';
	string pre = preOrder(Head);
	cout << "Preorder: " << pre << '\n';
	string post = postOrder(Head);
	cout << "Postorder: " << post << '\n';
	double res = postOrderEval(post);
	cout << "Result: " << res << '\n';	
	//Head->showNode();
}

string FormatString_V1(string s)
{
	string str = "";
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '+' || s[i] == '-')
		{
			int count = s[i++] == '+' ? 0 : 1;

			while (s[i] == '+' || s[i] == '-')
			{
				if (s[i] == '-')
					count++;

				i++;
			}
			i--;

			if (count % 2 == 0)
				str += "+";
			else
				str += "-";
		}
		else
			str += s[i];
	}

	return str;
}

string FormatString_V2(string s)
{
	string str = "";
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '!')
		{
			int count = 1;
			i++;

			while (s[i] == '!')
			{
				count++;

				i++;
			}
			i--;

			if (count % 2 == 0)
				str += "";
			else
				str += "!";
		}
		else
			str += s[i];
	}

	return str;
}

node* FindingChar(string& subleft, string& subright, string const& charlist, string const& precharList, string expression)
{
	int numpara = 0;

	node* Head = nullptr;

	string* ptr = &subright;
	
	int lenEx = expression.length();
	int lenCh = charlist.length();
	int lenPreCh = precharList.length();
	for (int i = lenEx - 1; i >= 0; i--)
	{
		bool isOperator = false;
		for (int j = 0; j < lenCh; j++)
		{
			if (expression[i] == charlist[j])
			{
				if (numpara == 0)
				{
					if (i > 0)
					{
						bool isAdjacency = false;
						for (int k = 0; k < lenPreCh; k++)
						{
							if (expression[i - 1] == precharList[k])
							{
								isAdjacency = true;
								break;
							}
						}

						if (!isAdjacency)
						{
							if (Head == nullptr)
							{
								Head = new node(string(1, expression[i]));

								ptr = &subleft;

								isOperator = true;

								break;
							}
						}
					}
					else
					{
						if (Head == nullptr)
						{
							Head = new node(string(1, expression[i]));

							ptr = &subleft;

							isOperator = true;

							break;
						}
					}
				}
			}
		}
		if (isOperator == true)
			continue;

		if (expression[i] == '(') numpara++;
		else if (expression[i] == ')') numpara--;

		*ptr = expression[i] + *ptr;
	}

	return Head;
}

bool isExpression(string expression, string operatorlist)
{
	int lenEx = expression.length();
	int lenOp = operatorlist.length();
	for (int i = 0; i < lenEx; i++)
	{
		for (int j = 0; j < lenOp; j++)
		{
			if (expression[i] == operatorlist[j])
				return true;
		}
	}

	return false;
}

node* AnalysisV1(string s)
{
	if (!isExpression(s, "+-*/^")) // Check the string s is a expression or not
	{
		if (s[0] == '(')
		{
			s = s.substr(1, s.length() - 2);
		}
		return new node(s);
	}
	else
	{
		string subleft, subright; // Store the subexpression on the left and the right
		node* Head = nullptr; // Hold the Node

#pragma region Addition and Subtraction

		subleft = ""; subright = "";
		Head = FindingChar(subleft, subright, "+-", "*/^", s); // Finding the operator

		// If we found the operator "+-" then we will recursive 2 subexpression which we found in loop
		// If not we will continue checking to another operator with the order: "+-" -> "*/" -> "^" -> "()"
		if (Head != nullptr)
		{
			Head->setLeft(AnalysisV1(subleft == "" ? "0" : subleft));
			Head->setRight(AnalysisV1(subright == "" ? "0" : subright));

			return Head;
		}

#pragma endregion

		// The case not having operator "+-" outside the parathesis in the expression. Example: 5*6*8*(3+2)
#pragma region Multiplication and Divsion

		subleft = ""; subright = "";
		Head = FindingChar(subleft, subright, "*/", "", s); // Finding the operator

		// Recursive or not
		if (Head != nullptr)
		{
			Head->setLeft(AnalysisV1(subleft == "" ? "0" : subleft));
			Head->setRight(AnalysisV1(subright == "" ? "0" : subright));

			return Head;
		}

#pragma endregion

		// The case not having operator "+-" and "*/" outside the parathesis in the expression we will check exponential
		// The procedure as Multiplication and Division
#pragma region Exponential

		subleft = ""; subright = "";
		Head = FindingChar(subleft, subright, "^", "", s);

		if (Head != nullptr)
		{
			Head->setLeft(AnalysisV1(subleft == "" ? "0" : subleft));
			Head->setRight(AnalysisV1(subright == "" ? "0" : subright));

			return Head;
		}

#pragma endregion

		// The Case not having other operator in expression. Example: (3+2): We do not having operator outside the parathesis
		// Remove the parathesis at the beginning and ending then we will recursive the substring
		subleft = s.substr(1, s.length() - 2);
		return AnalysisV1(subleft);
	}
}

node* AnalysisV2(string s)
{
	if (!isExpression(s, "&|>!+"))
	{
		if (s[0] == '(')
		{
			s = s.substr(1, s.length() - 2);
		}

		return new node(s);
	}
	else
	{
		string subleft, subright;
		node* Head = nullptr;

		// Using the idea of computing number with the checking order: Imply > OR > XOR > AND > NOT > ()
#pragma region Imply Operator

		subleft = subright = "";

		Head = FindingChar(subleft, subright, ">", "", s);

		if (Head != nullptr)
		{
			Head->setLeft(AnalysisV2(subleft));
			Head->setRight(AnalysisV2(subright));

			return Head;
		}

#pragma endregion

		// If the expression doesn't have "Imply Operator" we will check this
#pragma region OR Operator

		subleft = subright = "";

		Head = FindingChar(subleft, subright, "|", "", s);

		if (Head != nullptr)
		{
			Head->setLeft(AnalysisV2(subleft));
			Head->setRight(AnalysisV2(subright));

			return Head;
		}
#pragma endregion

		// If the expression doesn't have "Imply Operator" and "OR operator" we will check this
#pragma region Exclusive Or Operator

		subleft = subright = "";

		Head = FindingChar(subleft, subright, "+", "", s);

		if (Head != nullptr)
		{
			Head->setLeft(AnalysisV2(subleft));
			Head->setRight(AnalysisV2(subright));

			return Head;
		}

#pragma endregion

		// If the expression doesn't have "Imply Operator" and "OR operator" and "XOR operator" we will check this
#pragma region And Operator

		subleft = subright = "";

		Head = FindingChar(subleft, subright, "&", "", s);

		if (Head != nullptr)
		{
			Head->setLeft(AnalysisV2(subleft == "" ? "0" : subleft));
			Head->setRight(AnalysisV2(subright == "" ? "0" : subright));

			return Head;
		}

#pragma endregion

		// If the expression doesn't have "Imply Operator" and "OR operator" and "XOR operator" and "NOT operator" we will check this
#pragma region Not Operator

		subleft = subright = "";

		Head = FindingChar(subleft, subright, "!", "", s);

		if (Head != nullptr)
		{
			if (subleft != "")
				Head->setLeft(AnalysisV2(subleft));

			Head->setRight(AnalysisV2(subright));

			return Head;
		}

#pragma endregion


		// The Case to find out parathesis
		// Remove the parathesis at the beginning and ending then we will recursive the substring
		subleft = s.substr(1, s.length() - 2);
		return AnalysisV2(subleft);
	}
}

node* GenerateGraph(string s, int Type)
{
	if (Type == 1)
	{
		s = FormatString_V1(s);
		return AnalysisV1(s);
	}
	else if (Type == 2)
	{
		s = FormatString_V2(s);
		return AnalysisV2(s);
	}
	else
		return nullptr;
}

string preOrder(node* root)
{
	if (root)
	{
		stack<node*> nStack;
		string retStr;
		retStr += root->getVal();
		if ( root->getRight() ) nStack.push( root->getRight() );
		if ( root->getLeft() ) nStack.push( root->getLeft() );
		while ( !nStack.empty() )
		{
			node* tempNode = nStack.top();
			retStr += ' ' + tempNode->getVal();
			nStack.pop();
			if ( tempNode->getRight() ) nStack.push( tempNode->getRight() );
			if ( tempNode->getLeft() ) nStack.push( tempNode->getLeft() );
		}
		return retStr;
	}
	else 
	{
		cout << "Tree does not exist!\n";
		return "";
	}
}

string postOrder(node* root)
{
	if (root)
	{
		stack<node*> nStack1;
		stack<node*> nStack2;		
		nStack1.push(root);
		while ( !nStack1.empty() )
		{
			node* tempNode = nStack1.top();
			nStack1.pop();
			nStack2.push(tempNode);
			if ( tempNode->getLeft() ) nStack1.push( tempNode->getLeft() );
			if ( tempNode->getRight() ) nStack1.push( tempNode->getRight() );
		}
		int stack2Size = nStack2.size();
		string retStr;
		for ( ; stack2Size - 1; stack2Size--)
		{
			retStr += nStack2.top()->getVal() + ' ';
			nStack2.pop();
		}
		retStr += nStack2.top()->getVal();
		nStack2.pop();
		return retStr;
	}
	else 
	{
		cout << "Tree does not exist!\n";
		return "";
	}
}

double postOrderEval(string str)
{
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
				double op2 = dStack.top();
				dStack.pop();
				double op1 = dStack.top();
				dStack.pop();
				switch (char(temp[0]))
				{
					case '*':
						dStack.push(op1*op2);
						break;
					case '/':
						if (!op2) 
						{
							cerr << "Divide by 0\n";
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
						dStack.push( pow(op1, op2) );
						break;
					default:
						cout << "Invalid operand " << temp << '\n';
						break;
					
				}
			}
		}
		else dStack.push( stod(temp) );
	}
	if ( !dStack.empty() ) return dStack.top();
	else return -696969.0;
}

