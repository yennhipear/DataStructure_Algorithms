#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define ALPHABET_SIZE 26

using namespace std;

struct TrieNode
{
    bool isEnd;                     //Check the end of 1 word
    TrieNode* next[ALPHABET_SIZE];  //The letters of the alphabet
};

TrieNode* createNode()
{
    TrieNode* p = new TrieNode;
    p->isEnd = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        p->next[i] = NULL;
    }
    return p;
}

//Convert a character to the ASCII value
int charToIndex(char c)
{
    return c - 'a';
}

//Convert the ASCII value to a character
char indexToChar(int i)
{
    return i + 'a';
}

//Add one key into Trie
void Insert(TrieNode*& root, string key)
{
    TrieNode* p = root;
    for (int i = 0; i < key.size(); i++)
    {
        int index = charToIndex(key[i]);    //Position of each letter
        if (p->next[index] == NULL) //If that letter doesn't exist, create a new one and add it to Trie
        {
            p->next[index] = createNode();
        }

        p = p->next[index]; //Point to the next letter
    }

    p->isEnd = true;
}

//Read from file "Dic.txt"
void sendWordToTrie(TrieNode*& root, string file_to_read)
{
    fstream fin;
    fin.open(file_to_read, ios::in);

    if (fin)
    {
        string word;
        while (getline(fin, word))
        {
            Insert(root, word);     //add word to Trie
        }
        fin.close();
    }
    else
    {
        cout << "NON-EXIST FILE!!!!" << endl;
    }
}

//Check input is a valid string
bool isValidInput(string input)
{
    int charMin = charToIndex('a');
    for (int i = 0; i < input.size(); i++)
    {
        if (i % 2 == 0)
        {
            if (islower(input[i]) && charToIndex(input[i]) >= charMin) //check input[i] is lower case letter and sorted in alphabetical order
            {
                charMin = charToIndex(input[i]);
            }
            else return false;
        }
        else
        {
            if (input[i] != ' ')
            {
                return false;
            }
        }
    }
    return true;
}

//Remove spaces from input string
vector <char> splitToChar(string input)
{
    vector <char> characters;
    for (int i = 0; i < input.size(); i++)
    {
        if (i % 2 == 0)
        {
            characters.push_back(input[i]);
        }
    }
    return characters;
}

//Check for validity of a found string
bool isValidString(string found, vector <char> characters)
{
    characters.push_back('/');

    int countChar = 1;      //count characters in one characters
    for (int i = 0; i < characters.size() - 1; i++)
    {
        if (characters[i] == characters[i + 1])
        {
            countChar++;
            continue;
        }
        int countKey = 0;   //count characters in found
        for (int j = 0; j < found.size(); j++)
        {
            if (found[j] == characters[i])
            {
                countKey++;
                if (countKey > countChar) return false;
            }
        }
        countChar = 1;
    }
    characters.pop_back();
    return true;
}

//Check for existence of a string
bool isExistBefore(vector <string> results, string found)
{
    int left = 0;
    int right = results.size() - 1;
    if (right < 0)
    {
        return false;
    }
    while (left <= right)   //Use Binary Search to check a word already exists or not
    {
        int mid = (left + right) / 2;
        if (results[mid] == found)
        {
            return true;
        }
        if (results[mid] < found)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return false;
}

//Search for a word based on key “found”
void searchWord(TrieNode* root, string found, vector <string> &results, vector<char>characters)
{
    if (root->isEnd)
    {
        if (found.size() > 2 && isValidString(found, characters) && !isExistBefore(results, found))
        {
            results.push_back(found);
        }
    }

    for (int i = 0; i < characters.size(); i++)
    {
        if (root->next[charToIndex(characters[i])])
        {
            searchWord(root->next[charToIndex(characters[i])],found + characters[i], results, characters);
        }
    }
}

//Find all valid words and return result
vector <string> findAllWords (TrieNode* root, vector <char> characters)
{
    vector <string> results;
    TrieNode* p = root;
    for (int i = 0; i < characters.size(); i++)
    {
        if (p->next[charToIndex(characters[i])])
        {
            string found = "";
            found += characters[i];
            searchWord(p->next[charToIndex(characters[i])], found, results, characters);
            //Search for a word based on key “found”
        }
    }
    return results;
}

//Remove Trie
void deleteTrie(TrieNode*& root)
{
    if (root == NULL)
    {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        deleteTrie(root->next[i]);  //Delete nodes in the tree from bottom to top
    }
    delete root;
    root = NULL;
}

//Main
int main()
{
    // IMPORT DICTIONARY
    TrieNode* root = createNode();
    sendWordToTrie(root, "Dic.txt");
    
    string input;
    fstream file;
    file.open("Input.txt",ios::in);
    if (file.fail()) cout << "Can't open file Input.txt" << endl;
    else
    {
        //INPUT
        while (!file.eof())
        {
            getline(file, input);
            if (isValidInput(input))  break;
        }
        file.close();
        
        //OUTPUT
        vector<char>characters  = splitToChar(input);
        vector<string>results   = findAllWords(root, characters);
        
        cout << results.size() << endl;
        for (int i = 0; i < results.size(); i++)
            cout << results[i] << endl;
        
        // DELETE TRIES
        deleteTrie(root);
    }
    
    cout << endl;
    return 0;
}

