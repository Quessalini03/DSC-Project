#include <iostream>
#include <stack>
#include <string>

using namespace std;

class node;

node* GenerateGraph(string s);
string postOrder(node* root);
void preprocess(string & str);
void errorCheck(string input);

class node
{
	string val = "";
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

	void showPrefix(node* current)
	{
		cout << current->val << " ";
		if (current->left != nullptr)
			showPrefix(current->left);
		if (current->right != nullptr)
			showPrefix(current->right);
	}

	void showPostfix(node* current)
	{
		if (current->left != nullptr)
			showPostfix(current->left);
		if (current->right != nullptr)
			showPostfix(current->right);

		cout << current->val << " ";
	}
};

int main()
{
	cout << "Input infix expression:\n";
	string s;
	getline(cin, s);
	
	preprocess(s);
	errorCheck(s);
	
	node* Head = GenerateGraph(s);
	string res = postOrder(Head);
	cout << res;
}

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

bool charSepByGap(char c1, char c2)
{
	bool b1 = (c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z');
	bool b2 = (c2 >= 'a' && c2 <= 'z') || (c2 >= 'A' && c2 <= 'Z');
	return b1 && b2;
}

void eraseBlank(string & str)
{
	int low = 0;
	int high = 0;
	bool remove = 0;
	for (int i = 0; str[i]; i++)
	{
		if (!remove)
		{
			if (str[i] == ' ')
			{
				low = i;
				high = i;
				remove = 1;
			}
		}
		else 
		{
			if (str[i] == ' ')
			{
				if (str[i+1] == ' ') continue;
			 	high = i;
			}
			if ( !charSepByGap(str[low - 1], str[high + 1]) )
			{
				str.erase(low, high - low + 1);
				i = low - 1;
			}
			remove = 0;
		}
	}
}

void removeEmptyParen(string & str)
{
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
}

void preprocess(string & str)
{
	eraseBlank(str);
	removeEmptyParen(str);
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

node* GenerateGraph(string s)
{
	s = FormatString_V2(s);
	return AnalysisV2(s);
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
