#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

struct NODE
{
    int key;
    NODE* p_left;
    NODE* p_right;
};

//1. Initialize a NODE from a given value:
NODE* createNode(int data)
{
    NODE *p = new NODE;
    p->key      = data;
    p->p_left   = NULL;
    p->p_right  = NULL;
    return p;
}

//2. Pre-order Traversal:
void NLR(NODE* pRoot)
{
    if (pRoot != NULL)
    {
        cout << pRoot->key << " ";
        NLR(pRoot->p_left);
        NLR(pRoot->p_right);
    }
}

//3. In-order Traversal:
void LNR(NODE* pRoot)
{
    if (pRoot != NULL)
    {
        NLR(pRoot->p_left);
        cout << pRoot->key << " ";
        NLR(pRoot->p_right);
    }
}

//4. Post-order Traversal:
void LRN(NODE* pRoot)
{
    if (pRoot != NULL)
    {
        NLR(pRoot->p_left);
        NLR(pRoot->p_right);
        cout << pRoot->key << " ";
    }
}

//5. Level-order Traversal:
void LevelOrder(NODE* pRoot)
{
    if (pRoot == NULL)  return;
    queue <NODE*> Q;
    Q.push(pRoot);
    
    while (!Q.empty())
    {
        NODE *cur = Q.front();
        cout << cur->key << " ";
        if (cur->p_left != NULL)     Q.push(cur->p_left);
        if (cur->p_right != NULL)    Q.push(cur->p_right);
        Q.pop();    // Remove the element at front
    }
}

//6. Find and return a NODE with given value from a given Binary Search Tree:
NODE* Search(NODE* pRoot, int x)
{
    if (pRoot == NULL)         { return NULL; }
    if (pRoot->key == x)       { return pRoot;}
    else if (x < pRoot->key)   { return Search(pRoot->p_left, x); }
    else return Search(pRoot->p_right, x);
}

//7. Add a NODE with given value into a given Binary Search Tree:
void Insert(NODE* &pRoot, int x)
{
    if (pRoot != NULL)
    {
        if (x < pRoot->key)         Insert(pRoot->p_left, x);
        else if (x > pRoot->key)    Insert(pRoot->p_right, x);
        else return;
    }
    else
    {
        NODE *p = createNode(x);
        pRoot = p;
    }
}

//8. Remove a NODE with given value from a given Binary Search Tree:
NODE *FindMinValue (NODE *pRoot)
{
    while (pRoot->p_left != NULL)
        pRoot = pRoot->p_left;
    return pRoot;
}

