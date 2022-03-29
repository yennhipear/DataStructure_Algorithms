//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int main()
//{
//
//    return 0;
//}


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

typedef vector <vector <int>> Graph;

Graph ReadGraphFromFile(const char* filename)
{
    vector < vector <int> > ans;
    ifstream fin(filename);

    int n; fin >> n; fin.ignore();

    for (int i = 0; i < n; i++)
    {
        vector <int> temp;
        string str; getline(fin, str);
        unsigned int j = 0;

        while (j < str.length())
        {
            string x = "";
            while ((j < str.length()) && (str[j] != ' ')) x = x + str[j++];
            temp.push_back(atoi(x.c_str()));
            j++;
        }

        ans.push_back(temp);
    }

    fin.close();
    return ans;
}

bool IsAdjacencyList(Graph G)
{
    for (unsigned int i = 0; i < G.size(); i++)
        if (G.size() != G[i].size()) return true;
    return false;
}

Graph AdjListToAdjMatrix(Graph G)
{
    Graph ans;

    for (unsigned int i = 0; i < G.size(); i++)
    {
        vector <int> temp;
        for (unsigned int j = 0; j < G.size(); j++)
            temp.push_back(0);
        ans.push_back(temp);
    }

    for (unsigned int i = 0; i < G.size(); i++)
        for (unsigned int j = 0; j < G[i].size(); j++)
            ans[i][G[i][j]] = 1;

    return ans;
}

void OutputGraph(Graph G)
{
    for (unsigned int i = 0; i < G.size(); i++)
    {
        for (unsigned int j = 0; j < G[i].size(); j++) cout << G[i][j] << " ";
        cout << endl;
    }
}

bool IsDirectedGraph(Graph G)
{
    for (unsigned int i = 1; i < G.size(); i++)
        for (unsigned int j = 0; j < i; j++)
            if (G[i][j] != G[j][i])
                return true;

    return false;
}

int CountEdges(Graph G)
{
    int ans = 0;
    for (unsigned int i = 0; i < G.size(); i++)
        for (unsigned int j = 0; j < G[i].size(); j++)
            ans += G[i][j];

    if (!IsDirectedGraph(G)) return ans / 2;
    return ans;
}

int CountVertices(Graph G)
{
    return G.size();
}

int CalcInDegree(Graph G, int v)
{
    int ans = 0;
    for (unsigned int j = 0; j < G[v].size(); j++) ans += G[v][j];
    return ans;
}

int CalcOutDegree(Graph G, int v)
{
    int ans = 0;
    for (unsigned int i = 0; i < G.size(); i++) ans += G[i][v];
    return ans;
}

int CalcDegree(Graph G, int v)
{
    if (IsDirectedGraph(G)) return CalcInDegree(G, v) + CalcOutDegree(G, v);
    return CalcInDegree(G, v);
}

void ListVerticesDegree(Graph G)
{
    for (int v = 0; v < CountVertices(G); v++)
        if (IsDirectedGraph(G)) cout << "v " << v << " : deg(+) = " << CalcInDegree(G, v) << ", deg(-) = " << CalcOutDegree(G, v) << endl;
        else cout << "v " << v << " : deg = " << CalcDegree(G, v) << endl;
}

void ListIsolatedVertices(Graph G)
{
    bool isExist = false;
    for (int v = 0; v < CountVertices(G); v++)
        if (CalcDegree(G, v) == 0)
        {
            cout << v << " ";
            isExist = true;
        }

    if (!isExist) cout << "No vertices";
}

void ListLeafVertices(Graph G)
{
    bool isExist = false;
    for (int v = 0; v < CountVertices(G); v++)
        if (CalcDegree(G, v) == 1)
        {
            cout << v << " ";
            isExist = true;
        }

    if (!isExist) cout << "No vertices";
}

bool IsCompleteGraph(Graph G)
{
    if (IsDirectedGraph(G)) return false;
    if (CountVertices(G) == 1) return true;

    for (unsigned int i = 1; i < G.size(); i++)
        for (unsigned int j = 0; j < i; j++)
            if ((G[i][j] == 0) || (G[j][i] == 0) || (G[i][j] != G[j][i])) return false;

    return true;
}

