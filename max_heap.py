from types import StringType
from collections import Iterable

class MaxHeap(object):
    def __init__(self):
        self.array = []
        self.cur_size = 0

    def heapify(self, item_list):
        self.array = item_list
        self.cur_size = len(item_list)
        for i in range(self.cur_size-1, -1, -1):
            self._heapify(i)

    def push(self, item):
        """
            push an item into the heap, re-arange the heap according to the key
        """
        self.array.append(item)
        self.cur_size += 1
        cur = self.cur_size - 1
        while (cur != 0):
            p = cur >> 1
            if self.get_key(self.array[cur]) > self.get_key(self.array[p]):
                self.swap(cur, p)
            else:
                return
            cur = p


    def pop(self):
        """
            pop the item with largest key value
        """
        if self.cur_size == 0:
            raise ValueError("No elements in the heap")
        ret = self.array[0]
        self.array[0] = self.array[self.cur_size-1]
        self.array.pop()
        self.cur_size -= 1
        self._heapify(0)
        return ret

    def top(self):
        """
            peek the top of the heap
        """
        if self.cur_size == 0:
            raise ValueError("No elements in the heap")
        return self.array[0]

    def size(self):
        """
            return the size of the heap
        """
        return self.cur_size

    def get_key(self, item):
        if isinstance(item, Iterable) and not isinstance(item, StringType):
            return item[0]
        else:
            return item

    def swap(self, i, j):
        tmp = self.array[i]
        self.array[i] = self.array[j]
        self.array[j] = tmp

    def _heapify(self, node):
        if node >= self.cur_size:
            return
        l = (node << 1) + 1
        r = (node << 1) + 2
        if l >= self.cur_size and r >= self.cur_size:
            return
        elif r >= self.cur_size:
            # only left child
            if self.get_key(self.array[l]) > self.get_key(self.array[node]):
                self.swap(l, node)
        else:
            # both child alive
            if self.get_key(self.array[node]) >= self.get_key(self.array[l]) and self.get_key(self.array[node]) >= self.get_key(self.array[r]):
                return
            if self.get_key(self.array[l]) >= self.get_key(self.array[r]):
                self.swap(l, node)
                self._heapify(l)
            else:
                self.swap(r, node)
                self._heapify(r)

if __name__=="__main__":
    hp = MaxHeap()
    items = [4,3,6,5,1,8,10,4,5,2,1,7]
    hp.heapify(items)
    hp.push(20)
    for i in range(hp.size()):
        print(hp.pop())
