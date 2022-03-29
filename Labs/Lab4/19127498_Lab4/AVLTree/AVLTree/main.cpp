#include <iostream>
#include <algorithm>
#include <queue>

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
  
    // Perform rotation
    x->p_right = y;
    y->p_left  = T2;
  
    // Update heights
    y->height = max(height(y->p_left), height(y->p_right)) + 1;
    x->height = max(height(x->p_left), height(x->p_right)) + 1;
  
    return x;   // Return new root
}

NODE *leftRotate(NODE *x)
{
    NODE *y = x->p_right;
    NODE *T2 = y->p_left;
  
    // Perform rotation
    y->p_left = x;
    x->p_right = T2;
  
    // Update heights
    x->height = max(height(x->p_left), height(x->p_right)) + 1;
    y->height = max(height(y->p_left), height(y->p_right)) + 1;
  
    return y;   // Return new root
}

//1. Initialize a NODE from a given value:
NODE* createNode(int data)
{
    NODE *p = new NODE;
    p->key = data;
    p->p_left = NULL;
    p->p_right = NULL;
    p->height = 1;
    return p;
}

//2. Add a NODE with given value into a given AVL tree (Notify if the given value existed):
void Insert(NODE* &pRoot, int x)
{
/* 1. Perform the normal BST insertion */
    if (pRoot == NULL)  pRoot = createNode(x);
      
    if (x < pRoot->key)         { Insert(pRoot->p_left, x); }
    else if (x > pRoot->key)    { Insert(pRoot->p_right, x); }
    else return;        // Equal keys are not allowed in BST
      
/* 2. Update height of this ancestor node */
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
      
/* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
    int balance = getBalance(pRoot);
    // If this node becomes unbalanced, then there are 4 cases
      
        // Left Left Case
    if (balance > 1 && x < pRoot->p_left->key)
        pRoot = rightRotate(pRoot);
      
        // Right Right Case
    if (balance < -1 && x > pRoot->p_right->key)
        pRoot = leftRotate(pRoot);
      
        // Left Right Case
    if (balance > 1 && x > pRoot->p_left->key)
    {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
      
        // Right Left Case
    if (balance < -1 && x < pRoot->p_right->key)
    {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

//3. Remove a NODE with given value from a given AVL Tree(Notify if the given value not existed):
NODE * minValueNode(NODE* pRoot)
{
    NODE *p = pRoot;
    while (p->p_left != NULL)
    {
        p = p->p_left;
    }
    return p;
}

void Remove(NODE* &pRoot, int key)
{
// STEP 1: PERFORM STANDARD BST DELETE
    if (pRoot == NULL)   return;
  
    // If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (key < pRoot->key)           Remove(pRoot->p_left, key);
  
    // If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if (key > pRoot->key)      Remove(pRoot->p_right, key);
  
    // if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if((pRoot->p_left == NULL) || (pRoot->p_right == NULL))
        {
            NODE *temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
  
            // No child case
            if (temp == NULL)
            {
                temp = pRoot;
                pRoot = NULL;
            }
            // One child case
            else { *pRoot = *temp; }    // Copy the contents of the non-empty child
            delete temp;
        }
        //Node with two children: Get the inorder successor (smallest in the right subtree)
        else
        {
            NODE* temp = minValueNode(pRoot->p_right);
            pRoot->key = temp->key;             //Copy the inorder successor's data to this node
            Remove(pRoot->p_right, temp->key);  //Delete the inorder successor
        }
    }
    // If the tree had only one node then return
    if (pRoot == NULL)   return;
  
// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
  
// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
    int balance = getBalance(pRoot);
    // If this node becomes unbalanced, then there are 4 cases
  
    // Left Left Case
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
    {
        pRoot = rightRotate(pRoot);
    }
  
    // Left Right Case
    if (balance > 1 && getBalance(pRoot->p_left) < 0)
    {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
  
    // Right Right Case
    if (balance < -1 && getBalance(pRoot->p_right) <= 0)
    {
        pRoot = leftRotate(pRoot);
    }
  
    // Right Left Case
    if (balance < -1 && getBalance(pRoot->p_right) > 0)
    {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

//4. Pre-order Traversal (key and height of NODE is required):
void NLR(NODE* pRoot)
{
    if (pRoot != NULL)
    {
        cout << pRoot->key << " ";
        NLR(pRoot->p_left);
        NLR(pRoot->p_right);
    }
}

//5. In-order Traversal (key and height of NODE is required):
void LNR(NODE* pRoot)
{
    if (pRoot != NULL)
    {
        LNR(pRoot->p_left);
        cout << pRoot->key << " ";
        LNR(pRoot->p_right);
    }
}

//6. Post-order Traversal (key and height of NODE is required):
void LRN(NODE* pRoot)
{
    if (pRoot != NULL)
    {
        LNR(pRoot->p_left);
        LNR(pRoot->p_right);
        cout << pRoot->key << " ";
    }
}

//7. Level-order Traversal (key and height of NODE is required):
void LevelOrder(NODE* pRoot)
{
    if (pRoot == NULL)  { return; }
    
    queue <NODE*> Q;
    Q.push(pRoot);
    
    while (!Q.empty())
    {
        NODE *p = Q.front();
        cout << p->key << " ";
        Q.pop();

        if (p->p_left != NULL)  { Q.push(p->p_left); }
        if (p->p_right != NULL) { Q.push(p->p_right); }
    }
}

//8. * Determine if a given Binary Tree is an AVL Tree:
bool isAVL(NODE* pRoot)
{
    if (pRoot == NULL)  { return true; }
    
    int left = height(pRoot->p_left);
    int right = height(pRoot->p_right);
    if (abs(left - right) <= 1 && isAVL(pRoot->p_left) && isAVL(pRoot->p_right))
    {
        return true;
    }
    
    return false;
}

int main()
{
    cout << "\t\t\t *** WELCOME TO AVL TREE *** \n\n";
    
    NODE *Tree = NULL;
    int numberofNodes, value;
    
    cout << "- Enter number of nodes: ";    cin >> numberofNodes;
    cout << "- Enter value of nodes: ";
    for (int i = 0; i < numberofNodes; i++)
    {
        cin >> value;
        Insert(Tree, value);
    }
    cout << "--> 7. Level-order Traversal: ";   LevelOrder(Tree);   cout << endl;
    
    cout << "--> 3. Remove a NODE with 10: ";   Remove(Tree, 10);
    LevelOrder(Tree);   cout << endl;
    
    cout << "--> 2. Add a NODE with (60, 70, 40): ";
    Insert(Tree, 60);   Insert(Tree, 70);   Insert(Tree, 40);
    LevelOrder(Tree);   cout << endl;

    cout << "--> 4. Pre-order Traversal: "; NLR(Tree);  cout << endl;
    
    cout << "--> 5. In-order Traversal: ";  LNR(Tree);  cout << endl;

    cout << "--> 6. Post-order Traversal: "; LRN(Tree); cout << endl;
    
    cout << "--> 8. Check a given Binary Tree is an AVL Tree: ";
    if (isAVL(Tree))    cout << "This is AVL tree! " << endl;
    else cout << "This is not AVL tree! " << endl;
    
    cout << endl;
    return 0;
}

//10 100 30 80 50
