#include "function.h"

// Read data
//float StringtoFloat(string line_info, int& index, char stopChar = ',')
//{
//    string temp = "";
//    while (line_info[index] != stopChar)
//    {
//        temp += line_info[index++];
//    }
//    index++;
//    if (temp.size() == 0)   return 0;
//    else return stof(temp);
//}
//
//Examinee ReadExaminee(string line_info)
//{
//    Examinee E;
//    int index = 0;
//
//    //ID
//    E.ID = "";
//    while (line_info[index] != ',')
//    {
//        E.ID += line_info[index++];
//    }
//    index++;
//
//    //Name == " "
//    index++;
//
//    //Scores
//    E.math              = StringtoFloat(line_info, index);
//    E.literature        = StringtoFloat(line_info, index);
//    E.physic            = StringtoFloat(line_info, index);
//    E.chemistry         = StringtoFloat(line_info, index);
//    E.biology           = StringtoFloat(line_info, index);
//    E.history           = StringtoFloat(line_info, index);
//    E.geography         = StringtoFloat(line_info, index);
//    E.civic_education   = StringtoFloat(line_info, index);
//    E.natural_science   = StringtoFloat(line_info, index);
//    E.social_science    = StringtoFloat(line_info, index);
//    E.foreign_language  = StringtoFloat(line_info, index);
//    E.natural_science   = E.physic + E.chemistry + E.biology;
//    E.social_science    = E.history + E.geography + E.civic_education;
//
//    return E;
//}

//vector <Examinee> ReadExamineeList(string file_name)
//{
//    ifstream fi;
//    fi.open(file_name);
//
//    string line_info;    getline(fi, line_info); //pass \n
//
//    vector <Examinee>  res;
//    while (getline(fi, line_info))
//        res.push_back(ReadExaminee(line_info));
//
//    fi.close();
//
//    return res;
//}

Examinee ReadExaminee(string line_info)
{
    Examinee E;
    stringstream ss (line_info);
    string name;
    string temp;
    
    getline (ss, E.ID, ',');
    getline (ss, name, ',');
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        E.math = stof(temp);
    }
    else E.math = 0;
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        E.literature = stof(temp);
    }
    else E.literature = 0;
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        E.physic = stof(temp);
    }
    else E.physic = 0;
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        E.chemistry = stof(temp);
    }
    else E.chemistry = 0;

    getline (ss, temp, ',');
    if (temp != "")
    {
        E.biology = stof(temp);
    }
    else E.biology = 0;
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        E.history = stof(temp);
    }
    else E.history = 0;
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        E.geography = stof(temp);
    }
    else E.geography = 0;
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        E.civic_education = stof(temp);
    }
    else E.civic_education = 0;

    E.natural_science = E.physic + E.chemistry + E.biology;
    E.social_science  = E.history + E.geography + E.civic_education;

    getline (ss, temp, ',');
    getline (ss, temp, ',');
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        E.foreign_language = stof(temp);
    }
    else E.foreign_language = 0;
    
    return E;
}

vector<Examinee> ReadExamineeList(string file_name)
{
    ifstream fi;
    fi.open(file_name);
    vector <Examinee> res;

    string line_info;   getline (fi, line_info);

    while (getline(fi, line_info))
    {
        res.push_back(ReadExaminee(line_info));
    }

    fi.close();
    return res;
}

void outputList (vector <Examinee> examinee_list)
{
    for (int i = 0; i < examinee_list.size(); i++)
    {
        cout << "\t\t\t *** EXAMINEE " << i << " *** " << endl;
        cout << "ID: "               << examinee_list[i].ID                 << endl;
        cout << "Math: "             << examinee_list[i].math               << endl;
        cout << "Literature: "       << examinee_list[i].literature         << endl;
        cout << "Physic: "           << examinee_list[i].physic             << endl;
        cout << "Chemistry: "        << examinee_list[i].chemistry          << endl;
        cout << "Biology: "          << examinee_list[i].biology            << endl;
        cout << "History: "          << examinee_list[i].history            << endl;
        cout << "Geography: "        << examinee_list[i].geography          << endl;
        cout << "Civic education: "  << examinee_list[i].civic_education    << endl;
        cout << "Natural science : " << examinee_list[i].natural_science    << endl;
        cout << "Social science: "   << examinee_list[i].social_science     << endl;
        cout << "Foreign language: " << examinee_list[i].foreign_language   << endl;

        cout << endl;
    }
}

