//
//  struc_func.hpp
//  data_structure_study
//
//  Created by zyl on 2019/11/29.
//  Copyright © 2019 zyl. All rights reserved.
//

#ifndef DATA_STRUCTURE_LEARN_TREE_H
#define DATA_STRUCTURE_LEARN_TREE_H

#include "common.h"

/****************************************************************/
/* tree */
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

/****************************************************************/





/***************************************************************/
/* Traverse of binary tree */
// Preorder traversal
void preorderRecursive(treeNode* root);
void preorderIterative(treeNode* root);
void MorrisTraverse(treeNode* root);
// Inorder traversal
void inorderRecursive(treeNode* root);
void inorderIterative(treeNode* root);
// Postorder traversal
void postorderRecursive(treeNode* root);
void postorderIterative(treeNode* root);
// Level traversal
void level(treeNode* root);
void level_plus(treeNode* root); // improved the simplicity of "level" function

/***************************************************************/


/***************************************************************/
/* Thread binary tree */
// 线索二叉树 --> 中序遍历建立线索
void inOrderBuildThread(treeNodeThread* root, treeNodeThread*& pre);
void inOrderBuildThreadNonRecursive(treeNodeThread* root, treeNodeThread* &pre);
// 遍历线索二叉树 --> to do
void inOrderTraverse(treeNodeThread* Head);
/***************************************************************/


/***************************************************************/
/* From sequence to binary tree */
// 从层次遍历序列和中序遍历序列得到二叉树
treeNode* buildTree(vector<int>& level, vector<int>& inorder, int L, int R);
/***************************************************************/


#endif //DATA_STRUCTURE_LEARN_GRAPH_H
