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

#define DOUBLE(x) (x+x)
#define MIN(x, y) x < y ? x : y

int main(int argc, const char * argv[]) {

    struct test{
        long a;
        short b;
    };

    cout << sizeof(test) << endl;
    int b = 5*DOUBLE(5);
    int c = MIN(3, 2);

    vector<vector<int>> graph = {{0, 1, 2, 3, 0, 0},
                                 {1, 0, 7, 0, 8, 0},
                                 {2, 7, 0, 6, 4, 0},
                                 {3, 0, 6, 0, 0, 5},
                                 {0, 8, 4, 0, 0, 9},
                                 {0, 0, 0, 5, 9, 0}};
    int res = Prim(graph);

    return 0;
}
