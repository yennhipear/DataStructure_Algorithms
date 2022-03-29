#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Company
{
    string name;
    string profit_tax;
    string address;
};

//1. Read the companies information from a given file:
Company readCompany(string line_info)
{
    Company C;
    stringstream ss (line_info);

    getline(ss, C.name, '|');

    getline(ss, C.profit_tax, '|');

    getline(ss, C.address);

    return C;
}

vector <Company> ReadCompanyList(string file_name)
{
    ifstream fi;
    fi.open(file_name);

    string line_info;    getline(fi, line_info);    //pass \n

    vector <Company> res;
    while (getline(fi, line_info))
        res.push_back(readCompany(line_info));

    fi.close();

    return res;
}

void outputList (vector <Company> company_list)
{
    for (int i = 0; i < company_list.size(); i++)
    {
        cout << "\t\t\t *** COMPANY " << i << " *** " << endl;
        cout << "Name: "        << company_list[i].name         << endl;
        cout << "Profit tax: "  << company_list[i].profit_tax   << endl;
        cout << "Address: "     << company_list[i].address      << endl;
        cout << endl;
    }
}

//long long HashString(string company_name)
//{
//    long long ans = 0;
//    int count = 19;
//    int i = company_name.size();
//    long long p = 1;
//
//    while (count >= 0)
//    {
////        cout << p << endl;
//        ans += ((company_name[i] % (1000000000 + 9))) * p % (1000000000 + 9);
//        p = p * 31 % (1000000000 + 9);
//        count--;
//        i--;
//    }
//    return ans;
//}

//2. Hash a string (company name) function
long long HashString (string company_name)
{
    long long ans = 0;
    long long m = 1000000000 + 9;
    long long p = 1;
    for (int i = company_name.size() - 20; i < company_name.size(); i++)
    {
        ans += company_name[i] % m * p % m;
        p = p * 31 % m;
    }
    return ans;
}

//3. The function to create a hash table of size 11, generated from the Companies list
Company* CreateHashTable(vector <Company> list_company)
{
    Company *Array = new Company[11];
    int index;

    for (int i = 0; i < list_company.size(); i++)
    {
        index = HashString(list_company[i].name) % 11;
        while (Array[index].name != "")
        {
            index ++;
            if (index >= 11)
            {
                index = 0;
            }
        }
        Array[index] = list_company[i];
    }
    return Array;
}

//4. Add the info of 1 company into an existed hash table:
void Insert(Company* hash_table, Company company)
{
    int index = HashString(company.name) % 11;
    while (hash_table[index].name != "")
    {
        index ++;
    }
    hash_table[index] = company;
}

//5. Search for company information by its name
Company* Search(Company* hash_table, string company_name)
{
    Company *res = new Company;
    int index = HashString(company_name) % 11;
    for (int i = 0; i < 11; i++)
    {
        if (i == index)
        {
            if (hash_table[i].name == company_name)
            {
//                res->name       = hash_table[i].name;
//                res->profit_tax = hash_table[i].profit_tax;
//                res->address    = hash_table[i].address;
                res = &hash_table[i];
                return res;
            }
            else  index++;
        }
    }
    return NULL;
}

int main()
{
    cout << "// 1. Read the companies information from a given file " << endl << endl;
    vector <Company> company;
    company = ReadCompanyList("MST1.txt");
    outputList(company);

 /* *********************************************************************************** */

    cout << "// 2. Hash a string (company name) function " << endl << endl;
    for (int i = 0; i < company.size(); i++)
    {
        cout << HashString(company[i].name) << " " << company[i].name << endl;
    }
    cout << endl;

/* *********************************************************************************** */

    cout << "// 3. The function to create a hash table of size 11, generated from the Companies list "<< endl << endl;
    Company *C = CreateHashTable(company);
    for (int i = 0; i < 10; i++)
    {
        cout << i << ". " << C[i].name << endl;
    }
    cout << endl;

/* *********************************************************************************** */

    cout << "// 4. Add the info of 1 company into an existed hash table " << endl << endl;
    Company LYN;
    LYN.name = "CONG TY BAC MAI LAM";
    LYN.profit_tax = "19127498";
    LYN.address = "13A VO THI SAU, PHUONG KINH DINH, TP. PHAN RANG - THAP CHAM, NINH THUAN, VIETNAM";

    Insert(C, LYN);
    cout << "Hash Table after add 1 company: " << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << i << ". " << C[i].name << endl;
    }
    cout << endl;

/* *********************************************************************************** */

    cout << "// 5. Search for company information by its name" << endl << endl;
    Company* C1 = Search(C, "CONG TY BAC MAI LAM");
    if (C1 != NULL)
    {
        cout << C1->name << " | " << C1->profit_tax << " | " << C1->address << endl << endl;
    }
    else
        cout << "NOTHING TO PRINT" << endl << endl;

    return 0;
}


