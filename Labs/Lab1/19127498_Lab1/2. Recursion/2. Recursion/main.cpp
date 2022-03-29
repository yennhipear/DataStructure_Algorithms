#include <iostream>
using namespace std;

int sumOfSquares(int n)
{
    if (n == 0) return 0;
    return n * n + sumOfSquares(n - 1);
}

int GCD(int a, int b)
{
    if (b == 0) return a;
    return GCD(b, a % b);
}

bool isPalindrome(int a[], int n)
{
    if (n < 2) return true;
    if (a[0] != a[n - 1]) return false;
    return isPalindrome(a + 1, n - 2);
}

int Factorial(int n)
{
    if (n == 0) return 1;
    return n * Factorial(n - 1);
}

int countDigit(int a)
{
    if (a / 10 == 0)  return 1;
    return 1 + countDigit(a / 10);
}

int Fib(int n)
{
    if (n == 0 || n == 1)   return n;
    return Fib(n - 1) + Fib(n - 2);
}

int main()
{
    int choice;
    cout << "\t\t   *** RECURSION *** " << endl;
    cout << "1. Find the total square value of all integers that less than or equal to n " << endl;
    cout << "2. Find the greatest common divisor of 2 integers a and b " << endl;
    cout << "3. Determine if a given array is palindrome " << endl;
    cout << "4. Find the Factorial of a number " << endl;
    cout << "5. Count the digits of a given number " << endl;
    cout << "6. Find the nth Fibonacci number " << endl;
    do
    {
        cout << endl;
        cout << "--> Enter choice: ";   cin >> choice;
        switch (choice)
        {
            case 1:
                cout << "1. Find the total square value of all integers that less than or equal to n " << endl;
                int n;
                cout << "Enter n: ";    cin >> n;
                cout << "Sum of S = 1*1 + 2*2 +..+ n*n: " << sumOfSquares(n) << endl;
                break;
            
            case 2:
                cout << "2. Find the greatest common divisor of 2 integers a and b " << endl;
                int a, b;
                cout << "Enter a, b: ";    cin >> a >> b;
                cout << "GCD of a, b: " << GCD(a, b) << endl;
                break;

            case 3:
            {
                cout << "3. Determine if a given array is palindrome " << endl;
                int arr[5] = {1, 2, 3, 4, 1};
                cout << ((isPalindrome(arr, 5)) ? "YES" : "NO");
                break;
            }
                
            case 4:
            {
                cout << "4. Find the Factorial of a number " << endl;
                int num;
                cout << "Enter n: ";    cin >> num;
                cout << "Factorial of " << num << ": " << Factorial(num) << endl;
                break;
            }
                
            case 5:
            {
                cout << "5. Count the digits of a given number " << endl;
                int x;
                cout << "Enter n: ";    cin >> x;
                cout << "The digits of number is " << countDigit(x) << endl;
                break;
            }
                
            case 6:
            {
                cout << "6. Find the nth Fibonacci number " << endl;
                int y;
                cout << "Enter n: ";    cin >> y;
                cout << "The " << y << "th Fibonacci number is " << Fib(y) << endl;
                break;
            }
                
            default:
            {
                cout << "Please enter your choice again! " << endl;
                break;
            }
        }
    }
    while (choice != 0);
    
    return 0;
}
