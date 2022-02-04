/* Binary Indexed Tree */

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <unordered_map>

static inline int lowbit(int x) {
    return x & -x;
}

class BIT {
public:
    
    // init from nums (a[1:_n])
    explicit BIT(const std::vector<int>& nums) {
        _n = nums.size() + 1;
        _tree.resize(_n, 0);

        int i = 1;
        while (i < _n) {
            _tree[i] += nums[i-1];
            int j = i + lowbit(i); // find father node
            if (j < _n) {
                _tree[j] += _tree[i];
            }
            i++;
        }
    }

    ~BIT() {}

    void print() {
        for (auto& i : _tree) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    
    // add k to a[x]
    void add(int x, int k) {
        while (x < _n) {
            _tree[x] += k;
            x += lowbit(x);
        }
    }
    
    // get prefix sum of a[1:x]
    int query(int x) {
        int res = 0;
        while (x > 0) {
            res += _tree[x];
            x -= lowbit(x);
        }    
        return res;
    }
    
    // get kth smallest value
    // a[i] represent the count of i
    int kth(int k) {
        int res = 0, cnter = 0;
        for (int i = std::log2(_n); ~i; i--) {
            res += 1 << i;
            if (res >= _n || cnter + _tree[res] >= k) { // 
                res -= 1 << i;
            } else {
                cnter += _tree[res];
            }
        }
        return res + 1;
    }

private:
    int _n;
    std::vector<int> _tree;
};

int main() {
    std::vector<int> nums = {1,2,3,4,5,6,7,8};

    // build
    BIT bit(nums);
    bit.print();

    // query
    std::cout << bit.query(6) << std::endl;

    // add
    bit.add(1,1);
    bit.print();

    // get kth smallest value
    nums = {1,1,2,1,2,1};
    BIT bit2(nums);
    std::cout << bit2.kth(3) << std::endl;

    return 0;
}
