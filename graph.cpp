//
// Created by zyl on 2020/3/26.
//

#include "graph.h"


/******************************************************************************/
/* set      --> denote whether current vertex node has been visited
 * low_cost --> denote the minimum edge from current tree to current node */
/******************************************************************************/
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


/********************************************************************************/
/* Description:  */
/********************************************************************************/
void sortRoad(vector<road>& graph) {

}

int getRoot(int p, vector<int>& FUSet) {
    while (p != FUSet[p])
        p = FUSet[p];
    return p;
}

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



/*******************************************************************/
/* 拓扑排序：找到入度为零的结点，遍历它的出边上的结点，知道遍历到一个
 * 没有出边的结点 */
/*******************************************************************/
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
    if (num_nodes == 0) // 如果所有结点都被遍历了则当前的图有拓扑序列
        return 1;
    else
        return 0;
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




