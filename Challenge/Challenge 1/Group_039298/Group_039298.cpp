#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <stack>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

using namespace std;

void getInput(char* fileInp, int n, vector<string>& a) {
	freopen(fileInp, "r", stdin);

	for (int i = 0; i < n; i++) {
		string s;
		getline(cin, s);
		a.push_back(s);
	}
}

bool checkError(string e) {
	// Check strange symbols
	// ***
	for (int i = 0; i < e.size(); i++)
		if (!(e[i] >= '0' && e[i] <= '9') &&
			!(e[i] == '(' || e[i] == ')' || e[i] == '[' || e[i] == ']' || e[i] == '{' || e[i] == '}') &&
			!(e[i] == '+' || e[i] == '-' || e[i] == '*' || e[i] == '*' || e[i] == '/' || e[i] == '^') &&
			!(e[i] == '.' || e[i] == ' ')) return false;
	// ***

	// Check error of brackets's order
	// ***
	stack<char> S;
	S.push('#'); // Pivot element of Stack

	for (int i = 0; i < e.size(); i++) {
		if (e[i] == '(' || e[i] == '[' || e[i] == '{') S.push(e[i]);
		if (e[i] == ')' || e[i] == ']' || e[i] == '}') {
			switch (e[i]) {
			case ')':
				if (S.top() != '(') return false;
				break;
			case ']':
				if (S.top() != '[') return false;
				break;
			case '}':
				if (S.top() != '{') return false;
				break;
			}
			S.pop();
		}
	}
	// ***

	// Error of brackets's number check
	// ***
	int i = 0;
	int cnt1 = 0, cnt2 = 0, cnt3 = 0;
	// cnt1 : case ()
	// cnt2 : case []
	// cnt3 : case {}

	while (i < e.size()) {
		// Opened bracket +1
		// Closed bracket -1
		if (e[i] == '(') cnt1++;
		if (e[i] == '[') {
			cnt2++;
			if (cnt1) return false; // Wrong priority brackets ([])
		}
		if (e[i] == '{') {
			cnt3++;
			if (cnt1 || cnt2) return false; // Wrong priority brackets ({}); [{}]
		}
		if (e[i] == ')') cnt1--;
		if (e[i] == ']') cnt2--;
		if (e[i] == '}') cnt3--;

		if (cnt1 < 0 || cnt2 < 0 || cnt3 < 0)
			return false; // Exist closed-bracket before opened

		i++;
	}

	if (cnt1 || cnt2 || cnt3) return false; // Excess opened brackets
	// ***

	// Check order of operands, operators
	// ***
	i = 0;
	int preSb = 0;
	// Check previous Bracket - 1, Operator - 2, Number - 3

	while (i < e.size()) {
		string tmp = "";
		while (e[i] != ' ' && i < e.size()) {  // Get group of characters
			tmp += e[i];
			i++;
		}

		// Head and tail of group of characters
		char c_head, c_tail;

		// Error of exist more than 1 space ' ' between operands, operators
		if (tmp.size()) {
			c_head = tmp[0];
			c_tail = tmp[tmp.size() - 1];
		}
		else
			return false;

		if (c_tail == '.') return false; // Error floating-point numbers 


		int cnt = 0;
		for (int i = 0; i < tmp.size(); i++) cnt += (tmp[i] == '.');
		if (cnt > 1) return false; // Exist more than 1 '.' in float number

		// Check error sequental brackets or numbers
		if (c_head == '(' || c_head == '[' || c_head == '{' || (c_head >= '0' && c_head <= '9'))
			if (preSb == 1 || preSb == 3)
				return false;

		// Check error sequental operators
		if (c_head == '+' || c_head == '-' || c_head == '*' || c_head == '/' || c_head == '^')
			if (preSb == 2)
				return false;

		// Define type of next previous-symbol
		if (c_tail == ')' || c_tail == '}' || c_tail == ']') preSb = 1;
		if (c_tail == '+' || c_tail == '-' || c_tail == '*' || c_tail == '/' || c_tail == '^') preSb = 2;
		if (c_tail >= '0' && c_tail <= '9') preSb = 3;

		i++; // Move to next group of numbers/brackets or operator
	}
	// ***

	return 1;
}

int getPriority(char c) { // Get priority of operators and other characters
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/') return 2;
	if (c == '^') return 3;
	return 0;
}

