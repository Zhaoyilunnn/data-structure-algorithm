//
//  struc_func.cpp
//  data_structure_study
//
//  Created by zyl on 2019/11/29.
//  Copyright © 2019 zyl. All rights reserved.
//

#include "tree.h"
//#include <stack> // currently self define a stack using vector

void preorderRecursive(treeNode* root) {
    root->Visit();
    if (root->m_left)
        preorderRecursive(root->m_left);
    if (root->m_right)
        preorderRecursive(root->m_right);
}

void preorderIterative(treeNode* root) {
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


/**
 * Morris traverse
 *  Principle: 1. current node is curr
 *             2. if curr.left; then find the most right node, denoted as most_right
 *                  a. if !most_right.right; then most_right.right = curr
 *                  b. if most_right.right; then most_right.right = null
 * @param root
 */
void MorrisTraverse(treeNode* root) {
    treeNode* curr = root;
    while (curr) {
//        cout << curr->m_val << endl;
        treeNode* most_right;
        if (curr->m_left) {
            most_right = curr->m_left;
            while (most_right->m_right && most_right->m_right != curr) {
                if (most_right->m_right != curr) most_right = most_right->m_right;
            }
            if (most_right->m_right) {
//                cout << curr->m_val << " ";  // inorder
                curr = curr->m_right;
            }
            else {
                cout << curr->m_val << " ";   // preorder
                most_right->m_right = curr;
                curr = curr->m_left;
            }
        } else {
            cout << curr->m_val << " ";
            curr = curr->m_right;
        }
    }
    cout << endl;
}

void inorderRecursive(treeNode* root) {
    if (root->m_left)
        inorderRecursive(root->m_left);
    root->Visit();
    if (root->m_right)
        inorderRecursive(root->m_right);
}

void inorderIterative(treeNode* root) {
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

void postorderIterative(treeNode* root) {
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

/**************************************************************************/
/* To do: implement non-traverse method */
/**************************************************************************/
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


/**********************************************************************************************************************/
/**
 * Segment tree start
 */
SegmentTree::SegmentTree() {
    root = new SegmentTreeNode(0);
}

SegmentTree::SegmentTree(const vector<int> &nums) {
    root = new SegmentTreeNode(0);
    BuildSegmentTree(nums);
}

SegmentTree::~SegmentTree() {
    DestroySegmentTree(root);
}

void SegmentTree::BuildSegmentTree(const vector<int>& nums) {
    int l = 0, r = (int) nums.size() - 1;
    BuildHelper(nums, l, r, root);
}

int SegmentTree::GetSum(int l, int r) {
    return GetSumHelper(root, l, r);
}

void SegmentTree::BuildHelper(const vector<int>& nums, int l, int r, SegmentTreeNode* node) {
    node->l = l;
    node->r = r;
    if (l == r) {
        node->val = nums[l];
        return;
    }
    int sum_val = 0;
    for (int i = l; i <= r; i++) {
        sum_val += nums[i];
    }
    node->val = sum_val;
    int mid = l + (r - l) / 2;
    node->left = new SegmentTreeNode(0);
    node->right = new SegmentTreeNode(0);
    BuildHelper(nums, l, mid, node->left);
    BuildHelper(nums, mid + 1, r, node->right);
}

int SegmentTree::GetSumHelper(SegmentTreeNode *node, int l, int r) {
    if (node->l >= l && node->r <= r) {
        return node->val;
    }
    if (node->r < l || node->l > r) {
        return 0;
    }
    return GetSumHelper(node->left, l, r) + GetSumHelper(node->right, l, r);
}

void SegmentTree::DestroySegmentTree(SegmentTreeNode* node) {
    if (node) {
        DestroySegmentTree(node->left);
        DestroySegmentTree(node->right);
        delete node;
    }
}

/**********************************************************************************************************************/