class UF:
    def __init__(self, n):
        self.parent = list(range(n))
    
    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]
    
    def join(self, x, y):
        self.parent[self.find(x)] = self.find(self.parent[y])



        