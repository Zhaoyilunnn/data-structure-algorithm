// Disjoint Set Union
// With Path compression
// TODO(yilun): Deletion?

#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
public:
    vector<int> _dsu;
    
    // Initialization
    UnionFind(int n) : _dsu(n, 0) {
        for (int i = 0; i < n; i++) {
            _dsu[i] = i;
        }
    }
    
    // Find root of a node
    int find(int x) {
        if (_dsu[x] != x) {
            _dsu[x] = find(_dsu[x]); // Path Compression
        }
        return _dsu[x];
    }

    // Merge two nodes
    void join(int x, int y) {
        int father_x = find(x);
        int father_y = find(y);

        if (father_x == father_y) {
            return;
        }

        _dsu[father_x] = father_y;
    }

};

int main() {
    
    UnionFind uf(5);
    uf.join(1, 2);
    uf.join(3, 2);
    uf.join(0, 4);

    cout << "Root of node 1: " << uf.find(1) << endl;
    cout << "Root of node 3: " << uf.find(3) << endl;
    cout << "Root of node 4: " << uf.find(4) << endl;

    cout << "Merging node 3 and node 4 ..." << endl;
    uf.join(3, 4);
    cout << "Root of node 1: " << uf.find(1) << endl;
    cout << "Root of node 3: " << uf.find(3) << endl;
    cout << "Root of node 4: " << uf.find(4) << endl;

    return 0;
}
