#include <iostream>
#include <string>

using namespace std;

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
            str.erase(low, high - low + 1);
            i = low - 1;
            remove = 0;
        }
    }
}

int main()
{
    string str = "   1 2 3   45  6     7     8    9    10    ";
    eraseBlank(str);
    cout << str;
}
