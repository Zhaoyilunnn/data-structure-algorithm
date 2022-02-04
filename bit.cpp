/* Binary Indexed Tree */

#include <iostream>
#include <vector>
#include <fstream>


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
            int step = lowbit(i);
            for (int j = i-step; j < i; j++) {
                _tree[i] += nums[j];
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

private:
    int _n;
    std::vector<int> _tree;
};


int main() {
    std::vector<int> nums = {1,2,3,4,5,6,7,8};
    BIT bit(nums);
    bit.print();
    std::cout << bit.query(6) << std::endl;
    bit.add(1,1);
    bit.print();
    return 0;
}
