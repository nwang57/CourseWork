"""
    Mono queue is a queue where has three operations:
    push: push an element into the queue O(1)
    pop: pop an element out of the queue O(1)
    max_item: return the maximum element O(1)
"""

class MaxStack(object):
    def __init__(self):
        self.stack = []

    def empty(self):
        return True if not self.stack else False

    def push(self, n):
        if not self.stack:
            self.stack.insert(0,(n, n))
        else:
            if n > self.stack[0][1]:
                self.stack.insert(0,(n, n))
            else:
                self.stack.insert(0,(n, self.stack[0][1]))

    def pop(self):
        if self.stack:
            return self.stack.pop()[0]

    def max_item(self):
        if self.stack:
            return self.stack[0][1]


class Monoqueue(object):
    def __init__(self):
        self.push_stack = MaxStack()
        self.pop_stack = MaxStack()

    def push(self, n):
        self.push_stack.push(n)

    def pop(self):
        if self.pop_stack.empty():
            while not self.push_stack.empty():
                self.pop_stack.push(self.push_stack.pop())
        return self.pop_stack.pop()

    def max_item(self):
        return max(self.push_stack.max_item(), self.pop_stack.max_item())

    def empty(self):
        return self.push_stack.empty() and self.pop_stack.empty()
