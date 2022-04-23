#include <iostream>
#include <string>
#include <stack>

using namespace std;

void reduceConsecutiveAddnSub(string & str)	// need to remove blanks prior to this
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

int main ()
{
	string str = "3+-++-+-4+--++-+-5*6+7-8";
	cout << "Before: " << str << '\n';
	reduceConsecutiveAddnSub(str);
	cout << "After: " << str << '\n';
	cout << "Expected: " << "3-4+5*6+7-8";
	return 0;
}
