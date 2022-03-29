#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Examinee
{
    string id;
    float math, literature,
        physic, chemistry, biology,
        history, geography, civic_education,
        natural_science, social_science, foreign_language;
};

//1. Read the information of one candidate
float StringtoFloat(string line_info, int& index, char stopChar = ',')
{
    string temp = "";
    while (line_info[index] != stopChar)
    {
        temp += line_info[index++];
    }
    index++;
    if (temp.size() == 0)   return 0;
    else return stof(temp);
}

Examinee readExaminee(string line_info)
{
    Examinee E;
    int index = 0;
    
    //ID
    E.id = "";
    while (line_info[index] != ',')
    {
        E.id += line_info[index++];
    }
    index++;
    
    //Name == " "
    index++;
    
    //Scores
    E.math              = StringtoFloat(line_info, index);
    E.literature        = StringtoFloat(line_info, index);
    E.physic            = StringtoFloat(line_info, index);
    E.chemistry         = StringtoFloat(line_info, index);
    E.biology           = StringtoFloat(line_info, index);
    E.history           = StringtoFloat(line_info, index);
    E.geography         = StringtoFloat(line_info, index);
    E.civic_education   = StringtoFloat(line_info, index);
    E.natural_science   = StringtoFloat(line_info, index);
    E.social_science    = StringtoFloat(line_info, index);
    E.foreign_language  = StringtoFloat(line_info, index);
    E.natural_science   = E.physic + E.chemistry + E.biology;
    E.social_science    = E.history + E.geography + E.civic_education;
    
    return E;
}

//2. Read the information of a list of candidates
vector <Examinee> readExamineeList(string file_name)
{
    ifstream fi;
    fi.open(file_name);
    
    string line_info;    getline(fi, line_info); //pass \n
    
    vector <Examinee>  res;
    while (getline(fi, line_info))
        res.push_back(readExaminee(line_info));
    
    fi.close();
    
    return res;
}

//3. Write the total score of candidates to file
void writeTotal(vector<Examinee> examinee_list, string out_file_name)
{
    ofstream fo(out_file_name);
    
    for (unsigned int i = 0; i < examinee_list.size(); i++)
    {
        fo << examinee_list[i].id << " " << examinee_list[i].math + examinee_list[i].literature + examinee_list[i].foreign_language + examinee_list[i].natural_science + examinee_list[i].social_science << endl;
    }
    
    fo.close();
}

int main()
{
    writeTotal(readExamineeList("data.txt"), "output.txt");
    return 0;
}
