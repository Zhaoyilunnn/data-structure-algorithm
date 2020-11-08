//
// Created by zyl on 2020/3/26.
//

#include "graph.h"


/**
 * MST
 * set      --> denote whether current vertex node has been visited
 * low_cost --> denote the minimum edge from current MST to current node
 * @param graph: input graph, where graph[i][j] means the weight of edge(i, j)
 * @return
 */
int Prim(vector<vector<int>> &graph) {
    int sum = 0;
    int n = graph.size();
    vector<int> set(n, 0);      // when visited, set 1
    vector<int> low_cost(n, 0); // assume that all edge > 0
    int v = 0;  // point to current node

    // initialize low_cost
    for (int j = 0; j < n; j++)
        low_cost[j] = graph[v][j];

    for (int i = 0; i < n-1; i++) {
        set[v] = 1;
        int min = 0;
        int k = 0;

        // find the minimum edge
        for (int j = 0; j < n; j++) {
            if ((!min || (low_cost[j] && low_cost[j] < min)) && !set[j]) {
                min = low_cost[j];
                k = j;
            }
        }

        sum += min;
        v = k;

        // update low_cost
        for (int j = 0; j < n; j++) {
            if ((!low_cost[j] || (graph[v][j] && graph[v][j] < low_cost[j])) && !set[j])
                low_cost[j] = graph[v][j];
        }
    }

    return sum;
}


void fastSort(vector<road>& graph, int l, int r) {
    if (l > r) return;
    int i = l, j = r;
    road temp = graph[l];
    while (i < j) {
        while (i < j && graph[j].w >= temp.w) j--;
        if (i < j) {
            graph[i] = graph[j];
            i++;
        }
        while (i < j && graph[i].w < temp.w) i++;
        if (i < j) {
            graph[j] = graph[i];
            j--;
        }
    }
    graph[i] = temp;
    fastSort(graph, l, i - 1);
    fastSort(graph, i + 1, r);
}

void sortRoad(vector<road>& graph) {
    int l = 0;
    int r = graph.size() - 1;
    fastSort(graph, l, r);
}

int getRoot(int p, vector<int>& FUSet) {
    while (p != FUSet[p])
        p = FUSet[p];
    return p;
}

/**
 * MST (Minimum Spanning Tree) using Kruscal's algorithm
 * Steps:
 *      1. Sort all the edges in non-decreasing order of their weight
 *      2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far, if cycle is not
 *      formed, include this edge. Else, discard it
 *      3. Repeat step 2 until there are (V - 1) edges in the spanning tree
 * @param graph
 * @param FUSet
 * @return
 */
int Kruskal(vector<road>& graph, vector<int>& FUSet) {
    int sum = 0;
    sortRoad(graph);
    for (int i = 1; i < graph.size(); i++) {
        if (getRoot(graph[i].a, FUSet) != getRoot(graph[i].b, FUSet)) {
            FUSet[graph[i].b] = graph[i].a;
            sum += graph[i].w;
        }
    }
    return sum;
}



/**
 * Shortest Paths -- Dijkstra
 * Steps:
 *      1.
 *      2.
 *      3.
 * @param graph: input graph, where graph[i][j] is the weight of arc(i, j)
 * @param source: source node, integer
 * @param dest: desi[i] is the shortest path from source to vertex i
 * @return
 */
void Dijkstra(vector<vector<int>>& graph, int source, vector<int>& dest) {
    int num_nodes = graph.size();

    // first initialize dest vector, stores current shortest path from source to dest
    for (int i = 0; i < num_nodes; i++) {
        if (i != source && graph[source][i]) dest[i] = graph[source][i];
        else dest[i] = INT32_MAX;
    }
    dest[source] = 0;
    vector<int> set_visited(num_nodes, 0);
    set_visited[source] = 1;
    for (int j = 0; j < num_nodes - 1; j++) {
        int curr_min_path = INT32_MAX;
        int curr_vertex = -1;
        for (int i = 0; i < num_nodes; i++) {
            if (dest[i] && !set_visited[i] && dest[i] < curr_min_path) {
                curr_min_path = dest[i];
                curr_vertex = i;
            }
        }
        set_visited[curr_vertex] = 1;
        for (int i = 0; i < num_nodes; i++) {
            if (graph[curr_vertex][i] && !set_visited[i] && graph[curr_vertex][i] + dest[curr_vertex] < dest[i])
                dest[i] = graph[curr_vertex][i] + dest[curr_vertex];
        }
    }
}

