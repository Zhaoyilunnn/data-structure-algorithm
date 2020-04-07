//
// Created by zyl on 2020/3/26.
//

#ifndef DATA_STRUCTURE_LEARN_GRAPH_H
#define DATA_STRUCTURE_LEARN_GRAPH_H

#include "common.h"

/*********************************************************************/
/* 有向图的存储结构：1. 邻接表
 *                 2. 十字链表 --> 同时存储出边和入边
 * 无向图的存储结构；*/

/*********************************************************************/
/* 邻接表，只存储该顶点指向的边结点 */

// 边的数据结构
struct digraphEdgeNode {
    int adjacent; // 边的结点的值
    digraphEdgeNode* next; // 下一个边结点
};

// 顶点的数据结构
struct vertexNode {
    int data; // 顶点的值
    digraphEdgeNode* first; // 当前顶点的第一个边的结点
};
/*********************************************************************/
/* 十字链表，相比于邻接表只能存储顶点指向的边或者指向顶点的边，十字链表可以
 * 存储指向顶点以及顶点指向的边 */

// 边的数据结构
struct digraphDualEdgeNode {
    int start; // 起始结点序号
    int end; // 终点结点序号
    digraphDualEdgeNode* nextIn;
    digraphDualEdgeNode* nextOut;
};

// 顶点的数据结构
struct digraphDualVertexNode {
    int data; // 顶点的值
    digraphDualVertexNode* firstIn;
    digraphDualVertexNode* firstOut;
};

/*********************************************************************/
/* 用于拓扑排序而扩展的邻接表 */

// 顶点的数据结构
struct topVertexNode {
    int data; // 顶点的值
    int count; // 入度的值
    digraphEdgeNode* first; // 第一个边结点
};

/*********************************************************************/

// 图的数据结构
struct digraph {
    vector<topVertexNode*> vertex_list;
    int n; // 结点数量
    int e; // 边的数量
};

/*********************************************************************/

/* Minimum spanning tree */

// Grim
int Prim(vector<vector<int>>& graph);

/* 拓扑排序 */
int topSort(digraph& gInput);

/* Understand the relationship between queue and BFS*/
void graphTraverseBFS(vector<vector<int>>& matrix);

#endif //DATA_STRUCTURE_LEARN_GRAPH_H
