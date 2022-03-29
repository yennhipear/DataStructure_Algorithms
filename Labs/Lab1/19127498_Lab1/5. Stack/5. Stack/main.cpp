#include <iostream>
using namespace std;

struct NODE
{
    int key;
    NODE *pNext;
};

struct Stack
{
    NODE *pHead;
    NODE *pTail;
};

NODE* createNode(int data)
{
    NODE *p = new NODE;
    p->key = data;
    p->pNext = NULL;
    return p;
}

void Initializer (Stack &S)
{
    S.pHead = S.pTail = NULL;
}

void Push (Stack &S, int data)
{
    NODE *p = createNode(data);
    if (S.pHead == NULL)    {S.pHead = p; S.pTail = p;}
    else
    {
        S.pTail->pNext = p;
        S.pTail = p;
    }
}

void Pop (Stack &S)
{
    if (S.pHead == NULL)    return;
    if (S.pHead->pNext == NULL) S.pHead = NULL;
    else {
    NODE *cur = S.pHead;
    while (cur->pNext->pNext != NULL)
    {
        cur = cur->pNext;
    }
    cur->pNext = NULL;
    }
}

int countElements(Stack &S)
{
    NODE *cur = S.pHead;
    int count = 0;
    while (cur != NULL)
    {
        count++;
        cur = cur->pNext;
    }
    return count;
}

bool isEmptyStack (Stack &S)
{
    if (S.pHead == NULL)    return true;
    return false;
}

void printStack (Stack &S)
{
    NODE *cur = S.pHead;
    while (cur != NULL)
    {
        cout << cur->key << " ";
        cur = cur->pNext;
    }
    cout << endl;
}

int main()
{
    Stack S;    Initializer(S);
    
    int size;
    cout << "Enter size of Stack: ";    cin >> size;
    
    int k;
    for (int i = 0; i < size; i++)
    {
        cin >> k;
        Push(S, k);
    }
    cout << "--> "; printStack(S);
    
    cout << "Number of elements in stack: " << countElements(S) << endl;

    Pop(S);
    cout << "Stack is poped: ";  printStack(S);
    
    return 0;
}
