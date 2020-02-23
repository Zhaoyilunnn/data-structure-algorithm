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
    if (NULL != root->m_left)
        preorderRecursive(root->m_left);
    if (NULL != root->m_right)
        preorderRecursive(root->m_right);
}

void preorderNonrecursive(treeNode* root) {
    cout << "Start preorder traverse (nonrecursive)\n" ;
    vector<treeNode*> vStack;
    vStack.push_back(root);
    treeNode* p = NULL;
    int top = 0; // stack top
    while (!vStack.empty()) {
        p = vStack[top];
        top--;
        vStack.pop_back();
        p->Visit();
        if (NULL != p->m_right) {
            top++;
            vStack.push_back(p->m_right);
        }
        if (NULL != p->m_left) {
            top++;
            vStack.push_back(p->m_left);
        }
    }
}

void inorderRecursive(treeNode* root) {
    if (NULL != root->m_left)
        inorderRecursive(root->m_left);
    root->Visit();
    if (NULL != root->m_right)
        inorderRecursive(root->m_right);
}

void inorderNonrecursive(treeNode* root) {
    cout << "Start inorder traverse (nonrecursive)\n";
    vector<treeNode*> vStack;
    vStack.push_back(root);
    treeNode* p = root;
    int top = 0; // stack top
    while (!vStack.empty()) {
        while (NULL != p->m_left) {
            top++;
            vStack.push_back(p->m_left);
            p = p->m_left;
        }
        p = vStack[top];
        top--;
        vStack.pop_back();
        p->Visit();
        if (NULL != p->m_right) {
            top++;
            vStack.push_back(p->m_right);
            p = p->m_right;
        }
    }
}

void postorderRecursive(treeNode* root) {
    if (NULL != root->m_left)
        postorderRecursive(root->m_left);
    if (NULL != root->m_right)
        postorderRecursive(root->m_right);
    root->Visit();
}

void postorderNonrecursive(treeNode* root) {
    cout << "Start postorder traverse (nonrecursive)\n";
    vector<treeNode*> vStack;
    vector<treeNode*> vStackOut;
    vStack.push_back(root);
    treeNode* p = NULL;
    int top = 0; // stack top
    while (!vStack.empty()) {
        p = vStack[top];
        top--;
        vStack.pop_back();
        vStackOut.push_back(p);
        if (NULL != p->m_left) {
            top++;
            vStack.push_back(p->m_left);
        }
        if (NULL != p->m_right) {
            top++;
            vStack.push_back(p->m_right);
        }
    }
    for (int i = int(vStackOut.size()-1); i >= 0 ; i--) {
        vStackOut[i]->Visit();
    }
}

void level(treeNode* root) {
    cout << "Start lever traversal\n";
    vector<treeNode*> vQueue;
    vQueue.push_back(root);
    treeNode* p = NULL;
    int front = 0;
    while (front != -1) {
        p = vQueue[front];
        front--;
        vQueue.pop_back();
        p->Visit();
        if (NULL != p->m_left) {
            vQueue.insert(vQueue.begin(), p->m_left);
            front++;
        }
        if (NULL != p->m_right) {
            vQueue.insert(vQueue.begin(), p->m_right);
            front++;
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
