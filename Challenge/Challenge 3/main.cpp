#include <iostream>
#include <vector>
#include <math.h>
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

bool checkStarGraph(vector<vector<bool>> adj) {
	//Kiem tra co phai do thi sao khong
	int size = adj.size();
	int degOneVert = 0, degVert = 0;   //Khoi tao so luong dinh co bac 1 và bac n - 1 la 0
	if (size == 1) //Khi co 1 dinh thi khong phai sao
		return 0;

	if (size == 2)
		return (adj[0][0] == 0 && adj[0][1] == 1 && adj[1][0] == 1 && adj[1][1] == 0);

	for (int i = 0; i < size; i++) {    
		int degree = 0;
		for (int j = 0; j < size; j++)    
			if (adj[i][j])
				degree++;
		if (degree == 1)
			degOneVert++;
		else if (degree == size - 1)
			degVert++;
	}
	
	return (degOneVert == (size - 1) && degVert == 1);
}

void removeVertex(int pos, vector<vector<bool>> &adj)
{
	//Xoa dinh pos ra khoi do thi
	if (pos > adj.size() || pos < 0) {
		return;
	}
	else {
		while (pos < adj.size() - 1) {	
			for (int i = 0; i < adj.size(); i++) {
				adj[i][pos] = adj[i][pos + 1];
			}
			for (int i = 0; i < adj.size(); i++) {
				adj[pos][i] = adj[pos + 1][i];
			}
			pos++;
		}	
		adj.pop_back();
	}	
}



int degree(vector<vector<bool>> adj, int pos) {
	int deg = 0;
	for (int i = 0; i < adj.size(); i++) {
		deg += adj[pos][i];
	}
	return deg;
}

int maxDegree(vector<vector<bool>> adj) {
	int max = 0;
	for (int i = 0; i < adj.size(); i++) {
		max = (max > degree(adj, i)) ? max : degree(adj, i);
	}
	return max;
}

bool isAdjacency(vector<vector<bool>>adj, int v1, int v2) {
	if (v1 > adj.size() || v2 > adj.size()) return 0;
	return (adj[v1][v2]);
}
vector<vector<short>> generateAdjList(vector<vector<bool>> adj) {
	vector<vector<short>> list;
	for (int i = 0; i < adj.size(); i++) {
		vector<short> temp;
		temp.push_back(i);
		for (int j = 0; j < adj.size(); j++) {	
			if (isAdjacency(adj, i, j)) {
				temp.push_back(j);
			}
		}
		list.push_back(temp);
	}
	return list;
}

//Ham dem so luong sao co the xay ra trong cua DO THI SAO ADJ. Duoc tinh bang cong thuc 2^(size-1) - 1
//Vi du: Do thi hinh sao co 4 dinh thi so luong sao co the co la 7
int countStarWithSize(vector<vector<bool>> adj) {
	return (pow(2, adj.size() - 1) - 1);
}

//Ham dem so luong sao
//Y tuong: Chia do thi ban dau ra thanh cac do thi sao nho (small) de tinh toan
//Cach lam: Tim nhung dinh co bac tu lon nhat den nho nhat, gia su goi la dinh v.
//		Khi do, lap mot do thi con gom dinh v va nhung dinh ke voi no, goi do thi do la G. (dung AdjList)
//		Tiep theo, tinh toan so luong sao co the co trong G
//		Moi lan tim duoc do thi SAO con trong do thi ban dau, ta xoa G ra khoi do thi ban dau.
//		Lap lai den khi do thi ban dau rong.
int countStars(vector<vector<bool>> adj) {
	int count = 0;
	vector<vector<bool>> originalAdj = adj;
	vector<vector<short>> AdjList;
	int maxDeg = maxDegree(adj);
	for (int deg = maxDeg; deg > 0; deg--) {
		AdjList = generateAdjList(adj);		
		for (int i = 0; i < adj.size(); i++) {
			
			if (degree(adj, i) == deg) {
				vector<vector<bool>> tempAdj;				
				for (int j = 0; j < AdjList[i].size(); j++) {
					vector<bool>temp;
					for (int k = 0; k < AdjList[i].size(); k++) {
						if (isAdjacency(adj, AdjList[i][j], AdjList[i][k])) temp.push_back(1);
						else temp.push_back(0);
					}
					tempAdj.push_back(temp);
				}				
				count += countStarWithSize(tempAdj);
				int countRemove = 0; //danh dau dung vi tri can xoa, vi sau khi xoa dinh i, ma tran ke se thay doi chi so 
				for (int j = 0; j < AdjList[i].size(); j++) {
					removeVertex(AdjList[i][j] - countRemove, adj);
					countRemove++;
				}
				i = 0;
			}
		}
	}
	adj = originalAdj;
	return count;
}



int main() {
	//vector<vector<bool>> adj = { {0,1,0,0,0},{1,0,0,0,0},{0,0,0,1,0},{0,0,1,0,0}, {0,0,0,0,0} };
	vector<vector<bool>> adj = { {0,0,0,1},{0,0,0,1},{0,0,0,1,},{1,1,1,0} };
	
	//vector<vector<bool>> adj = { {0,1,0,0,0,0,0},{1,0,1,0,0,0,0},{0,1,0,0,0,0,0},{0,0,0,0,1,1,1},{0,0,0,1,0,0,0},{0,0,0,1,0,0,0} ,{0,0,0,1,0,0,0} };
	OutputMatrix(adj);
	cout << endl;
	cout << "There is/are "<<countStars(adj)<<" star(s)\n";
	
}