#include <iostream>
using namespace std;

struct d_NODE
{
    int key;
    d_NODE* pNext;
    d_NODE* pPrev;
};

struct d_List
{
     d_NODE* pHead;
     d_NODE* pTail;
 };

d_NODE *CreateNode (int data)
{
    d_NODE *p = new d_NODE;
    p->key = data;
    p->pNext = NULL;
    p->pPrev = NULL;
    return p;
}

//1. Initialize a list from a given integer.
d_List *CreateList (int data)
{
    d_NODE *node = CreateNode(data);
    d_List *myList = new d_List;
    myList->pHead = myList->pTail = node;
    return myList;
}

//2. Add a node at the front of a given List.
void addHead (d_List *L, d_NODE *p)
{
    if (L->pHead == NULL)   L->pHead = L->pTail = p;
    else
    {
        p->pNext = L->pHead;
        L->pHead->pPrev = p;
        L->pHead = p;
    }
}

//3. Add a node before a given node.
void addBefore (d_List *L, d_NODE *p, int data)
{
    d_NODE *node = CreateNode(data);
    d_NODE *p1 = p->pPrev;
    
    node->pNext = p;
    node->pPrev = p1;
    p1->pNext = node;
    p->pPrev = node;
}

//4. Add a node after a given node.
void addAfter (d_List *L, d_NODE *p, int data)
{
    d_NODE *node = CreateNode(data);
    d_NODE *p1 = p->pNext;
    
    node->pNext = p1;
    node->pPrev = p;
    p->pNext = node;
    p1->pPrev = node;
}

//5. Add a node at the end of a given List.
void addTail (d_List *L, d_NODE *p)
{
    if(L->pHead == NULL)    L->pHead = L->pTail = p;
    else
    {
        p->pPrev = L->pTail;
        L->pTail->pNext = p;
        L->pTail = p;
    }
}

//6. Remove a node at the front of a given List.
void deleteHead (d_List *L)
{
    if (L->pHead == NULL)   return;
    if (L->pHead->pNext == NULL)    {   L->pHead = NULL;   }
    
    d_NODE *p = L->pHead;
    d_NODE *cur = p->pNext;
    
    L->pHead = cur;
    cur->pPrev = NULL;
    delete p;
}

//7. Remove a node at the end of a given List.
void deleteTail (d_List *L)
{
    if (L->pHead == NULL)   return;
    if (L->pHead->pNext == NULL)    {  L->pHead = NULL;  }
    
    d_NODE *p = L->pTail;
    d_NODE *cur = p->pPrev;
    
    L->pTail = cur;
    cur->pNext = NULL;
    delete p;
}

//8. Remove the first node with given value.
void RemoveNode_withkey (d_List *L, int data)
{
    while (L->pHead->key == data)
    {
        deleteHead(L);  break;
//        if (L->pHead == NULL)   break;
    }
    d_NODE *cur = L->pHead;
    while (true)
    {
        if (cur->pNext->key == data)
        {
            d_NODE *p = cur->pNext;
            cur->pNext = p->pNext;
            p->pNext->pPrev = cur;
            delete p;
            break;
        }
        else  cur = cur->pNext;
    }
}

void inputDList (d_List *L, int n)
{
    int k;
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        d_NODE *p = CreateNode(k);
        addTail(L, p);
    }
}

void outputDList (d_List *L)
{
    d_NODE *cur = L->pHead;
    while (cur != NULL)
    {
       cout << cur->key << " ";
       cur = cur->pNext;
    }
}

int main()
{
    d_List *L = new d_List;
    L->pHead = L->pTail = NULL;
    
    int size;
    cout << "Enter size: ";     cin >> size;
    cout << "Enter values: ";   inputDList(L, size);
    cout << "Doubly Linked List --> ";     outputDList(L);     cout << endl;
    
    d_NODE *p = CreateNode(9);
    addHead(L, p);
    cout << "- Add head --> ";     outputDList(L);     cout << endl;
    
    d_NODE *p1 = CreateNode(10);
    addTail(L, p1);
    cout << "- Add tail --> ";     outputDList(L);     cout << endl;

    addBefore(L, p1, 7);
    cout << "- Add before --> ";     outputDList(L);     cout << endl;

    addAfter(L, p, 12);
    cout << "- Add after --> ";     outputDList(L);     cout << endl;
    
//    deleteHead(L);
//    cout << "- Delete head --> ";     outputDList(L);     cout << endl;
//
//    deleteTail(L);
//    cout << "- Delete tail --> ";     outputDList(L);     cout << endl;
    
    RemoveNode_withkey(L, 5);
    cout << "- Delete first 5 --> ";     outputDList(L);     cout << endl;
    
    cout << endl;
    return 0;
}
