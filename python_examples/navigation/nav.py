import namemap
import time
adjacencies = [
    #0 1 2 3 4
    [0,1,0,1,0],#0
    [1,0,1,0,0],#1
    [0,1,0,1,1],#2
    [1,0,1,0,1],#3
    [0,0,1,1,0],#4

]

positions = [
    #x y
    [0,0],#0
    [0,-100],#1
    [50,-80],#2
    [30,0],#3
    [100,20],#3
]

class myQueue:
    def __init__(self):
        self.queueRep=[]
    def queue(self,num):
        self.queueRep.append(num)
    def dequeue(self):
        ret = self.queueRep[0]
        self.queueRep.pop(0)
        return ret
    def showQ(self):
        print(self.queueRep)
    def qSize(self):
        return len(self.queueRep)
    def qGet(self,pos):
        return self.queueRep[pos]

# use BFS (shortest path)

distances = [float('inf'),float('inf'),float('inf'),float('inf'),float('inf')]

start = 0
prevDist = 0

q = myQueue()
q.queue(start)
distances[0] = 0
done = []
prevPath = 1

#paths1.append([0])

while(q.qSize() != 0):
    curr = q.qGet(0)
    for destID in range(len(adjacencies[curr])):
        adjValue = adjacencies[curr][destID]
        dist = adjValue + prevDist
        if (adjValue>0):
            skip = False
            for adjValue in done:
                if adjValue == destID:
                    skip = True
            if not(skip):
                q.queue(destID)
        if (adjValue > 0) & (distances[destID]>dist):
            distances[destID] = dist
            #paths1[destID] = 
    q.showQ()
    done.append(q.dequeue())
    q.showQ()
    prevDist = distances[curr]

print(distances)
#print(namemap.names)
#print(len(namemap.names))
