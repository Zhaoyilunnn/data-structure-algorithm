//
//  struc_func.cpp
//  data_structure_study
//
//  Created by zyl on 2019/11/29.
//  Copyright © 2019 zyl. All rights reserved.
//

#include "struc_func.hpp"
//#include <stack> // currently self define a stack using vector

void preorderRecursive(treeNode* root) {
    
}

void preorderNonrecursive(treeNode* root) {
    cout << "Start preorder traverse\n" ;
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
    
}

void inorderNonrecursive(treeNode* root) {
    
}

void postorderRecursive(treeNode* root) {
    
}

void postorderNonrecursive(treeNode* root) {
    cout << "Start postorder traverse\n" ;
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