class comp {
public:
    bool operator() (const pair<int, int>* l, const pair<int, int>* r) {
        return l->second < r->second;
    }
};


/**
 * Pseudo code
 * InitSSSP(s)
 * Insert(s, 0)
 * while the priority queue is not empty
 *      u <-- ExtractMin()
 *      for all edges u-->v
 *          if u-->v is tense
 *              Relax(u-->v)
 *              if v is in the priority queue
 *                  DecreaseKey(v, dist(v))
 *              else
 *                  Insert(v, dist(v))
 *
 * Ref: https://jeffe.cs.illinois.edu/teaching/algorithms/
 * @param graph
 * @param src
 * @param dest
 */
void DijkstraII(vector<vector<int>>& graph, int src, vector<int>& dest) {
    int n = graph.size();
    set<pair<int, int>*, comp> pq;  // performs like a priority queue
    unordered_map<int, pair<int, int>*> maps;  // connect each vertex with corresponding key in pq

    // initialization
    for (int i = 0; i < n; i++) {
        if (graph[src][i]) {
            dest[i] = graph[src][i];
            auto p = new pair<int, int>(i, graph[src][i]);
            pq.emplace(p);
            maps[i] = p;
        } else dest[i] = INT32_MAX;
    }
    dest[src] = 0;
    auto p = new pair<int, int>(src, 0);
    maps[src] = p;
    pq.emplace(p);
    while (!pq.empty()) {
        int u = (*pq.begin())->first;
        pq.erase(pq.begin());
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && graph[u][v] + dest[u] < dest[v]) {
                // Edge u-->v is tense
                dest[v] = graph[u][v] + dest[u];
                if (maps.find(v) != maps.end()) {
                    // v is in priority queue
                    auto it = pq.find(maps[v]);
                    (*it)->second = dest[v];
                } else {
                    // v is not priority queue
                    auto q = new pair<int, int>(v, dest[v]);
                    pq.emplace(q);
                    maps[v] = q;
                }
            }
        }
    }
    for (auto m : maps) {
        delete m.second;
    }
}


/**
 * 拓扑排序：找到入度为零的结点，遍历它的出边上的结点，直到遍历到一个没有出边的结点
 * @param gInput
 * @return
 */
int topSort(digraph &gInput) {
    stack<topVertexNode*> topNodes; // 存储一开始入度为0的所有结点
    vector<topVertexNode*> nodes = gInput.vertex_list; // 存储邻接表
    for (auto node : nodes) {
        if (node->count == 0)
            topNodes.push(node); // 将所有入度为零的结点入栈，（也可以只存储结点的标号）
    }
    int num_nodes = gInput.n;
    while (!topNodes.empty()) {
        topVertexNode* topNode = topNodes.top();
        topNodes.pop();
        num_nodes--;
        digraphEdgeNode* edgeNode = topNode->first;
        cout << topNode->data;
        while (edgeNode) {
            nodes[edgeNode->adjacent]->count--;
            if (nodes[edgeNode->adjacent]->count == 0)
                topNodes.push(nodes[edgeNode->adjacent]);
            edgeNode = edgeNode->next;
        }
    }
    return num_nodes == 0 ? 1 : 0;  // 如果所有结点都被遍历了则当前的图有拓扑序列
}

// Here the matrix is M by M, if the element is 1, and the position is (m, n), it means that the number m+1 has
// a connection with number n+1 node
void graphTraverseBFS(vector<vector<int>>& matrix) {
    vector<int> visited(matrix.size()+1, 0);
    visited[1] = 1;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int top = q.front();
        cout << top << endl;
        q.pop();
        int i;
        for (i = 1; i <= matrix.size(); i++) {
            if (visited[i] == 0 && matrix[top-1][i-1] == 1) {
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}