void Remove(NODE* &pRoot, int x)
{
    if (pRoot == NULL)  return;
    else if (x < pRoot->key)    Remove(pRoot->p_left, x);
    else if (x > pRoot->key)    Remove(pRoot->p_right, x);
    else
    {
        // Case 1: No child
        if (pRoot->p_left == NULL && pRoot->p_right == NULL)    { delete pRoot; pRoot = NULL;}
        
        // Case 2: 1 child
        else if (pRoot->p_left == NULL)
        {
            NODE *temp = pRoot;
            pRoot = pRoot->p_right;
            delete temp;
        }
        else if (pRoot->p_right == NULL)
        {
            NODE *temp = pRoot;
            pRoot = pRoot->p_left;
            delete temp;
        }
        
        // Case 3: 2 children, find successor
        else
        {
            NODE *temp = FindMinValue(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
}

//9. ***** Initialize a Binary Search Tree from a given array:
NODE* createTree(int a[]);

//10. Completely remove a given Binary Search Tree:
void removeTree(NODE* &pRoot)
{
    if (pRoot == NULL)  return;
    
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    
    delete pRoot;
    pRoot = NULL;
}

//11. Calculate the height of a given Binary Tree;
int Height(NODE* pRoot)
{
    if (pRoot == NULL)
        return -1;
    
    int leftHeight = Height(pRoot->p_left);
    int rightHeight = Height (pRoot->p_right);
    
    return max(leftHeight, rightHeight) + 1;
}

//12. Count the number of NODE from a given Binary Tree:
int countNode(NODE* pRoot)
{
    if (pRoot == NULL)  return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

//13. ***** Calculate the total value of all NODEs from a given Binary Tree:
int sumNode(NODE* pRoot)
{
    if (pRoot == NULL)  return 0;
    int sum = pRoot->key;
    return sum + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

//14. ***** Calculate the height of a NODE with given value: (return -1 if value not exist)
double heightNode(NODE* pRoot, int value)
{
    NODE *p = Search(pRoot, value);
    return Height(p);
}

//15. * Calculate the level of a given NODE:
int Level(NODE* pRoot, NODE* p)
{
    if (pRoot->key == p->key)
    {
        return 0;
    }
    if (p->key < pRoot->key)
        return 1 + Level(pRoot->p_left, p);
    else return 1 + Level (pRoot->p_right, p);
}

//16. * Count the number leaves from a given Binary Tree:
int countLeaf(NODE* pRoot)
{
    if (pRoot == NULL)  { return 0; }
    if (pRoot->p_left == NULL && pRoot->p_right == NULL)    { return 1; }
    else return (countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right));
}

//17. * Count the number of NODE from a given Binary Search Tree which key value is less than a given value:
int countLess(NODE* pRoot, int x)
{
    int ans;
    if (pRoot == NULL)      { return 0; }
    if (x > pRoot->key)
    {
        ans = 1 + countNode(pRoot->p_left) + countLess(pRoot->p_right, x);
    }
    else { ans = countLess(pRoot->p_left, x); }
    return ans;
}

//18. * Count the number of NODE from a given Binary Search Tree which key value is greater than a given value:
int countGreater(NODE* pRoot, int x)
{
    int ans;
    if (pRoot == NULL)  { return 0; }
    if (x < pRoot->key)
    {
        ans = 1 + countNode(pRoot->p_right) + countGreater(pRoot->p_left, x);
    }
    else { ans = countGreater(pRoot->p_right, x); }
    return ans;
}

//19. * Determine if a given Binary Tree is Binary Search Tree:
int isBSTUtil(NODE* pRoot, int min, int max)
{
    if (pRoot == NULL)   { return 1; }
   
    if (pRoot->key > min && pRoot->key < max && isBSTUtil(pRoot->p_left, min, pRoot->key) && isBSTUtil(pRoot->p_right, pRoot->key, max))
        return true;
    
    else return false;
}

bool isBST(NODE* pRoot)
{
    return(isBSTUtil(pRoot, INT_MIN, INT_MAX));
}

//20. ***** * Determine if a given Binary Tree is a Full Binary Search Tree:
bool isFullBST(NODE* pRoot)
{
    if (pRoot == NULL)  return true;
    if (pRoot->p_left == NULL && pRoot->p_right == NULL)    return true;
    if (pRoot->p_left && pRoot->p_right)
        return (isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right));
    return false;
}

int main()
{
    cout << "\t\t\t *** WELCOME TO BINARY SEARCH TREE *** \n\n";
    NODE *Tree = NULL;
    
    int numberOfNode, value;
    cout << " - Enter the number of nodes: ";    cin >> numberOfNode;
    cout << " - Enter value of nodes: ";
    for (int i = 0; i < numberOfNode; i++)
    {
        cin >> value;
        Insert(Tree, value);
    }
    
    cout << "--> 2. Pre-order Traversal: ";    NLR(Tree);          cout << endl;
    
    cout << "--> 3. In-order Traversal: ";     LNR(Tree);          cout << endl;
    
    cout << "--> 4. Post-order Traversal: ";   LRN(Tree);          cout << endl;
    
    cout << "--> 5. Level-order Traversal: "; LevelOrder(Tree);    cout << endl;
    
    cout << "--> 6. Find a node with given value. " << endl;
    cout << "Enter key you wanna search ";  int key;    cin >> key;
    cout << "Address of that node: " << Search(Tree, key) << endl;
    
//    cout << "--> 8. Remove a NODE with given value "; Remove(Tree, 4);
//    LevelOrder(Tree);   cout << endl;
    
//    cout << "--> 10. Remove Tree: ";    removeTree(Tree);   cout << endl;
    
    cout << "--> 11. Height of a given Binary Tree: " << Height(Tree) << endl;
    
    cout << "--> 12. Count the number of nodes: " << countNode(Tree) << endl;
    
    cout << "--> 13. Calculate the total value of all nodes: " << sumNode(Tree) << endl;
    
    cout << "--> 14. Calculate the height of a NODE with given value: " << heightNode(Tree, 16) << endl;
    
    NODE *p = createNode(0);
    cout << "--> 15. Calculate the level of a given node: " << Level(Tree, p) << endl;
    
    cout << "--> 16. Count the number leaves: "  << countLeaf(Tree) << endl;
    
    cout << "--> 17. Count the number of NODE which key value is less than 11: " << countLess(Tree, 2) << endl;

    cout << "--> 18. Count the number of NODE which key value is greater than 5: " << countGreater(Tree, 5) << endl;

    cout << "--> 19. A given Binary Tree is Binary Search Tree? ";
    if (isBST(Tree))    cout << "YES " << endl;
    else cout << "NO " << endl;

    cout << "--> 20. A given Binary Tree is FULL Binary Search Tree? ";
    if (isFullBST(Tree))    cout << "YES " << endl;
    else cout << "NO " << endl;
    
    removeTree(Tree);   cout << endl;

    cout << endl;
    return 0;
}

//5 2 0 4 67 16 5
//5 7 -2 0 -5 1 6 -3
