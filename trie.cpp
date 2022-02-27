#include <iostream>
#include <vector>
#include <string>
#include <memory>

#define CHAR_NUM 26

class Node {
public:
    Node() {
        char_vec.resize(CHAR_NUM, 0);    
    }

    ~Node() {

    }

    std::vector<int> char_vec;
};

class Trie {
public:
    Trie() {
        auto node = std::make_shared<Node>();
        trie.push_back(node);
    }

    std::vector<std::shared_ptr<Node> > trie;
    
    void insert(const std::string& word) {
        size_t length = word.size();
        int nid = 1;
        for (size_t i = 0; i < length; i++) {
            int c_id = word[i] - 'a';
            if (!trie[nid-1]->char_vec[c_id]) {
                auto node = std::make_shared<Node>();
                trie.push_back(node);
                trie[nid-1]->char_vec[c_id] = trie.size();
            }
            nid = trie[nid-1]->char_vec[c_id];
        }
    }

    bool find(const std::string& word) {
        size_t length = word.size();
        int nid = 1;
        for (size_t i = 0; i < length; i++) {
            int c_id = word[i] - 'a';
            if (!trie[nid-1]->char_vec[c_id]) {
                return false;
            }
            nid = trie[nid-1]->char_vec[c_id];
        }
        return true;
    }

    void print() {
        for (auto& n : trie) {
            for (int i = 0; i < CHAR_NUM; i++) {
                std::cout << n->char_vec[i] << " ";
            }
            std::cout << std::endl;
        }
    }

};

int main() {
    std::vector<std::string> test_words = {
        "abcd",
        "efgh",
        "ada",
        "aaa",
        "iill"
    };

    auto trie = std::make_shared<Trie>();
    
    for (auto& w : test_words) {
        trie->insert(w);
    }
    
    trie->print();

    return 0;
}