void modifyString(string& s) { // Erase excess space
	string res = "";
	int i = 0;

	while (s[i] == ' ' && i < s.size()) i++;

	while (i < s.size()) {
		while (s[i] != ' ' && i < s.size()) res += s[i++];
		res += ' ';
		while (s[i] == ' ' && i < s.size()) i++;
	}

	s = "";
	for (int i = 0; i < res.size() - 1; i++) s += res[i];
}

void infix_to_postfix(string& e) { // Convert infix expression to postfix expression
	stack<char> S;
	string res = "";

	S.push('#'); // # : Empty-stack-check character

	for (int i = 0; i < e.size(); i++)
		if (e[i] == '(' || e[i] == '[' || e[i] == '{')  // Opened-bracket cases
			S.push(e[i]);
		else
			if ((e[i] >= '0' && e[i] <= '9') || e[i] == '.' || e[i] == ' ') // Number or Floating-point or Space cases
				res += e[i];
			else
				//
				// Closed-bracket cases
				//
				if (e[i] == ')' || e[i] == ']' || e[i] == '}') {
					switch (e[i]) {
					case ')':
						while (S.top() != '#' && S.top() != '(') {
							res = res + " " + S.top();
							S.pop();
						}
						break;
					case ']':
						while (S.top() != '#' && S.top() != '[') {
							res = res + " " + S.top();
							S.pop();
						}
						break;
					case '}':
						while (S.top() != '#' && S.top() != '{') {
							res = res + " " + S.top();
							S.pop();
						}
						break;
					}

					S.pop();
				}
				else
					// 
					// Operators cases
					//
					if (e[i] == '+' || e[i] == '-' || e[i] == '*' || e[i] == '/' || e[i] == '^') {
						while (S.top() != '#' && getPriority(S.top()) >= getPriority(e[i])) {
							res = res + " " + S.top();
							S.pop();
						}
						S.push(e[i]);
					}

	// Handle remaining characters in Stack
	while (S.top() != '#') {
		res = res + " " + S.top();
		S.pop();
	}

	modifyString(res); // Erase excess space beetween numbers, operators, brackets
	e = res;
}

void calExpression(string e) {
	stack<float> S;

	int i = 0;

	while (i < e.size()) {
		string tmp = "";

		while (e[i] == ' ' && i < e.size()) i++;
		while (e[i] != ' ' && i < e.size()) tmp += e[i++]; // Get number or operator

		float num = 0;
		if (tmp.size() == 1 && (tmp[0] < '0' || tmp[0]>'9')) { // Case of operator
			float num1, num2, res;

			num2 = S.top(); //
			S.pop();		// Two elements in top of Stack 
							// will be popped out to calculate
			num1 = S.top(); // Format: num1 + op + num2
			S.pop();		//

			switch (tmp[0]) {
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
				if (num2 == 0) {
					cout << "E\n";
					return;
				}
				res = (num1 / num2);
				break;
			case '^':
				res = pow(num1, num2);
				break;
			}

			S.push(res); // Push result of operation to stack again, in order to calculate continous.
		}
		else {
			//
			// Case of float numbers
			//
			if (tmp.find('.') != string::npos) {
				float num1 = 0, num2 = 0;
				int j = 0, k = 1;

				while (tmp[j] != '.') num1 = num1 * 10 + tmp[j++] - '0';
				j++;
				while (j < tmp.size()) num2 = num2 + float((tmp[j++] - '0') / pow(10, k++));

				num = num1 + num2;
			}
			else {
				// 
				// Case of integers
				//
				int j = 0;

				while (j < tmp.size()) num = num * 10 + tmp[j++] - '0';
			}

			S.push(num);
		}

		i++;
	}

	// Modify cout integer or float type
	if (S.top() - int(S.top()) != 0) cout << setprecision(2) << fixed << S.top() << '\n';
	else cout << int(S.top()) << '\n';
}

int main(int argc, char* argv[]) {
	cin.tie(0);
	cout.tie(0);

	int n = 0;
	vector<string> listExpression;

	// Convert to get value of n
	for (int i = 0; i < strlen(argv[2]); i++) n = n * 10 + argv[2][i] - '0';

	// argv[1] - address of input file
	getInput(argv[1], n, listExpression);

	// argv[4] - address of output file
	freopen(argv[4], "w", stdout);

	for (int i = 0; i < n; i++)
		if (checkError(listExpression[i])) { // Check error (true-valid / false-invalid)
			string tmp = listExpression[i];

			infix_to_postfix(tmp); // Convert infix expression to postfix expression

			if (argv[3][1] == 't')
				cout << tmp << '\n';
			else
				if (argv[3][1] == 'c') calExpression(tmp);
				else
					cout << "E\n";
		}
		else
			cout << "E\n";
}

