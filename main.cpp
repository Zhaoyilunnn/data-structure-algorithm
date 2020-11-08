//
//  main.cpp
//  data_structure_study
//
//  Created by zyl on 2019/11/29.
//  Copyright © 2019 zyl. All rights reserved.
//

#include "tree.h"
#include "graph.h"
#include "sort.h"
#include "algorithm.h"

#define DOUBLE(x) (x+x)
#define MIN(x, y) x < y ? x : y



int main(int argc, const char * argv[]) {

    vector<int> nums = {1, 3, 5, 7, 9, 11};
    SegmentTreeNode* root = buildSegmentTree(nums);
    destroySegmentTree(root);
    return 0;
}
