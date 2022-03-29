#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <queue>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node *CreateNode (int data)
{
    Node *p = new Node;
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void addNode (Node *&pRoot, int x)
{
    Node *p = CreateNode(x);
    if (pRoot)
    {
        if (x > pRoot->data)        { addNode(pRoot->right, x); }
        else if (x < pRoot->data)   { addNode(pRoot->left, x); }
        else return;
    }
    else
    {
        pRoot = p;
    }
}

void inputTreeFromFile (Node *&pRoot, ifstream &fi)
{
    string line;    getline(fi, line);
    stringstream ss (line);
    
    int x;
    while (ss >> x)
    {
        addNode (pRoot, x);
    }
}

void printTree_NLR (Node *&pRoot)
{
    if (pRoot)
    {
        cout << pRoot->data << " ";
        printTree_NLR(pRoot->left);
        printTree_NLR(pRoot->right);
    }
}

bool isDivisor (int a, int b)
{
    if (b % a == 0) return 1;
    else return 0;
}

void doSth2 (Node *pRoot)
{
    if (pRoot == NULL)  return;
    
    doSth2(pRoot->left);
    
    if (pRoot->left != NULL && pRoot->right != NULL && isDivisor(pRoot->left->data, pRoot->right->data))
        cout << pRoot->data << " ";
    
    doSth2(pRoot->right);
}

//void doSth2 (Node *pRoot)
//{
//    if (pRoot == NULL)  return;
//    else
//    {
//        if (pRoot->left != NULL && pRoot->right != NULL && isDivisor(pRoot->left->data, pRoot->right->data))
//        {
//            cout << pRoot->data << " ";
//        }
//        doSth2(pRoot->left);
//        doSth2(pRoot->right);
//    }
//}

Node *FindMinValue (Node *pRoot)
{
    while (pRoot->left != NULL)
        pRoot = pRoot->left;
    return pRoot;
}

void Remove(Node* &pRoot, int x)
{
    if (pRoot == NULL)  return;
    else if (x < pRoot->data)    Remove(pRoot->left, x);
    else if (x > pRoot->data)    Remove(pRoot->right, x);
    else
    {
        // Case 1: No child
        if (pRoot->left == NULL && pRoot->right == NULL)    { delete pRoot; pRoot = NULL;}
        
        // Case 2: 1 child
        else if (pRoot->left == NULL)
        {
            Node *temp = pRoot;
            pRoot = pRoot->right;
            delete temp;
        }
        else if (pRoot->right == NULL)
        {
            Node *temp = pRoot;
            pRoot = pRoot->left;
            delete temp;
        }
        
        // Case 3: 2 children, find successor
        else
        {
            Node *temp = FindMinValue(pRoot->right);
            pRoot->data = temp->data;
            Remove(pRoot->right, temp->data);
        }
    }
}

Node *nodeToDelete (Node *pRoot)
{
    if (pRoot == NULL)  { return NULL; }
    
    Node *temp = nodeToDelete(pRoot->right);
    if (temp != NULL)   return temp;
    if ((pRoot->right != NULL) && (pRoot->left != NULL) && (pRoot->data % pRoot->left->data == 0))
    {
        return pRoot;
    }
    return nodeToDelete(pRoot->left);
}

void LevelOrder(Node* pRoot)
{
    if (pRoot == NULL)  return;
    queue <Node*> Q;
    Q.push(pRoot);
    
    while (!Q.empty())
    {
        Node *cur = Q.front();
        cout << cur->data << " ";
        if (cur->left != NULL)     Q.push(cur->left);
        if (cur->right != NULL)    Q.push(cur->right);
        Q.pop();    // Remove the element at front
    }
}

int main()
{
    Node *Tree = NULL;
    
    ifstream fin;
    fin.open("input.txt");
    if (!fin.is_open())
    {
        cout << "Not OK " << endl;
    }
    else
    {
        inputTreeFromFile(Tree, fin);
        printTree_NLR(Tree);
    }
    
    fin.close();
    cout << endl;
    
    doSth2(Tree);   cout << endl;
    
    Node *p = nodeToDelete(Tree);
    Remove(p, p->data);
    
    LevelOrder(Tree);

    cout << endl;
    return 0;
}

