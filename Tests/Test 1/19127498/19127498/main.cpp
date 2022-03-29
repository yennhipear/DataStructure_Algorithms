#include "header.h"
#include <fstream>
#include <sstream>
#include <cmath>

Animal* createAnimal (string ID, double W1, double W2)
{
    Animal *A = new Animal;
    
    A->id = ID;
    A->w1 = W1;
    A->w2 = W2;
    A->next = NULL;
    
    return A;
}

AnimalList* createAnimalList ()
{
    AnimalList *L = new AnimalList;
    L->first = L->last = NULL;
    return L;
}

int getType (string s) //0: Pig     1: Cow
{
    if (s[0] == 'P' && s[1] == 'i')     return 0;
    if (s[0] == 'C' && s[1] == 'o')     return 1;
    
    return -1;
}

Animal *takeInfo (string line_info)
{
    Animal *A = new Animal;
    stringstream ss (line_info);
    
    getline (ss, A->id, ' ');
    ss >> A->w1;
    ss >> A->w2;

    return A;
}

void addFirst (AnimalList *L, Animal *A)
{
    if (L->first == NULL)
        L->first = L->last = A;
    else
    {
        A->next = L->first;
        L->first = A;
    }
}

void addLast (AnimalList *L, Animal *A)
{
    if (L->first == NULL)
        L->first = L->last = A;
    else
    {
        L->last->next = A;
        L->last = A;
    }
}

AnimalList* read_file(string input_file)
{
    AnimalList* animals = createAnimalList();

    // HINT: uncomment the command below if you dont know how to code this function
    // animals = read_file_ref(input_file);

    // TODO: read input.txt and return linked list of animals
    
    ifstream fi;
    fi.open(input_file);
    
    if (!fi.is_open())  {return animals;}
    
    while (!fi.eof())
    {
        string line_info;
        
        getline(fi, line_info);
        if (line_info == "")    break;
        
        Animal *A = takeInfo(line_info);
        if (getType(A->id) == 0)        addFirst(animals, A);
        else if (getType(A->id) == 1)        addLast(animals, A);
        else addLast(animals, A);
    }
    return animals;
}

bool isValid (Animal *A)    // 1: hợp lệ    0: ko hợp lệ
{
    bool flag = true;
    
    string birthmonth = "";
    birthmonth += A->id[2];
    birthmonth += A->id[3];
    
    int BirthMonth = stoi(birthmonth);
    if (BirthMonth < 1 || BirthMonth > 12)    {  flag = false; }
    
    if (A->w1 <= 0 || A->w2 <= 0)     { flag = false; }
    
    if (A->id.size() < 9 || A->id.size() > 9)   { flag = false; }
    
    if (getType(A->id) == 0)
    {
        if ((A->w2 <= 50 || A->w2 >= 100) || (A->w1 <= 50 || A->w1 >= 100))  flag = false;
    }
    else if (getType(A->id) == 1)
    {
        if ((A->w2 <= 50 || A->w2 >= 200) || (A->w1 <= 50 || A->w1 >= 200))  flag = false;
    }
    else flag = false;
    
    if (flag == true)   return 1;
    else return 0;
}

void print_output(AnimalList* animals, int x)
{
    // TODO: do all other tasks and print output like output.txt
//    Animal *cur = animals->first;
//    while (cur != NULL)
//    {
//        cout << cur->id << " " << cur->w1 << " " << cur->w2 << endl;
//        cur = cur->next;
//    }
//
//    cout << "-------------------------" << endl;
//
    AnimalList *animals1 = createAnimalList();
    
    Animal *cur1 = animals->first;
    while (cur1 != NULL)
    {
        if (isValid(cur1) == 0)
        {
//           cout << cur1->id << " " << isValid(cur1) << " " << endl;
            Animal *temp = createAnimal(cur1->id, cur1->w1, cur1->w2);
            addLast(animals1, temp);
        }
        cur1 = cur1->next;
    }
    
    Animal *p = animals1->first;
    while (p != NULL)
    {
        cout << p->id << " " << p->w1 << " " << p->w2 << endl;
        p = p->next;
    }
}

void main_debug (string input_file, int x)
{
    // MAIN HERE: do whatever you want here
    AnimalList *L = read_file("input.txt");
    print_output(L, 0);
}

int main(int argc, char* argv[])
{
    string input_file; int x = 4;
//    if (argc > 2)
//    {
//        input_file = argv[1];
//        x = atoi(argv[2]);
//        if (argc > 3 && atoi(argv[3]) == 1)
//        {
//            main_testcases(input_file, x); return 0;
//        }
//    }
//    else
//    {
//        cout << "Enter input_file:"; cin >> input_file;
//         cout << "Enter x:"; cin >> x;
//    }
    main_debug(input_file, x);
    if (!system(NULL)) system("pause");
    return 0;
}

void main_testcases(string input_file, int x)
{
    AnimalList* animals = read_file(input_file);
    print_output(animals, x);
}
