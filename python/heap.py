import sys

# Helper funcitons

def left(x):
    return 2*x + 1

def right(x):
    return 2*x + 2

class Heap:
    """ A simple heap python implementation """
    max_size = 0
    size = 0
    tree = []

    def __init__(self, k):
        """ Init a heap from heap size 
            Currently not support init from a vector"""
        self.max_size = k
        self.tree = [-1] * k

    def empty(self):
        return self.size == 0

    def swap(self, idx1, idx2):
        tmp = self.tree[idx1]
        self.tree[idx1] = self.tree[idx2]
        self.tree[idx2] = tmp

    def do_swap(self, idx):
        c = self.tree[idx] # cur
        idx_l = left(idx)
        idx_r = right(idx)
        n_idx = -1 # next index
        n_val = c # next value
        if idx_l < self.size and n_val > self.tree[idx_l]:
            n_idx = idx_l
            n_val = self.tree[idx_l]
        if idx_r < self.size and n_val > self.tree[idx_r]:
            n_idx = idx_r
            n_val = self.tree[idx_r]
        if n_idx != idx and n_idx >= 0:
            self.swap(idx, n_idx)
        return n_idx
    
    def drop(self, idx):
        n_idx = self.do_swap(idx) 
        if n_idx != idx and n_idx >= 0:
            self.drop(n_idx)

    def up(self, idx):
        if (idx < 0):
            return 
        self.do_swap(idx)
        self.up((idx-1)/2)

    def debug(self):
        print(self.size)
        print(self.tree)

    def push(self, num):
        """ Push a value to a heap """
        if self.size == self.max_size:
            # Heap full
            if num > self.tree[0]:
                self.tree[0] = num
                self.drop(0)
        else:
            self.size += 1
            self.tree[self.size-1] = num
            self.up((self.size-1)/2)

    def pop(self):
        """ Pop and return front """
        if self.empty():
            return None
        res = self.tree[0]
        self.tree[0] = self.tree[self.size-1]
        self.size -= 1
        self.drop(0)
        return res
            

def topk():
    k = int(sys.argv[1])
    heap = Heap(k)
    for line in sys.stdin:
        num = int(line.strip())
        heap.push(num)
    
    while not heap.empty():
        yield heap.pop()


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: cat <file> | python {} <k>".format(sys.argv[0]))
        sys.exit(1)
    for n in topk():
        print(n)
