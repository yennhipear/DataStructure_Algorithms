#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;


vector<vector<bool>> InputAdjMatrix(int size) {
	vector<vector<bool>> adj;
	bool n;
	for (int i = 0; i < size; i++) {
		vector<bool> temp;
		for (int j = 0; j < size; j++) {
			cin >> n;
			temp.push_back(n);
		}
		adj.push_back(temp);
	}
	return adj;
}

void OutputMatrix(vector<vector<bool>> adj) {
	for (int i = 0; i < adj.size(); i++) {
		for (int j = 0; j < adj.size(); j++) {
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}
}

//Kiem tra co phai do thi sao khong
bool checkStarGraph(vector<vector<bool>> adj) {
	int size = adj.size();
	int degOneVert = 0, degVert = 0;   //Khoi tao so luong dinh co bac 1 và bac n - 1 la 0
	if (size == 1) //Khi co 1 dinh thi khong phai sao
		return 0;

	if (size == 2)
		return (adj[0][0] == 0 && adj[0][1] == 1 && adj[1][0] == 1 && adj[1][1] == 0);

	for (int i = 0; i < size; i++)
    {
		int degree = 0;
		for (int j = 0; j < size; j++)
        {
			if (adj[i][j])  degree++;
        }
		if (degree == 1)                degOneVert++;
		else if (degree == size - 1)    degVert++;
	}
	
	return (degOneVert == (size - 1) && degVert == 1);
}

bool isButterfly (vector <vector<bool>> adj)
{
    int size = adj.size();
    int numberVerts = 0; int numberOneVert = 0;
    
    if (size < 5)   return 0;
    
    for (int i = 0; i < size; i++)
    {
        int degree = 0;
        for (int j = 0; j < size; j++)
        {
            if (adj[i][j])  degree++;
        }
        if (degree == 2)                numberVerts++;
        else if (degree == size - 1)    numberOneVert++;
    }
    return (numberVerts == (size - 1) && numberOneVert == 1);
}

//Xoa dinh pos ra khoi do thi
void removeVertex(int pos, vector<vector<bool>> &adj)
{
	//Neu vi tri xoa khong hop le thi thoat khoi ham
	if (pos > adj.size() || pos < 0)       return;
	else
    {
		while (pos < adj.size() - 1)
        {
			for (int i = 0; i < adj.size(); i++)
            {
				adj[i][pos] = adj[i][pos + 1];
			}
			for (int i = 0; i < adj.size(); i++)
            {
				adj[pos][i] = adj[pos + 1][i];
			}
			pos++;
		}	
		adj.pop_back();
	}	
}

//Kiem tra 2 dinh ke nhau
bool isAdjacency(vector<vector<bool>>adj, int v1, int v2)
{
	if (v1 > adj.size() || v2 > adj.size()) return 0;
	return (adj[v1][v2]);
}

//Khoi tao danh sach ke tu ma tran ke
vector<vector<short>> generateAdjList(vector<vector<bool>> adj)
{
	vector<vector<short>> list;
	for (int i = 0; i < adj.size(); i++)
    {
		vector<short> temp;
		temp.push_back(i);
		for (int j = 0; j < adj.size(); j++)
        {
			if (isAdjacency(adj, i, j))
            {
				temp.push_back(j);
			}
		}
		list.push_back(temp);
	}
	return list;
}

//Ma tran con duoc tao ra boi thanh phan lien thong trong ma tran ban dau
vector<vector<bool>> buildAdjFromConnectedComponent(vector<short> vertex, vector<vector<bool>> adj)
{
	vector<vector<short>> AdjList = generateAdjList(adj);
	vector <vector<bool>> tempAdj;
	for (int i = 0; i < vertex.size(); i++)
    {
		vector<bool>temp;
		for (int j = 0; j < vertex.size(); j++)
        {
			if (isAdjacency(adj, vertex[i], vertex[j]))
                 temp.push_back(1);
			else temp.push_back(0);
		}
		tempAdj.push_back(temp);
	}
	return tempAdj;
}

//Ham dem sao
//Y tuong chinh: Chia do thi ban dau thanh tung thanh phan lien thong. Bien tung thanh phan lien thong do thanh ma tran con roi kiem tra
//Sau moi lan kiem tra, xoa thanh phan lien thong do.
int countStars(vector<vector<bool>> adj)
{
	int count = 0;
	for (int i = 0; i < adj.size(); i++)
    {
		vector<bool> visited(adj.size(), 0);
		if (!visited[i])
		{
			// BFS
			queue <int> q; q.push(i);
			vector<short> temp;
			while (!q.empty())
			{
				int u = q.front(); q.pop();
				visited[u] = true;
				temp.push_back(u);
				for (int v = 0; v < adj.size(); v++)
                {
					if ((isAdjacency(adj, u, v)) && (!visited[v]))
                        q.push(v);
                }
			}
			vector <vector<bool>> tempAdj = buildAdjFromConnectedComponent(temp, adj);
			if (checkStarGraph(tempAdj)) count++;
            
			int countRemove = 0;                    //danh dau dung vi tri can xoa, vi sau khi xoa dinh i, ma tran ke se thay doi chi so
			vector<vector<short>> AdjList = generateAdjList(adj);
			for (int i = 0; i < temp.size(); i++)
            {
				removeVertex(temp[i] - countRemove, adj);
				countRemove++;
			}
		}
	}
	return count;
}


int main() {
	vector<vector<bool>> adj;
	int size;
	cout << "Please input SIZE of adjacency matrix: ";
	cin >> size;
	cout << "Please input ADJACENCY MATRIX:\n";
	adj = InputAdjMatrix(size);
	cout << "\nYour matrix:\n";
	OutputMatrix(adj);
    
////	cout << "\n\nThere is/are "<<countStars(adj)<<" star(s)\n";
//    if (isButterfly(adj))   cout << "\n\n There is a butterfly \n";
//    else cout << "\n\n There is not a butterfly \n";
	return 0;
}
