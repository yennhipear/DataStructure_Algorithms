#ifndef _function_h
#define _function_h

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct Examinee
{
    string ID;
    float math, literature, physic,
        chemistry, biology, history,
        geography, civic_education,
        natural_science, social_science, foreign_language;
};

// Read data
Examinee ReadExaminee(string line_info);
vector<Examinee> ReadExamineeList(string file_name);

// Q1
string FindExamineeByLiterature(vector<Examinee> sorted_list, float v);

// Q2.1
vector<Examinee> GetTopHighestLiterature(vector<Examinee> list_examinee, int k);

// Q2.2
vector<Examinee> MergeTwoList(vector<Examinee> list1, vector<Examinee> list2);

#endif
