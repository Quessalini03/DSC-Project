#include<iostream>
#include<string.h>
#include<stack>
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

int main()
{
	//string s = "485.25*253.45--25.698*(7/526.85-+-+-(85*--25/2578++25^(24-85+-25)))";

	string s = "p&q&(!p|!!!r|r)|!!!(q+r+e+s+!(!(!t)))";

	// Type: 1. Mathematic Version	2. Logical Version
	node* Head = GenerateGraph(s, 2);

	Head->showNode();
}

string FormatString_V1(string s)
{
	string str = "";
	for (int i = 0; i < s.length(); i++)
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
	for (int i = 0; i < s.length(); i++)
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

	for (int i = expression.length() - 1; i >= 0; i--)
	{
		bool isOperator = false;
		for (int j = 0; j < charlist.length(); j++)
		{
			if (expression[i] == charlist[j])
			{
				if (numpara == 0)
				{
					if (i > 0)
					{
						bool isAdjacency = false;
						for (int k = 0; k < precharList.length(); k++)
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
	for (int i = 0; i < expression.length(); i++)
	{
		for (int j = 0; j < operatorlist.length(); j++)
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