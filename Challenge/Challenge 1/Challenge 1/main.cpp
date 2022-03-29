#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <stack>
#include <iomanip>
#include <stdlib.h>
#include <cmath>

using namespace std;

void getInput (char* fileInp, int n, vector <string>& a)
{
    freopen(fileInp, "r", stdin);
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        string s;   getline(cin, s);
        a.push_back(s);
    }
}

bool checkError (string e)
{
    int i = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    // cnt1 : ()
    // cnt2 : []
    // cnt3 : {}

    // Error of brackets check
    while (i < e.size())
    {
        // Opened bracket +1
        // Closed bracket -1
        if (e[i] == '(') cnt1++;
        if (e[i] == '[') cnt2++;
        if (e[i] == '{') cnt3++;
        if (e[i] == ')') cnt1--;
        if (e[i] == ']') cnt2--;
        if (e[i] == '}') cnt3--;

        if (cnt1 < 0 || cnt2 < 0 || cnt3 < 0) return false; // Exist closed-bracket before opened

        i++;
    }

    i = 0;
    int preSb = 0;
    // check previous Bracket - 1, Operator - 2, Number - 3

    while (i < e.size())
    {
        string tmp = "";
        while (e[i] != ' ' && i < e.size()) tmp += e[i++];

        char c_head, c_tail;
        if (tmp.size()) {
            c_head = tmp[0];
            c_tail = tmp[tmp.size() - 1];
        }
        else return false; // Separated by more one single space " "

        // Check error sequental brackets or numbers
        if (c_head == '(' || c_head == '[' || c_head == '{' || (c_head >= '0' && c_head <= '9'))
            if (preSb == 1 || preSb == 3) return false;

        // Check error sequental operators
        if (c_head == '+' || c_head == '-' || c_head == '*' || c_head == '/' || c_head == '^')
            if (preSb == 2) return false;

        // Define type of next previous-symbol
        if (c_tail == ')' || c_tail == '}' || c_tail == ']') preSb = 1;
        if (c_tail == '+' || c_tail == '-' || c_tail == '*' || c_tail == '/' || c_tail == '^') preSb = 2;
        if (c_tail >= '0' && c_tail <= '9') preSb = 3;

        i++; // Move to next group of numbers/brackets or operator
    }

    return 1;
}

int getPriority(char c)
{
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

void modifyString(string& s)
{
    string res = "";
    int i = 0;
    while (s[i] == ' ' && i < s.size()) i++;
    while (i < s.size())
    {
        while (s[i] != ' ' && i < s.size()) res += s[i++];
        res += ' ';
        while (s[i] == ' ' && i < s.size()) i++;
    }
    s = "";
    for (int i = 0; i < res.size() - 1; i++) s += res[i];
}

void infix_to_postfix(string& e)
{
    stack <char> S;
    string res = "";

    S.push('#'); // # : Empty-stack-check character

    for (int i = 0; i < e.size(); i++)
    {
        if (e[i] == '(' || e[i] == '[' || e[i] == '{')  // Opened-bracket cases
        {
            S.push(e[i]);
        }
        else
        {
            if ((e[i] >= '0' && e[i] <= '9') || e[i] == '.' || e[i] == ' ') // Number or Floating-point or Space cases
                res += e[i];
            else
            {
                // Closed-bracket cases
                if (e[i] == ')' || e[i] == ']' || e[i] == '}')
                {
                    switch (e[i])
                    {
                        case ')':
                            while (S.top() != '#' && S.top() != '(')
                            {
                                res = res + " " + S.top();
                                S.pop();
                            }
                            break;
                            
                        case ']':
                            while (S.top() != '#' && S.top() != '[')
                            {
                                res = res + " " + S.top();
                                S.pop();
                            }
                            break;
                            
                        case '}':
                            while (S.top() != '#' && S.top() != '{')
                            {
                                res = res + " " + S.top();
                                S.pop();
                            }
                            break;
                    }
                    S.pop();
                }
                
                else
                {
                    if (e[i] == '+' || e[i] == '-' || e[i] == '*' || e[i] == '/' || e[i] == '^')
                    {  // Operators cases
                        while (S.top() != '#' && getPriority(S.top()) >= getPriority(e[i]))
                        {
                            res = res + " " + S.top();
                            S.pop();
                        }
                        S.push(e[i]);
                    }
                }
            }
        }
    }

    // Handle remaining characters in Stack
    while (S.top() != '#')
    {
        res = res + " " + S.top();
        S.pop();
    }

    modifyString(res); // Erase excess space beetween numbers, operators, brackets
    e = res;
}

void calExpression (string e)
{
    stack <float> S;

    int i = 0;

    while (i < e.size())
    {
        string tmp = "";

        while (e[i] == ' ' && i < e.size()) i++;
        while (e[i] != ' ' && i < e.size()) tmp += e[i++];

        float num = 0;
        if (tmp.size() == 1 && (tmp[0] < '0' || tmp[0]>'9'))
        {
            float num1, num2, res;

            num2 = S.top();
            S.pop();

            num1 = S.top();
            S.pop();

            switch (tmp[0])
            {
                case '+':
                    res = (num1 + num2);
                    break;
                case '-':
                    res = (num1 - num2);
                    break;
                case '*':
                    res = (num1 * num2);
                    break;
                case '/':
                    if (num2 == 0)
                    {
                        cout << "E\n";
                        return;
                    }
                    res = (num1 / num2);
                    break;
                case '^':
                    res = pow(num1, num2);
                    break;
            }

            S.push(res);
        }
        
        else
        {
            if (tmp.find('.') != string::npos)
            {
                float num1 = 0, num2 = 0;
                int j = 0, k = 1;

                while (tmp[j] != '.') num1 = num1 * 10 + tmp[j++] - '0';
                j++;
                while (j < tmp.size()) num2 = num2 + float((tmp[j++] - '0') / pow(10, k++));

                num = num1 + num2;
            }
            else
            {
                int j = 0;

                while (j < tmp.size()) num = num * 10 + tmp[j++] - '0';
            }

            S.push(num);
        }

        i++;
    }

    if (S.top() - int(S.top()) != 0) cout << setprecision(2) << fixed << S.top() << '\n';
    else cout << int(S.top()) << '\n';
}

int main(int argc, char* argv[])
{
    cin.tie(0);
    cout.tie(0);

    int n = 4;
    vector <string> listExpression;

    getInput(argv[1], n, listExpression);

    freopen(argv[4], "w", stdout);

    for (int i = 0; i < n; i++)
    {
        if (checkError(listExpression[i]))
        {
            string tmp = listExpression[i];
            if (argv[3][0] == 't')
            {
                infix_to_postfix(tmp);
                cout << tmp << ' ';
            }
            else calExpression(tmp);
        }
        else
            cout << "E\n";
    }
}

