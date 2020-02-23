//
//  main.cpp
//  data_structure_study
//
//  Created by zyl on 2019/11/29.
//  Copyright © 2019 zyl. All rights reserved.
//

#include "struc_func.h"

int main(int argc, const char * argv[]) {
    // create a tree for test
//    treeNode* root = new treeNode(0);
//    root->m_left = new treeNode(1);
//    root->m_right = new treeNode(2);
//    root->m_left->m_left = new treeNode(3);
//    root->m_left->m_right = new treeNode(4);
//    root->m_right->m_left = new treeNode(5);
//    root->m_right->m_right = new treeNode(6);
//    // start traverse
//    cout << "Start preorder traverse\n";
//    preorderRecursive(root);
//    cout << "Start inorder traverse\n";
//    inorderRecursive(root);
//    cout << "Start postorder traverse\n";
//    postorderRecursive(root);
//    preorderNonrecursive(root);
//    inorderNonrecursive(root);
//    postorderNonrecursive(root);
//    level(root);

    // -------------------------- test thread tree ------------------------------------
    treeNodeThread root = {
            1,
            0,
            0,
            nullptr,
            nullptr
    };

    treeNodeThread root_left = {
            2,
            0,
            0,
            nullptr,
            nullptr
    };

    treeNodeThread root_left_left = {
            3,
            0,
            0,
            nullptr,
            nullptr
    };

    treeNodeThread root_left_right = {
            4,
            0,
            0,
            nullptr,
            nullptr
    };

    treeNodeThread root_right = {
            5,
            0,
            0,
            nullptr,
            nullptr
    };

    treeNodeThread root_right_right = {
            6,
            0,
            0,
            nullptr,
            nullptr
    };

    // assign value
    root.left = &root_left;
    root.right = &root_right;
    root_left.left = &root_left_left;
    root_left.right = &root_left_right;
    root_right.right = &root_right_right;
    treeNodeThread Head = {
            0,
            0,
            0,
            nullptr,
            nullptr
    };
    treeNodeThread* H = &Head;
    treeNodeThread* pRoot = &root;
    inOrderBuildThread(pRoot, H);

    // --------------------------- test thread tree ---------------------------------------
    return 0;
}
