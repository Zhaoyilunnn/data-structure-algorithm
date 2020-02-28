//
//  struc_func.hpp
//  data_structure_study
//
//  Created by zyl on 2019/11/29.
//  Copyright © 2019 zyl. All rights reserved.
//

#ifndef struc_func_h
#define struc_func_h

#include <iostream>
#include <vector>
using namespace std;

class treeNode {
    
public:
    int m_val = 0;
    treeNode* m_left = nullptr;
    treeNode* m_right= nullptr;
    
    // construct
    explicit treeNode(int val) {
        m_val = val;
    }
    
    // deconstruct
    ~treeNode() {
        delete m_left;
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

// 遍历线索二叉树 --> to do
void inOrderTraverse(treeNodeThread* Head);

// 从层次遍历序列和中序遍历序列得到二叉树
treeNode* buildTree(vector<int>& level, vector<int>& inorder, int L, int R);
#endif /* struc_func_h */
