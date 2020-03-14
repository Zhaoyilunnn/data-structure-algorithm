//
//  struc_func.cpp
//  data_structure_study
//
//  Created by zyl on 2019/11/29.
//  Copyright © 2019 zyl. All rights reserved.
//

#include "struc_func.h"
//#include <stack> // currently self define a stack using vector

void preorderRecursive(treeNode* root) {
    root->Visit();
    if (root->m_left)
        preorderRecursive(root->m_left);
    if (root->m_right)
        preorderRecursive(root->m_right);
}

void preorderNonrecursive(treeNode* root) {
    cout << "Start preorder traverse (nonrecursive)\n" ;
    vector<treeNode*> vStack;
    vStack.push_back(root);
    treeNode* p = nullptr;
    int top = 0; // stack top
    while (!vStack.empty()) {
        p = vStack[top];
        top--;
        vStack.pop_back();
        p->Visit();
        if (p->m_right) {
            top++;
            vStack.push_back(p->m_right);
        }
        if (p->m_left) {
            top++;
            vStack.push_back(p->m_left);
        }
    }
}

void inorderRecursive(treeNode* root) {
    if (root->m_left)
        inorderRecursive(root->m_left);
    root->Visit();
    if (root->m_right)
        inorderRecursive(root->m_right);
}

void inorderNonrecursive(treeNode* root) {
    cout << "Start inorder traverse (nonrecursive)\n";
    vector<treeNode*> vStack;
    vStack.push_back(root);
    treeNode* p = root;
    int top = 0; // stack top
    while (!vStack.empty()) {
        while (p->m_left) {
            top++;
            vStack.push_back(p->m_left);
            p = p->m_left;
        }
        p = vStack[top];
        top--;
        vStack.pop_back();
        p->Visit();
        if (p->m_right) {
            top++;
            vStack.push_back(p->m_right);
            p = p->m_right;
        }
    }
}

void postorderRecursive(treeNode* root) {
    if (root->m_left)
        postorderRecursive(root->m_left);
    if (root->m_right)
        postorderRecursive(root->m_right);
    root->Visit();
}

void postorderNonrecursive(treeNode* root) {
    cout << "Start postorder traverse (nonrecursive)\n";
    vector<treeNode*> vStack;
    vector<treeNode*> vStackOut;
    vStack.push_back(root);
    treeNode* p = nullptr;
    int top = 0; // stack top
    while (!vStack.empty()) {
        p = vStack[top];
        top--;
        vStack.pop_back();
        vStackOut.push_back(p);
        if (p->m_left) {
            top++;
            vStack.push_back(p->m_left);
        }
        if (p->m_right) {
            top++;
            vStack.push_back(p->m_right);
        }
    }
    for (int i = int(vStackOut.size()-1); i >= 0 ; i--) {
        vStackOut[i]->Visit();
    }
}

void level(treeNode* root) {
    cout << "Start level traversal\n";
    vector<treeNode*> vQueue;
    vQueue.push_back(root);
    treeNode* p = nullptr;
    int front = 0;
    while (front != -1) {
        p = vQueue[front];
        front--;
        vQueue.pop_back();
        p->Visit();
        if (p->m_left) {
            vQueue.insert(vQueue.begin(), p->m_left);
            front++;
        }
        if (p->m_right) {
            vQueue.insert(vQueue.begin(), p->m_right);
            front++;
        }
    }
}

void level_plus(treeNode* root) {
    cout << "Start level traversal" << endl;
    vector<treeNode*> vctQueue;
    vctQueue.push_back(root);
    while (!vctQueue.empty()) {
        int size = vctQueue.size();
        for (int i = 0; i < size; i++) {
            if (vctQueue[0]->m_left)
                vctQueue.push_back(vctQueue[0]->m_left);
            if (vctQueue[0]->m_right)
                vctQueue.push_back(vctQueue[0]->m_right);
            vctQueue[0]->Visit();
            vctQueue.erase(vctQueue.begin());
        }
    }
}

void inOrderBuildThread(treeNodeThread* root, treeNodeThread* &pre) {
    if (root->left)
        inOrderBuildThread(root->left, pre);
    if (!root->left) {
        root->lFlag = 1;
        root->left = pre;
    }
    if (!pre->right){
        pre->rFlag = 1;
        pre->right = root;
    }
    pre = root;
    if (root->right)
        inOrderBuildThread(root->right, pre);
}

int search(vector<int>& dest, int val, int L, int R) {
    for (int i = L; i <= R; i++) {
        if (dest[i] == val)
            return i;
    }
    return -1;
}

void sublevel(vector<int>& sublevel, vector<int>& level, vector<int>& inorder, int L, int R) {
    for (int i : level) {
        if (search(inorder, i, L, R) >= 0)
            sublevel.push_back(i);
    }
}

// Here L is the start position and R is the end position
// The operating principle is as follows
//      1. Find the root node from the inorder sequence --> the inorder[0]
//      2. Based on the root node, we can determine the root's left child nodes and right child nodes
//      3. Find the left level nodes right level nodes in level and then recursively execute buildTree function
treeNode* buildTree(vector<int>& level, vector<int>& inorder, int L, int R) {
    if (L > R)
        return nullptr;
    auto* root = new treeNode(level[0]);
    int i = search(inorder, level[0], L, R);
    vector<int> lLevel, rLevel;
    int lR = i-1;
    int rL = i+1;
    sublevel(lLevel, level, inorder, L, lR);
    sublevel(rLevel, level, inorder, rL, R);
    root->m_left = buildTree(lLevel, inorder, L, lR);
    root->m_right = buildTree(rLevel, inorder, rL, R);
    return root;
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

