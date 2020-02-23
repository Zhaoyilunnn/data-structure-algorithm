//
//  struc_func.hpp
//  data_structure_study
//
//  Created by zyl on 2019/11/29.
//  Copyright © 2019 zyl. All rights reserved.
//

#ifndef struc_func_hpp
#define struc_func_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class treeNode {
    
public:
    int m_val = 0;
    treeNode* m_left = NULL;
    treeNode* m_right= NULL;
    
    // construct
    treeNode(int val) {
        m_val = val;
    }
    
    // deconstruct
    ~treeNode() {
        if (NULL != m_left)
            delete m_left;
        if (NULL != m_right)
            delete m_right;
        m_val = 0;
    }
    
    // visit
    void Visit() {
        cout << "Visit: " << m_val << "\n";
    }
};

// 线索二叉树
struct treeNodeThread {
    int item = 0;
    int lFlag = 0;  // if lFlag == 1, then left is previous node
    int rFlag = 0;  // if rFlag == 1, then right is next node
    treeNodeThread* left = nullptr;
    treeNodeThread* right = nullptr;
};

// Preorder traversal
void preorderRecursive(treeNode* root);
void preorderNonrecursive(treeNode* root);
// Inorder traversal
void inorderRecursive(treeNode* root);
void inorderNonrecursive(treeNode* root);
// Postorder traversal
void postorderRecursive(treeNode* root);
void postorderNonrecursive(treeNode* root);
// Level traversal
void level(treeNode* root);

// 线索二叉树 --> 中序遍历建立线索
void inOrderBuildThread(treeNodeThread* root, treeNodeThread*& pre);

// 遍历线索二叉树哦
void inOrderTraverse(treeNodeThread* Head);

//treeNode* creatTree(vector<int>& treeVals);

#endif /* struc_func_hpp */
