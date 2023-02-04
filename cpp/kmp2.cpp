#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> get_next(const string& pattern) {
    vector<int> next(pattern.size(), 0);

    for (size_t i = 1; i < pattern.size(); i++) {
        if (pattern[i] == pattern[next[i-1]]) {
            next[i] += next[i-1];
        }
    }

    return next;
}

void debug(const vector<int>& vec) {
    for (auto v : vec) {
        cout << v << " ";
    }
    cout << endl;
}

vector<int> kmp(const string& pattern, const string& target) {
    vector<int> next = get_next(pattern);
    debug(next);
    
    size_t i = 0, j = 0;
    vector<int> res;


    while (i < target.size()) {
        while (j < pattern.size() 
                && i < target.size() 
                && pattern[j] == target[i]) {
            cout << i << " " << j << endl;
            i++;
            j++;
        }
        
        if (j > 0) {
            if (j == pattern.size()) {
                res.push_back(i);
            }
            j = next[j - 1];
        } else {
            i++;
        }
    }

    return res;
}


int main() {

    cout << "Please input pattern:" << endl;
    string pattern;
    getline(cin, pattern);
    cout << "Please input target: " << endl;
    string target;
    getline(cin, target);
    cout << "pattern:" << pattern << " target:" << target << endl; 

    auto match = kmp(pattern, target);
    for (auto m : match) cout << m << endl;

    return 0;
}
