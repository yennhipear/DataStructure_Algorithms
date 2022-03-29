#include <iostream>
using namespace std;

struct NODE
{
    int key;
    NODE *p_next;
};

struct List
{
    NODE *p_head;
    NODE *p_tail;
};

//1. Initialize a NODE from a given integer
NODE* createNode(int data)
{
    NODE *p = new NODE;
    p->key = data;
    p->p_next = NULL;
    return p;
}

//2. Initialize a List from a give NODE
List* createList(NODE* p_node)
{
    List *L = new List;
    L->p_head = L->p_tail = p_node;
    return L;
}

//3. Insert an integer to the head of a given List
void addHead(List* &L, int data)
{
    NODE *p = createNode(data);
    if (L->p_head == NULL)  L->p_head = p;
    else
    {
        p->p_next = L->p_head;
        L->p_head = p;
    }
}

//4. Insert an integer to the tail of a given List
void addTail(List* &L, int data)
{
    NODE *p = createNode(data);
    if (L->p_head == NULL)  L->p_head = L->p_tail = p;
    else
    {
        L->p_tail->p_next = p;
        L->p_tail = p;
    }
}

//5. Remove the first NODE of a given List
void removeHead(List* &L)
{
    if (L->p_head == NULL)  return;
    if (L->p_head->p_next == NULL)   L->p_head = NULL;
    else
    {
        NODE *cur = L->p_head;
        L->p_head = L->p_head->p_next;
        delete cur;
    }
}

//6. Remove the last NODE of a given List
void removeTail(List* &L)
{
    if (L->p_head == NULL)  return;
    if (L->p_head->p_next == NULL)   L->p_head = NULL;
    else
    {
        NODE *cur = L->p_head;
        while (cur->p_next->p_next != NULL)
        {
            cur = cur->p_next;
        }
        cur->p_next = NULL;
    }
}

//7. Remove all NODE from a given List
void removeAll(List* &L)
{
    while (L->p_head != NULL)
    {
        removeHead(L);
    }
}

//8. Print all elements of a given List
void printList(List* L)
{
    NODE *cur = L->p_head;
    while (cur != NULL)
    {
        cout << cur->key << " ";
        cur = cur->p_next;
    }
}

//9. Count the number of elements List
int countElements(List* L)
{
    NODE *cur = L->p_head;
    int count = 0;
    while (cur != NULL)
    {
        count++;
        cur = cur->p_next;
    }
    return count;
}

//10. Create a new List by reverse a given List
List* reverseList(List* L)
{
    List *L1 = new List;
    L1->p_head = L1->p_tail = NULL;
    
    NODE *cur = L->p_head;
    while (cur != NULL)
    {
        addHead(L1, cur->key);
        cur = cur->p_next;
    }
    return L1;
}

//11. Remove all duplicates from a given List
void RemoveDuplicate(List* &L)
{
    NODE *cur = L->p_head;
    while (cur->p_next != NULL)
    {
        if (cur->key == cur->p_next->key)
        {
            NODE *p = cur->p_next;
            cur->p_next = p->p_next;
            delete p;
        }
        else cur = cur->p_next;
    }
}

//12. Remove all key value from a given List
void RemoveElement(List* &L, int key)
{
    while (L->p_head->key == key)
    {
        removeHead(L);
        if (L->p_head == NULL) break;
    }
    NODE *cur = L->p_head;
    while (cur->p_next != NULL)
    {
        if (cur->p_next->key == key)
        {
            NODE *p = cur->p_next;
            cur->p_next = p->p_next;
            delete p;
        }
        else
        {
            cur = cur->p_next;
        }
    }
}

int main()
{
    cout << "\t\t\t *****    LINKED LIST    ***** \n" << endl;
    List *myList = new List;
    myList->p_head = myList->p_tail = NULL;
    
    int size, value;
    cout << "Enter size: ";     cin >> size;
    cout << "Enter value of nodes: ";
    for (int i = 0; i < size; i++)
    {
        cin >> value;
        addTail(myList, value);
    }
        
    int choice;
    cout << endl;
    cout << "1. Print all elements of a given list " << endl;
    cout << "2. Insert an integer to the head " << endl;
    cout << "3. Insert an integer to the tail " << endl;
    cout << "4. Remove the first NODE of list " << endl;
    cout << "5. Remove the last NODE of list " << endl;
    cout << "6. Remove all NODE from list " << endl;
    cout << "7. Count the number of elements list " << endl;
    cout << "8. Create a new List by reverse a given list " << endl;
    cout << "9. Remove all duplicates from list " << endl;
    cout << "10. Remove all key value from list " << endl;

    do
    {
        cout << endl;
        cout << "--> Enter choice: ";   cin >> choice;
        switch (choice)
        {
            case 1:
            {
                cout << "1. Print all elements of a given list " << endl;
                cout << "--> "; printList(myList); cout << endl;
                break;
            }
            
            case 2:
            {
                cout << "2. Insert an integer to the head " << endl;
                cout << "- Enter value: ";
                int k;  cin >> k;
                addHead(myList, k);
                cout << "--> "; printList(myList); cout << endl;
                break;
            }

            case 3:
            {
                cout << "3. Insert an integer to the tail " << endl;
                cout << "- Enter value: ";
                int h;  cin >> h;
                addTail(myList, h);
                cout << "--> "; printList(myList); cout << endl;
                break;
            }
                
            case 4:
            {
                cout << "4. Remove the first NODE of list " << endl;
                removeHead(myList);
                cout << "- Remove head: "; printList(myList); cout << endl;
                break;
            }
                
            case 5:
            {
                cout << "5. Remove the last NODE of list " << endl;
                removeTail(myList);
                cout << "- Remove tail: "; printList(myList); cout << endl;
                break;
            }
                
            case 6:
            {
                cout << "6. Remove all NODE from list " << endl;
                removeAll(myList);
                cout << "- Remove all: "; printList(myList); cout << endl;
                break;
            }
             
            case 7:
            {
                cout << "7. Count the number of elements list " << endl;
                cout << "- Number of elements list: " << countElements(myList) << endl;
                break;
            }
                
            case 8:
            {
                cout << "8. Create a new List by reverse a given list " << endl;
                List *tempList = reverseList(myList);
                cout << "--> "; printList(tempList); cout << endl;
                break;
            }
                
            case 9:
            {
                cout << "9. Remove all duplicates from list " << endl;
                RemoveDuplicate(myList);
                cout << "--> "; printList(myList); cout << endl;
                break;
            }
                
            case 10:
            {
                cout << "10. Remove all key value from list " << endl;
                int key_toDelete;
                cout << "Enter key to delete: ";    cin >> key_toDelete;
                RemoveElement(myList, key_toDelete);
                cout << "--> "; printList(myList); cout << endl;
                break;
            }

            default:
            {
                cout << "Please enter your choice again! " << endl;
                break;
            }
        }
    }
    while (choice != 0);
    
    cout << endl << endl;
    return 0;
}