// Q1
string FindExamineeByLiterature(vector<Examinee> sorted_list, float v)
{
    string res;
    for (int i = 0; i < sorted_list.size(); i++)
    {
        if (sorted_list[i].literature == v)
        {
            res = sorted_list[i].ID;
            break;
        }
    }
    if (res == "") { return "Not Found"; }
    return res;
}

// Q2.1
//vector<Examinee> GetTopHighestLiterature(vector<Examinee> list_examinee, int k)
//{
//    vector <Examinee> res;
//    vector <bool> used(list_examinee.size(), false);
//
//    int index;
//
//    while (k > 0)
//    {
//        float max = 0;
//        for (int i = 0; i < list_examinee.size(); i++)
//        {
//            if (used[i] == false)
//            {
//                if (list_examinee[i].literature > max)
//                {
//                    max = list_examinee[i].literature;
//                    index = i;
//                }
//            }
//        }
//        used[index] = true;
//        k--;
//    }
//
//    for (int i = 0; i < list_examinee.size(); i++)
//    {
//        if (used[i] == true)
//            res.push_back(list_examinee[i]);
//    }
//    return res;
//}

int partition(vector <Examinee> &a, int left, int right)
{
    float pivot = a[(left + right) / 2].literature;
    int i = left, j = right;

    while (i <= j)
    {
        while (a[i].literature > pivot)     { i++; }
        while (a[j].literature < pivot)     { j--; }
        if (i <= j)
        {
            swap (a[i], a[j]);
            i++;
            j--;
        }
    }
    return i;
}

void QuickSort (vector <Examinee> &a, int left, int right)
{
    if (left < right)
    {
        int pi = partition(a, left, right);
        QuickSort(a, left, pi - 1);
        QuickSort(a, pi, right);
    }
}

vector<Examinee> GetTopHighestLiterature(vector<Examinee> list_examinee, int k)
{
    vector <Examinee> res;
    QuickSort(list_examinee, 0, list_examinee.size() - 1);
    
    for (int i = 0; i < k; i++)
    {
        res.push_back(list_examinee[i]);
    }
    return res;
}

// Q2.2
vector <Examinee> MergeTwoList(vector<Examinee> list1, vector<Examinee> list2)
{
    vector <Examinee> res;
    
    int n1 = list1.size();
    int left1 = 0;
    
    int n2 = list2.size();
    int left2 = 0;
    
    float L[n1], R[n2];
 
    for (int i = 0; i < n1; i++)
        L[i] = list1[left1 + i].literature;
    for (int j = 0; j < n2; j++)
        R[j] = list2[left2 + j].literature;
 
    int i = 0, j = 0;
 
    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
        {
            res.push_back(list1[i]);
            i++;
        }
        else
        {
            res.push_back(list2[j]);;
            j++;
        }
    }
 
    while (i < n1)
    {
        res.push_back(list1[i]);
        i++;
    }
 
    while (j < n2)
    {
        res.push_back(list2[j]);
        j++;
    }
    return res;
}

int main()
{
//Đọc file
    
    vector <Examinee> examinee_list;
    examinee_list = ReadExamineeList("data1.txt");
//    outputList(examinee_list);

//Q1
    
//    vector <Examinee> sorted_list;
//    sorted_list = ReadExamineeList("descending_Literature.txt");
//    string findExamineebyLiterature = FindExamineeByLiterature(sorted_list, 9.0);
//    cout << findExamineebyLiterature << endl;
    
//Q2.1
    
//    vector <Examinee> TopLiterature;
//    TopLiterature = GetTopHighestLiterature(ReadExamineeList("data.txt"), 10);
//    outputList(TopLiterature);
  
    
//Q2.2

    vector <Examinee> Merge = MergeTwoList(ReadExamineeList("Lyn1.txt"), ReadExamineeList("Lyn2.txt"));
    outputList(Merge);
    
    return 0;
}
