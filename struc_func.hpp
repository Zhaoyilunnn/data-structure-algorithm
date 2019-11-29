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

// Preorder traversal
void preorderRecursive(treeNode* root);
void preorderNonrecursive(treeNode* root);
// Inorder traversal
void inorderRecursive(treeNode* root);
void inorderNonrecursive(treeNode* root);
// Postorder traversal
void postorderRecursive(treeNode* root);
void postorderNonrecursive(treeNode* root);

//treeNode* creatTree(vector<int>& treeVals);

#endif /* struc_func_hpp */
