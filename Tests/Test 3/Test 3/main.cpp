#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct NODE
{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

int height(NODE* p_root)
{
    if (p_root == NULL)
        return 0;
    return p_root->height;
}

int getBalance(NODE *pRoot)
{
    if (pRoot == NULL)
        return 0;
    return height(pRoot->p_left) - height(pRoot->p_right);
}

NODE *rightRotate(NODE *y)
{
    NODE *x  = y->p_left;
    NODE *T2 = x->p_right;
  
    x->p_right = y;
    y->p_left  = T2;
  
    y->height = max(height(y->p_left), height(y->p_right)) + 1;
    x->height = max(height(x->p_left), height(x->p_right)) + 1;
  
    return x;   // Return new root
}

NODE *leftRotate(NODE *x)
{
    NODE *y = x->p_right;
    NODE *T2 = y->p_left;
  
    y->p_left = x;
    x->p_right = T2;
  
    x->height = max(height(x->p_left), height(x->p_right)) + 1;
    y->height = max(height(y->p_left), height(y->p_right)) + 1;
  
    return y;   // Return new root
}

NODE* createNode(int data)
{
    NODE *p = new NODE;
    p->key = data;
    p->p_left = NULL;
    p->p_right = NULL;
    p->height = 1;
    return p;
}

void Insert(NODE* &pRoot, int x)
{
    if (pRoot == NULL)  pRoot = createNode(x);
      
    if (x < pRoot->key)         { Insert(pRoot->p_left, x); }
    else if (x > pRoot->key)    { Insert(pRoot->p_right, x); }
    else return;
      
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
      
    int balance = getBalance(pRoot);
      
    if (balance > 1 && x < pRoot->p_left->key)
        pRoot = rightRotate(pRoot);
      
    if (balance < -1 && x > pRoot->p_right->key)
        pRoot = leftRotate(pRoot);
      
    if (balance > 1 && x > pRoot->p_left->key)
    {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
      
    if (balance < -1 && x < pRoot->p_right->key)
    {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

void doSth1 (NODE*&root, ifstream &fi)
{
    string line1;   getline(fi, line1);
    
    string line2;   getline(fi, line2);
    stringstream ss(line2);

    int k;
    while (ss >> k)
    {
        Insert(root, k);
    }
}

void LRN (NODE*&root)
{
    if(root != NULL)
    {
        LRN(root->p_left);
        LRN(root->p_right);
        cout << root->key << " ";
    }
}

int takeA (ifstream &fi)
{
    string line1;   getline(fi, line1);
    string line2;   getline(fi, line2);
    
    string line3;   getline(fi, line3);
    stringstream ss(line3);
    
    int A; ss >> A;
    return A;
}

int sumNode(NODE* pRoot)
{
    if (pRoot == NULL)  return 0;
    int sum = pRoot->key;
    return sum + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

void doSth2 (NODE *&root, int A)
{
    if (root == NULL)   return;
    doSth2(root->p_right, A);
    
    if ((sumNode(root) - (root->key)) < A)
    {
        cout << root->key << " ";
    }
    
    doSth2(root->p_left, A);
}

//NODE * minValueNode(NODE* pRoot)
//{
//    NODE *p = pRoot;
//    while (p->p_left != NULL)
//    {
//        p = p->p_left;
//    }
//    return p;
//}

NODE * maxValueNode(NODE* pRoot)
{
    NODE *p = pRoot;
    while (p->p_right != NULL)
    {
        p = p->p_right;
    }
    return p;
}

void Remove(NODE* &pRoot, int key)
{
    if (pRoot == NULL)   return;
  
    if (key < pRoot->key)           Remove(pRoot->p_left, key);
  
    else if (key > pRoot->key)      Remove(pRoot->p_right, key);
  
    else
    {
        if((pRoot->p_left == NULL) || (pRoot->p_right == NULL))
        {
            NODE *temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
  
            if (temp == NULL)
            {
                temp = pRoot;
                pRoot = NULL;
            }
            else { *pRoot = *temp; }
            delete temp;
        }
        else
        {
            NODE* temp = maxValueNode(pRoot->p_left);
            pRoot->key = temp->key;             //Copy the inorder predecessor's data to this node
            Remove(pRoot->p_left, temp->key);  //Delete the inorder predecessor
        }
    }
    if (pRoot == NULL)   return;
  
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
  
    int balance = getBalance(pRoot);
  
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
    {
        pRoot = rightRotate(pRoot);
    }
  
    if (balance > 1 && getBalance(pRoot->p_left) < 0)
    {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
  
    if (balance < -1 && getBalance(pRoot->p_right) <= 0)
    {
        pRoot = leftRotate(pRoot);
    }
  
    if (balance < -1 && getBalance(pRoot->p_right) > 0)
    {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

NODE *FindNode (NODE *&root)
{
    if (root == NULL)   { return NULL; }
    
    NODE *temp = FindNode(root->p_right);
    if (temp != NULL)   { return temp; }
    
    if ((root->p_right != NULL) && (root->p_left != NULL) && (root->p_right->key) % (root->p_left->key) == 0)    { return root; }
    
    return FindNode(root->p_left);
}

int main()
{
    NODE *Tree = NULL;
    
    ifstream fi;    fi.open("input.txt");
    doSth1(Tree, fi);
    LRN(Tree);
    fi.close();
    
    cout << endl;
    
    ifstream fin;    fin.open("input.txt");
    doSth2(Tree, takeA(fin));
    fin.close();
    
    cout << endl;

    NODE *temp = FindNode(Tree);
    Remove(temp, temp->key);
    LRN(Tree);

    cout << endl;
    return 0;
}
