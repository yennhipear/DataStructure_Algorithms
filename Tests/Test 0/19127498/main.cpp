#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int do_something (int n)
{
    if (n < 100)    return n;
    else
        return (max(do_something(n / 10), n % 100));
}

int main()
{
    // input file
    string input_file;
    cin >> input_file;

    // MAIN here: do whatever you want in main function to debug
    // erase all your stuff (cin/cout) before submitting

    // read testcases and check
    string line;
    ifstream file(input_file);
    
    while(getline(file, line))
    {
        stringstream linestream(line);
        int value;
        linestream >> value;
        cout << value << " " << do_something(value) << "\n" ;
    }
    return 0;
}
