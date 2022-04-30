#include <iostream>
#include <stack>
#include <string>

using namespace std;

class node;

bool bracesIsBalanced(string str);
int OpPrec(char c);
bool checkConsecutiveOp(int current, int next);
bool checkFloatingPoint(char current, char next);
bool checkPrecedence(string tmp, int counter, bool& check, int& temp);
bool checkBlank(string str);
void errorCheck(string input);
void eraseBlank(string & str);
void removeEmptyParen(string & str);
void preprocess(string & str);
node* GenerateGraph(string s);
string postOrder(node* root);
void reduceConsecutiveAddnSub(string & str);

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

int main()
{
	cout << "Input infix expression:\n";
	string str;
	getline(cin, str);

	preprocess(str);
	errorCheck(str);
	
	node* root = GenerateGraph(str);
	string pre = postOrder(root);
	cout << "Postfix form: " << pre << '\n';
	return 0;
}

bool bracesIsBalanced(string str)
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
    if ((current == 2 || current == 3) & (next == 2 || next == 3)) return true;
    return false;
}

bool checkFloatingPoint(char current, char next)
{
    if (current == '.' & ('0' > next || next > '9')) return true;
    return false;
}

bool checkPrecedence(string tmp, int counter, bool& check, int& temp)
{
    if (tmp[counter] == ')')
        if (tmp[counter - 1] != '(') temp = 0;
    if (OpPrec(tmp[counter]) == 2)
    {
        if (temp == 0) check = false;
        if (check == true) return true;
        check = true;
        temp++;
    }
    if (OpPrec(tmp[counter]) == 1)
    {
        if (OpPrec(tmp[counter]) == 1)
        {
            if (OpPrec(tmp[counter + 1]) == 1) return false;
            while (tmp[counter + 1] == ' ') counter++;
            if (OpPrec(tmp[counter + 1]) == 1) return false;
            if (temp == 0) check = true;
            if (check == false) return true;
            check = false;
            temp++;
        }
    }
    return false;
}

bool checkBlank(string str)
{
    bool check = false;
    for (int i = 0; str[i]; i++)
    {
        if (isdigit(str[i])) check = true;
        if (OpPrec(str[i]) == 1 || OpPrec(str[i]) == 2 || OpPrec(str[i]) == 3 || (str[i]) == '.') check = false;
        if (str[i] == ' ')
            if (check == true)
                if (isdigit(str[i + 1])) return true;
    }
    return false;
}

void errorCheck(string input)//function will cerr error name and exit(1) if there is an error
{
    bool check = true;
    int temp = 0;
    int counter = 0;
    while (input[counter] != '\0')
    {
        if (counter == 0)
        {
            if (!bracesIsBalanced(input))
            {
                cerr << "Parenthesis error";
                exit(1);
            }
            if (checkBlank(input))
            {
                cerr << "Blank error";
                exit(1);
            }
        }
        if (checkPrecedence(input, counter, check, temp))
        {
            cerr << "Precedence Error";
            exit(1);
        }
        if (OpPrec(input[counter]) >= 2) // only need to check if op = * or / of ^
        {
            if (checkConsecutiveOp(OpPrec(input[counter]), OpPrec(input[counter + 1])))
            {
                cerr << "Invalid Input Error";
                exit(1);
            }
        }
        if (input[counter] == '.')
        {
            if (checkFloatingPoint(input[counter], input[counter + 1]))
            {
                cerr << "FLoating Point Error";
                exit(1);
            }
        }
        counter++;
    }
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
			if ( !(str[low - 1] >= '0' && str[low - 1] <= '9' && str[high + 1] >= '0' && str[high + 1] <= '9') )
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

void reduceConsecutiveAddnSub(string & str)
{
	int low = -1;
	int high = -1;
	int countSub = 0;
	int countAdd = 0;
	bool reduceMode = 0;
	for (int i = 0; str[i]; i++)
	{
		if (!reduceMode)
		{
			bool seeAddOrSub = str[i] == '+' || str[i] == '-';
			if (seeAddOrSub)
			{
				low = i;
				high = i;
				reduceMode = 1;
				countAdd += int(str[i] == '+');
				countSub += int(str[i] == '-');
			}
		}
		else
		{
			bool seeAddOrSub = str[i] == '+' || str[i] == '-';
			bool seeAddOrSubNext = str[i+1] == '+' || str[i+1] == '-';
			if (seeAddOrSub)
			{
				high = i;
				countAdd += int(str[i] == '+');
				countSub += int(str[i] == '-');
				if (seeAddOrSubNext) continue;
			}
			if ( (countAdd + countSub) > 1 )
			{
				str.erase(low, high - low + 1);
				int remain = countSub % 2;
				if (remain) str.insert(low, "-");
				else str.insert(low, "+");
				i = low - 1;
			}
			low = -1;
			high = -1;
			reduceMode = 0;
			countAdd = 0;
			countSub = 0;
		}
	}
}

void preprocess(string & str)
{
	eraseBlank(str);
	removeEmptyParen(str);
	reduceConsecutiveAddnSub(str);
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

node* GenerateGraph(string s)
{
	return AnalysisV1(s);
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
