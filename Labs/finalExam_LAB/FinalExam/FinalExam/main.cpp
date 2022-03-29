#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct NODE
{
    string ID;
    float math, literature, forein_language;
    NODE *pLeft;
    NODE *pRight;
};

float AverageScore (NODE *root)
{
    return ((root->math + root->literature + root->forein_language)/3);
}

NODE* createNode(string id, float math, float liter, float fl)
{
    NODE *p = new NODE;
    
    p->ID               = id;
    p->math             = math;
    p->literature       = liter;
    p->forein_language  = fl;
    
    p->pLeft   = NULL;
    p->pRight  = NULL;
    
    return p;
}

NODE *takeInfo (string line_info)
{
    stringstream ss (line_info);
    NODE *Stu = new NODE;
    string temp;
    
    getline(ss, Stu->ID, ',');
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        Stu->math = stof(temp);
    }
    else Stu->math = 0;
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        Stu->literature = stof(temp);
    }
    else Stu->literature = 0;
    
    getline (ss, temp, ',');
    if (temp != "")
    {
        Stu->forein_language = stof(temp);
    }
    else Stu->forein_language = 0;

    return Stu;
}

void Insert(NODE* &pRoot, NODE *&p)
{
    if (pRoot != NULL)
    {
        if (AverageScore(p) < AverageScore(pRoot))         Insert(pRoot->pLeft, p);
        else Insert(pRoot->pRight, p);
//        else  (AverageScore(p) >= AverageScore(pRoot))
    }
    else
    {
        pRoot = p;
    }
}

void inputTreeFromFile (NODE *&root, string file_name)
{
    ifstream fi;    fi.open(file_name);
    string line_info;   getline(fi, line_info);
    
    while (getline(fi, line_info))
    {
        NODE *temp = takeInfo(line_info);
        Insert(root, temp);
    }
    fi.close();
}

void DisplayIDs(NODE *pRoot)
{
    if (pRoot != NULL)
    {
        DisplayIDs(pRoot->pLeft);
        cout << pRoot->ID << " " << AverageScore(pRoot) << endl;
        DisplayIDs(pRoot->pRight);
    }
}

int Height(NODE *&pRoot)
{
    if (pRoot == NULL)
        return -1;
    
    int leftHeight = Height(pRoot->pLeft);
    int rightHeight = Height (pRoot->pRight);
    
    return max(leftHeight, rightHeight) + 1;
}

void LevelOrder(NODE *pRoot)
{
    if (pRoot == NULL)  { return; }
    queue <NODE*> Q;
    Q.push(pRoot);

    while (!Q.empty())
    {
        NODE *cur = Q.front();
        cout << cur->ID << " " << AverageScore(cur) << endl;
        if (cur->pLeft != NULL)     Q.push(cur->pLeft);
        if (cur->pRight != NULL)    Q.push(cur->pRight);
        Q.pop();
    }
}

void FindStudentEqual (NODE *pRoot, vector <string> &ans, float s)
{
    if (pRoot == NULL)  return;
    if (AverageScore(pRoot) == s)   { ans.push_back(pRoot->ID); }
    
    FindStudentEqual (pRoot->pLeft, ans, s);
    FindStudentEqual (pRoot->pRight, ans, s);
}

vector <string> SearchEqual (NODE *&pRoot, float s)
{
    vector <string> ans;
    FindStudentEqual(pRoot, ans, s);
    return ans;
}

void FindStudentGreater (NODE *pRoot, vector <string> &ans, float s)
{
    if (pRoot == NULL)  return;
    if (AverageScore(pRoot) >= s)   { ans.push_back(pRoot->ID); }
    
    FindStudentGreater (pRoot->pLeft, ans, s);
    FindStudentGreater (pRoot->pRight, ans, s);
}

vector <string> SearchGreater(NODE *&pRoot, float s)
{
    vector <string> ans;
    FindStudentGreater (pRoot, ans, s);
    return ans;
}

int main()
{
    NODE *Tree = NULL;
    
    cout << "1. ID tang dan theo diem trung binh. " << endl;
    
    inputTreeFromFile(Tree, "data1.txt");
//    LevelOrder(Tree);
    DisplayIDs(Tree);

    cout << endl;
    
    cout << "2. Chieu cao cay nhi phan: " << Height(Tree) << endl;
    cout << "3. Danh sach hoc sinh co diem trung binh la 4.5 " << endl;
    vector <string> id_list = SearchEqual(Tree, 4.5);
    for (int i = 0; i < id_list.size(); i++)
    {
        cout << id_list[i] << endl;
    }
    cout << endl;
    
    cout << "4. Danh sach hoc sinh co diem trung binh lon hon 4.9 " << endl;
    vector <string> id_list1 = SearchGreater(Tree, 4.9);
    for (int i = 0; i < id_list1.size(); i++)
    {
        cout << id_list1[i] << endl;
    }
    cout << endl;
    
    return 0;
}
