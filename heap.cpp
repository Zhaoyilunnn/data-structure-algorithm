// A simple big root heap

#include <iostream>
#include <vector>
#include <climits>
#include <string>

using namespace std;

class Heap {
public:
    explicit Heap(uint32_t max_size) {
        _size = max_size;
        _vec.resize(max_size, 0);
    }

    bool empty() {
        return _cur_size <= 0 ? true : false;
    }

    void push(int val) {
        if (_cur_size == _size) {    
            if (val < _vec[0]) {
                _vec[0] = val;
                adjust(0);
            }
        } else {
            _vec[_cur_size] = val;
            _cur_size++;
            if (_cur_size == _size) {
                build_heap();
            }
        }
    }

    int pop() {
        if (_cur_size <= 0) {
            return -1;
        }
        int res = _vec[0];
        int temp = _vec[_cur_size-1];
        _vec[_cur_size-1] = _vec[0];
        _vec[0] = temp;
        _cur_size--;
        adjust(0);
        return res;
    }

    uint32_t size() {
        return _cur_size;
    }
    
    void debug() {
        for (auto i : _vec) {
            cout << i << " ";    
        }    
        cout << endl;
    }

private:
    // get left child idx
    int get_lc(uint32_t idx) {
        return 2*idx+1 >= _cur_size ? -1 : 2*idx+1;
    }
    
    // get right child idx
    int get_rc(uint32_t idx) {
        return 2*idx+2 >= _cur_size ? -1 : 2*idx+2;
    }
    
    // judge whether need drop, return the swap idx
    int need_drop(uint32_t idx) {
        int lc_idx = get_lc(idx), rc_idx = get_rc(idx);
        if (lc_idx < 0 && rc_idx < 0) { // leaf node
            return -1;
        }

        int lc_val = lc_idx >= 0 ? _vec[lc_idx] : INT_MIN;
        int rc_val = rc_idx >= 0 ? _vec[rc_idx] : INT_MIN;
        
        uint32_t res = lc_val > rc_val ? lc_idx : rc_idx;

        return _vec[idx] < _vec[res] ? res : -1;
    }

    void build_heap() {
        int start = _size / 2 - 1;
        while (start >= 0) {
            adjust(start);
            start--;
        }
    }

    void adjust(uint32_t idx) {
        //cout << "adjusting:_vec:" << idx << endl;
        auto swap_idx = need_drop(idx);
        while (swap_idx >= 0) {
            //cout << "swapping:" << swap_idx << endl;
            auto tmp = _vec[idx];
            _vec[idx] = _vec[swap_idx];
            _vec[swap_idx] = tmp;
            //debug();
            idx = swap_idx;
            swap_idx = need_drop(idx);
        } 
    }

private:
    uint32_t _size {0};
    uint32_t _cur_size {0};

    vector<int> _vec;

};

int main() {
    vector<int> test_seq;
    int vlen, h_size, tmp;
    cout << "Please input heap size" << endl;
    cin >> h_size;
    cout << "Please input vector size" << endl;
    cin >> vlen;
    cout << "Please input a vector" << endl;

    for (int i = 0; i < vlen; i++) {
        cin >> tmp;
        test_seq.push_back(tmp);
    }
    
    Heap myheap(h_size);
    for (auto i : test_seq) {
        myheap.push(i);
        //myheap.debug();
    }
    
    while (!myheap.empty()) {
        myheap.debug();
        cout << myheap.pop() << endl;
    }

    return 0;
}