bool IsCircularGraph(Graph G)
{
    if (IsDirectedGraph(G)) return false;
    if (CountEdges(G) != CountVertices(G)) return false;

    for (unsigned int v = 0; v < G.size(); v++)
        if (CalcDegree(G, v) != 2) return false;

    return true;
}

bool IsBigraph(Graph G)
{
    if (CountVertices(G) < 2) return false;

    int colorArr[11];
    colorArr[CountVertices(G)] = {-1}; // -1: Not Checked Yet, 0: Blue, 1: Yellow
    colorArr[0] = 1;

    // BSF
    queue <int> q; q.push(0);

    while (!q.empty())
    {
        int u = q.front(); q.pop();

        if (G[u][u] == 1) return false; // A loop

        for (int v = 0; v < CountVertices(G); v++)
            if (G[u][v] && (colorArr[v] == -1))
            {
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
            else if (G[u][v] && colorArr[v] == colorArr[u]) return false;
    }

    return true;
}

bool IsCompleteBigraph(Graph G)
{
    if (CountVertices(G) < 2) return false;

    // Check for Bigraph
    int colorArr[11];
    colorArr[CountVertices(G)] = {-1}; // -1: Not Checked Yet, 0: Blue, 1: Yellow
    colorArr[0] = 1;

    // BSF
    queue <int> q; q.push(0);

    while (!q.empty())
    {
        int u = q.front(); q.pop();

        if (G[u][u] == 1) return false; // A loop

        for (int v = 0; v < CountVertices(G); v++)
            if (G[u][v] && (colorArr[v] == -1))
            {
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
            else if (G[u][v] && colorArr[v] == colorArr[u]) return false;
    }

    // Check for complete
    int countColor0 = 0, countColor1 = 0;
    for (int v = 0; v < CountVertices(G); v++)
    {
        countColor0 += (!colorArr[v]);
        countColor1 += colorArr[v];
    }

    if (CountEdges(G) != countColor0 * countColor1) return false;
    return true;
}

int CountConnectedComponents(Graph G)
{
    int ans = 0; bool visited[11];
    visited[CountVertices(G)] = {false};

    for (int i = 0; i < CountVertices(G); i++)
        if (!visited[i])
        {
            // BFS
            queue <int> q; q.push(i);

            while (!q.empty())
            {
                int u = q.front(); q.pop();
                visited[u] = true;

                for (int v = 0; v < CountVertices(G); v++)
                    if ((G[u][v]) && (!visited[v])) q.push(v);
            }

            ans++;
        }

    return ans;
}

int CountTrees(Graph G)
{
    int ans = 0; bool visited[11];
    visited[CountVertices(G)] = {false};

    for (int i = 0; i < CountVertices(G); i++)
        if (!visited[i])
        {
            // BFS
            bool isCycle = false;
            queue <int> q; q.push(i);

            while (!q.empty())
            {
                int u = q.front(); q.pop();
                visited[u] = true;

                for (int v = 0; v < CountVertices(G); v++)
                    if (G[u][v])
                    {
                        if (visited[v]) isCycle = true;
                        else q.push(v);
                    }
            }

            ans += isCycle;
        }

    return ans;
}

int CountCutVertices(Graph G)
{
    int ans = 0;
    int numOfConnectedComponents_OLD = CountConnectedComponents(G);

    for (int v = 0; v < CountVertices(G); v++)
    {
        Graph tempG = G;

        // Remove vertex i from graph tempG
        for (int i = 0; i < CountVertices(tempG); i++)
            tempG[v][i] = tempG[i][v] = 0;

        // If number of connected components in the new graph (except the component v) is greater than old graph's, it's a cut vertex
        if (CountConnectedComponents(tempG) - 1 > numOfConnectedComponents_OLD) ans++;
    }

    return ans;
}

int CountBridgeEdges(Graph G)
{
    int ans = 0;
    int numOfConnectedComponents_OLD = CountConnectedComponents(G);

    for (int u = 0; u < CountVertices(G); u++)
        for (int v = 0; v < CountVertices(G); v++)
            if (G[u][v])
            {
                Graph tempG = G;

                // Remove edge u->v from graph tempG
                tempG[u][v] = 0;
                if (!IsDirectedGraph(G)) tempG[v][u] = 0; // Remove v->u too, because this is an undirected graph

                // If number of connected components in the new graph is greater than old graph's, it's a cut vertex
                if (CountConnectedComponents(tempG) > numOfConnectedComponents_OLD) ans++;
            }

    if (!IsDirectedGraph(G)) return ans / 2; // Edges in Directed graph are check twice
    return ans;
}

Graph BaseUndirectedGraph(Graph G)
{
    Graph ans = G;

    for (unsigned int u = 0; u < ans.size(); u++)
        for (unsigned int v = 0; v < ans[u].size(); v++)
            if ((ans[u][v]) && (!ans[v][u])) ans[v][u] = ans[u][v];

    return ans;
}

Graph ComplementGraph(Graph G)
{
    Graph ans = G;

    for (unsigned int u = 0; u < ans.size(); u++)
        for (unsigned int v = 0; v < ans[u].size(); v++)
            if (u != v) ans[u][v] = !ans[u][v];

    return ans;
}

Graph ConverseGraph(Graph G)
{
    Graph ans = G;

    for (unsigned int u = 1; u < ans.size(); u++)
        for (unsigned int v = 0; v < u; v++)
            swap(ans[u][v], ans[v][u]);

    return ans;
}

void HierholzersAlgorithm(Graph G)
{
    vector<int> circuit;

    stack<int> curr_path; curr_path.push(0);
    int curr_v = 0;

    while (!curr_path.empty())
    {
        if (G[curr_v].size())
        {
            curr_path.push(curr_v);
            int next_v = G[curr_v].back(); G[curr_v].pop_back();
            curr_v = next_v;
        }
        else
        {
            circuit.push_back(curr_v);
            curr_v = curr_path.top(); curr_path.pop();
        }
    }

    for (int i = circuit.size() - 1; i >= 0; i--)
    {
        cout << circuit[i];
        if (i) cout << " -> ";
    }
}

void DFS(Graph G, bool visited[], int u)
{
    visited[u] = true; cout << u << " ";

    for (int v = 0; v < CountVertices(G); v++)
        if ((G[u][v])&&(!visited[v]))
            DFS(G, visited, v);
}

void SpanningTreeDFS(Graph G)
{
    bool visited[11];
    visited[CountVertices(G)] = {false};
    DFS(G, visited, 0);
}

void SpanningTreeBFS(Graph G)
{
    bool visited[11];
    visited[CountVertices(G)] = {false};

    queue <int> q; q.push(0); visited[0] = true;
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        cout << u << " ";

        for (int v = 0; v < CountVertices(G); v++)
        {
            if ((G[u][v])&&(!visited[v]))
            {
                q.push(v);
                visited[v] = true;
            }
        }
    }
}

void PrimAlgorithm(Graph G)
{
    if ((CountEdges(G) >= CountVertices(G) - 1) && (CountConnectedComponents(G) == 1))
    {
        bool visited[20];
        visited[CountVertices(G)] = {false};
        visited[5] = true;

        for (int i = 1; i < CountVertices(G); i++)
        {
            int minBranch = 100000, curr_v = -1, next_v = -1;
            for (int u = 0; u < CountVertices(G); u++)
            {
                if (visited[u])
                {
                    for (int v = 0; v < CountVertices(G); v++)
                    {
                        if ((u != v) && (!visited[v]) && (G[u][v] < minBranch))
                        {
                            minBranch = G[u][v];
                            curr_v = u; next_v = v;
                        }
                    }
                }
            }
            visited[next_v] = true;
            cout << curr_v << next_v << " ";
        }
    }
    else cout << "Cannot draw a spanning!" << endl;
}

struct Edge
{
    int first;
    int last;
    int weight;
};

void KruskalAlgorithm(Graph G)
{
    if ((CountEdges(G) >= CountVertices(G) - 1) && (CountConnectedComponents(G) == 1))
    {
        vector <Edge> e;
        for (int u = 1; u < CountVertices(G); u++)
        {
            for (int v = 0; v < u; v++)
            {
                Edge temp = {u, v, G[u][v]};
                e.push_back(temp);
            }
        }

        for (unsigned int i = 0; i < e.size() - 1; i++)
        {
            for (unsigned int j = i + 1; j < e.size(); j++)
            {
                if (e[i].weight > e[j].weight)
                {
                    Edge temp = e[i];
                    e[i] = e[j];
                    e[j] = temp;
                }
            }
        }
        bool visited[11];
        visited[CountVertices(G)] = {false}; int n = 0, i = 0;
        do
        {
            while (visited[e[i].first] && visited[e[i].last]) i++;
            cout << e[i].last << e[i].first << " ";
            visited[e[i].first] = true; visited[e[i].last] = true;
            n++;
        } while (n < CountVertices(G) - 1);
    }
    else cout << "Cannot draw a spanning!" << endl;
}

void DFS_NoPrint(Graph G, bool visited[], int u)
{
    visited[u] = true;

    for (int v = 0; v < CountVertices(G); v++)
    {
        if ((G[u][v])&&(!visited[v]))
            DFS_NoPrint(G, visited, v);
    }
}

bool IsConnectivity(Graph G, int v1, int v2)
{
    bool visited[11];
    visited[CountVertices(G)] = {false};
    DFS_NoPrint(G, visited, v1);
    return visited[v2];
}

int DijkstraAlgorithm(Graph G, int v1, int v2)
{
    bool visited[11];
    visited[CountVertices(G)] = {false};

    int d[CountVertices(G)][CountVertices(G)];
    for (int i = 0; i < CountVertices(G); i++)
    {
        for (int j = 0; j < CountVertices(G); j++)
            d[i][j] = 100000000;
    }
    d[0][v1] = 0;

    for (int i = 1; i < CountVertices(G); i++)
    {
        int minVal = 100000000, minVertex = -1;
        for (int v = 0; v < CountVertices(G); v++)
        {
            if ((!visited[v]) && (d[i - 1][v] < minVal))
            {
                minVal = d[i - 1][v];
                minVertex = v;
            }
        }
        visited[minVertex] = true;

        for (int v = 0; v < CountVertices(G); v++)
        {
            if ((!visited[v]) && (d[i - 1][v] > d[i - 1][minVertex] + G[minVertex][v]))
                d[i][v] = d[i - 1][minVertex] + G[minVertex][v];
            else d[i][v] = d[i - 1][v];
        }
    }

    return d[CountVertices(G) - 1][v2];
}

int FloydWarshallAlgorithm(Graph G, int v1, int v2)
{
    int d[CountVertices(G)][CountVertices(G)];
    for (int i = 0; i < CountVertices(G); i++)
    {
        for (int j = 0; j < CountVertices(G); j++)
            d[i][j] = G[i][j];
    }

    for (int k = 0; k < CountVertices(G); k++)
        for (int i = 0; i < CountVertices(G); i++)
            for (int j = 0; j < CountVertices(G); j++)
                if (d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j];

    return d[v1][v2];
}

int BellmanFordAlgorithm(Graph G, int v1, int v2)
{
    int d[CountVertices(G)][CountVertices(G)];
    for (int i = 0; i < CountVertices(G); i++)
        for (int j = 0; j < CountVertices(G); j++)
            d[i][j] = 100000000;
    d[0][v1] = 0;

    for (int i = 1; i < CountVertices(G); i++)
    {
        for (int u = 0; u < CountVertices(G); u++)
        {
            d[i][u] = d[i - 1][u];

            for (int v = 0; v < CountVertices(G); v++)
            {
                if (d[i - 1][u] > d[i - 1][v] + G[v][u])
                    d[i][u] = d[i - 1][v] + G[v][u];
            }
        }

        bool isStability = true;
        for (int u = 0; u < CountVertices(G); u++)
        {
            if (d[i][u] != d[i - 1][u]) isStability = false;
        }
        if (isStability) return d[i][v2];
    }

    return -1;
}

int main()
{
    // 1 and 2. Read From File
    Graph G = ReadGraphFromFile("graph2.txt"); // Could be replaced to graph1.txt
    cout << "File content: " << endl; OutputGraph(G); cout << endl;
    if (IsAdjacencyList(G)) G = AdjListToAdjMatrix(G);

    // 3. Providing infomation
    cout << "This is a " << ((IsDirectedGraph(G)) ? "Directed Graph!" : "Undirected Graph!") << endl;
    cout << "Number of edges: " << CountEdges(G) << endl;
    cout << "Number of vertices: " << CountVertices(G) << endl;
    cout << "Vertices degree: " << endl; ListVerticesDegree(G);
    cout << "List of isolated vertices: "; ListIsolatedVertices(G); cout << endl;
    cout << "List of leaf vertices: "; ListLeafVertices(G); cout << endl;
    cout << "This is " << ((IsCompleteGraph(G)) ? " a Complete Graph" : " NOT a Complete Graph") << endl;
    cout << "This is " << ((IsCircularGraph(G)) ? " a Circular Graph" : " NOT a Circular Graph") << endl;
    cout << "This is " << ((IsBigraph(G)) ? " a Bigraph" : " NOT a Bigraph") << endl;
    cout << "This is " << ((IsCompleteBigraph(G)) ? " a Complete Bigraph" : " NOT a Complete Bigraph") << endl;
    cout << "Number of Connected components: " << CountConnectedComponents(G) << endl;
    cout << "Number of Trees: " << CountTrees(G) << endl;
    cout << "Number of Cut Vertices: " << CountCutVertices(G) << endl;
    cout << "Number of Bridge Edges: " << CountBridgeEdges(G) << endl << endl;

    // 4. Base undirected graph
    if (IsDirectedGraph(G))
    {
        cout << "Base undirected graph: " << endl;
        OutputGraph(BaseUndirectedGraph(G));
        cout << endl;
    }
    else  cout << "Cannot make Base undirecion because it's already undirection" << endl;

    // 5. Complement graph
    if (!IsDirectedGraph(G))
    {
        cout << "Complement graph: " << endl;
        OutputGraph(ComplementGraph(G));
        cout << endl;
    } else cout << "Cannot make component graph" << endl;

    // 6. Converse Graph
    if (IsDirectedGraph(G))
    {
        cout << "Converse graph: " << endl;
        OutputGraph(ConverseGraph(G));
        cout << endl;
    }
    else cout << "All model now to using fat milk, protect you now!" << endl;

    // 7. Hierholzer's Algorithm
    G = ReadGraphFromFile("EulerGraph.txt");
    cout << "Euler Circle: "; HierholzersAlgorithm(G); cout << endl;

    // 8. Spanning Tree
    G = BaseUndirectedGraph(ReadGraphFromFile("graph1.txt"));
    cout << "Spanning Tree using DFS: "; SpanningTreeDFS(G); cout << endl;
    cout << "Spanning Tree using BFS: "; SpanningTreeBFS(G); cout << endl;

    // 9. Minimum Spanning Tree
    G = ReadGraphFromFile("WeightGraph.txt");
    cout << "Prim Algorithm: "; PrimAlgorithm(G); cout << endl;
    cout << "Kruskal Algorithm: "; KruskalAlgorithm(G); cout << endl;

    // 10. Verify the connection between v1 and v2
    int v1, v2;
    cout << "First vertex  : "; cin >> v1;
    cout << "Second vertex : "; cin >> v2;
    if (IsConnectivity(G, v1, v2))
    {
        cout << "Connectivity" << endl;

        // 11. Shortest path
        cout << "Shortest path (Dijkstra Algorithm)       : " << DijkstraAlgorithm(G, v1, v2) << endl;
        cout << "Shortest path (Floyd-Warshall Algorithm) : " << FloydWarshallAlgorithm(G, v1, v2) << endl;
        cout << "Shortest path (Bellman-Ford Algorithm)   : " << BellmanFordAlgorithm(G, v1, v2) << endl;
    }
    else cout << "Unconnectivity" << endl;

    return 0;
}


