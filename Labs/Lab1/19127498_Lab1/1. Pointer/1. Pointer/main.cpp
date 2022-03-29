#include <iostream>
#include <cmath>

using namespace std;

void inputArray(int* &a, int &n)
{
    cout << "Enter value: ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
}

void dellocateArray(int* &a)
{
    delete []a;
}

void printArray(int* a, int &n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int findMin(int* a, int &n)
{
    int minVal = a[0];
    for (int i = 0; i < n; i++)
    {
        if (a[i] < minVal)  minVal = a[i];
    }
    return minVal;
}

int findMaxModulus(int* a, int &n)
{
    int maxAbsVal = abs(a[0]);
    for (int i = 0; i < n; i++)
    {
        if (abs(a[i]) > maxAbsVal)
            maxAbsVal = abs(a[i]);
    }
    return maxAbsVal;
}

bool isAscending(int* a, int &n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] >= a[i + 1])
            return false;
    }
    return true;
}

int sumOfArray(int* a, int &n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    return sum;
}

bool isPrimeNum (int x)
{
    int y = abs(x);
    if (y < 2)  return false;
    for (int i = 2; i <= sqrt(y); i++)
    {
        if (y % i == 0) return false;
    }
    return true;
}

int countPrime(int* a, int &n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (isPrimeNum(a[i]))
            count++;
    }
    return count;
}

void reverseArray(int* &a, int* b, int &n)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = a[n - i - 1];
    }
}

int LinearSearch(int* a, int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == key)
            return i;
    }
    return -1;
}

int SentinelLinearSearch(int* a, int n, int key)
{
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == key)
        {
            flag = true;
            return i;
        }
    }
    return -1;
}

int BinarySearch(int* a, int n, int key)
{
    int left = 0;
    int right = n - 1;
    
    while (left <= right)
    {
        int mid = left + (right - left) /2;

        if (a[mid] == key)
            return mid;
        if (key < a[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

int RecursiveBinarySearch(int* a, int left, int right, int key)
{
    if (left <= right)
    {
        int mid = left + (right - left) /2;

        if (a[mid] == key)
            return mid;
        if (key < a[mid])
            return RecursiveBinarySearch(a, left, mid - 1, key);
        
        return RecursiveBinarySearch(a, mid + 1, right, key);
    }
    return -1;
}


int main()
{
    int n;
    cout << "Enter n: ";    cin >> n;

    int *a = new int[n];
    int *b = new int[n];
    
    inputArray(a, n);
    cout << "- Array a: ";    printArray(a, n);
    
    cout << "- The smallest value from the array a: " << findMin(a, n) << endl;

    cout << "- The greatest absolute value from the array a: " << findMaxModulus(a, n) << endl;
    
    if (isAscending(a, n)) cout << "- Array a is ascending " << endl;
    else cout << "- Array a is not ascending " << endl;
    
    cout << "- The total value of all elements of the array: " << sumOfArray(a, n) << endl;
    
    cout << "- The number of prime numbers in the array: " << countPrime(a, n) << endl;
    
    reverseArray(a, b, n);
    cout << "- Array b: ";    printArray(b, n);
    cout << endl;
    
    int key1;
    cout << "Enter key 1: ";  cin >> key1;
    cout << "- Position of " << key1 << " (Sequential Search): " << LinearSearch(a, n, key1) << endl;
    cout << "- Position of " << key1 << " (Sequential Search - using flag): " << SentinelLinearSearch(a, n, key1) << endl;
    cout << endl;

    int key2;
    cout << "Enter key 2: ";  cin >> key2;
    int index1 = BinarySearch(a, n, key2);
    cout << "- Position of " << key2 << " (BinarySearch): " << index1 << endl;
    int index2 = RecursiveBinarySearch(a, 0, n - 1, key2);
    cout << "- Position of " << key2 << " (BinarySearch - using recursion): " << index2 << endl;
    
    dellocateArray(a);
    dellocateArray(b);
    
    cout << endl;
    return 0;
}
