#include <iostream>
using namespace std;

bool isMatch(const string &s, const string &p)
{
    for (int i = 0, j = 0; i < s.size();)
    {
        if (j < p.size())
            if (s[i] == p[j])
            {
                i++;
                j++;
            }
            else
            {
                if (p[j] == '.')
                {
                    i++;
                    j++;
                }
                else if (p[j] == '*')
                {
                    if (s[i] == p[j - 1])
                    {
                        i++;
                    }
                    else if (p[j - 1] == '.')
                    {
                        return true;
                    }
                    else
                    {
                        if (j + 1 >= p.size())
                            return false;
                        if (s[i] == p[j + 1])
                        {
                            i++;
                            j += 2;
                        } else j++;
                    }
                } else j++;
            }
        else
            return false;
    }
    return true;
}

int main()
{
    string tests[] = {"ab", ".*c", "mississippi", "mis*is*p*.", "aa", "a", "aa", "a*", "ab", ".*", "aab", "a*b", "aab", "c*a*b"};
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i += 2)
        cout << (isMatch(tests[i], tests[i + 1]) ? "true" : "false") << endl;
    return 0;
}