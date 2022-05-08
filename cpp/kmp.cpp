#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Meaning of next: when we pat[1:i] matched
// we just need to restart from pat[next[i]], 
// since pat[i-next[i]:i] already matched
vector<int> get_next(const string& pat) { 
    int n = pat.size();
    vector<int> next(n, 0);
    if (pat.empty()) {
        return next;
    }

    for (int i = 1; i < n; i++) {
        if (pat[i] == pat[next[i-1]]) {
            next[i] = next[i-1] + 1;
        }
    }

    return next;
}

vector<int> kmp(const string& str, const string& pat) { 
    vector<int> res;
    if (str.empty() || pat.empty()) {
        return res;
    }

    vector<int> next = get_next(pat);
    
    int p1 = 0, p2 = 0;
    int n1 = str.size(), n2 = pat.size();

    while (p1 < n1) {
        while (str[p1] == pat[p2]) {
            if (p2 == n2-1) {
                res.push_back(p1 - n2 + 1);
                break;
            }
            p1++;
            p2++;
        }
        
        if (p2 > 0) { // Already matched sth
            p2 = next[p2-1];
        } else { // Else find next position of str
            p1++;
        }
    }

    return res;
}

int main() {
    
    string str, pat;

    cout << "Please input a string" << endl;
    getline(cin, str);
    cout << "Please input a pattern" << endl;
    getline(cin, pat);

    vector<int> pos = kmp(str, pat);
    
    cout << "Find positions: ";
    for (auto& i : pos) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
