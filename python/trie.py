import sys

class Trie:
    """ A naive implementation of trie """
    
    def __init__(self):
        self.trie = {}

    def insert(self, word):
        """ Insert a word to trie """
        node = self.trie
        for w in word:
            if w not in node:
                node[w] = {} 
            node = node[w]

    def find(self, word):
        """ Find a word in a trie """
        node = self.trie
        for w in word:
            if w not in node:
                return False
            node = node[w]

        return True


def test():
    word_list = {"abc", "def", "acd", "adasdfadl", "dog", "document", "exact"}
    trie = Trie()
    for w in word_list:
        trie.insert(w)
    print(trie.trie)

    print("abcd in trie? {}".format(trie.find("abcd")))
    print("exact in trie? {}".format(trie.find("exact")))
    

if __name__ == '__main__':
    test()
