//
//  main.cpp
//  data_structure_study
//
//  Created by zyl on 2019/11/29.
//  Copyright © 2019 zyl. All rights reserved.
//

#include "struc_func.hpp"

int main(int argc, const char * argv[]) {
    // create a tree for test
    treeNode* root = new treeNode(0);
    root->m_left = new treeNode(1);
    root->m_right = new treeNode(2);
    root->m_left->m_left = new treeNode(3);
    root->m_right->m_left = new treeNode(4);
    
    preorderNonrecursive(root);
    postorderNonrecursive(root);
}
