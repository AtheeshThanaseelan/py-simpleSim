import nav
import physicsEnv
import time
h = physicsEnv.host(True)

class objFunc:
    def __init__(self):
        self.frame = 0
        self.start = nav.positions[2]
        self.end = nav.positions[0]
    def update(self,o):
        if self.frame == 0:
            o.setTransform_qat([1,0,0,0,self.start[0],0,self.start[1]])
            self.pos = [1,0,0,0,self.start[0],0,self.start[1]]
        elif (self.pos[6] == self.end[1]) & (self.pos[4] == self.end[0]):
            quit(0)
        else:
            if (self.start[0]-self.end[0])==0:
                self.pos[6] = self.pos[6] - 0.01
                o.setTransform_qat(self.pos)
            else:
                m = (self.start[1]-self.end[1])/(self.start[0]-self.end[0])
                b = self.start[0]-m*self.start[1]
                x = self.frame*0.01
                self.pos[4] = x
                self.pos[6] = m*x+b
                o.setTransform_qat(self.pos)                   
                #print(m)
        self.frame = self.frame + 1
        #print(o.getTransform_qat())


class objTravel:
    def __init__(self):
        self.frame = 0
        self.dest = [100,100]
    def update(self,o):
        if self.frame == 0:
            self.pos = [o.getTransform_qat()[4],o.getTransform_qat()[6]]
            print(self.pos)
            slowness = 100
            self.delta = [(self.dest[0]-self.pos[0])/slowness,(self.dest[1]-self.pos[1])/slowness]
        elif (o.getTransform_qat()[4] == self.dest[0]) & (o.getTransform_qat()[6] == self.dest[1]):
            quit()
        elif (o.getTransform_qat()[4] in range(self.dest[0]-10,self.dest[0]+10)) & (o.getTransform_qat()[6] in range(self.dest[1]-10,self.dest[1]+10)):
            quit()
        else:
            transform = o.getTransform_qat()
            transform[4] = transform[4]  + self.delta[0]
            transform[6] = transform[6]  + self.delta[1]
            o.setTransform_qat(transform)
            print(transform)
        self.frame = self.frame +1

class pyObj:
    def __init__(self,o):
        self.cObj = o
        self.upFuncs = []
    def attachUpdateFunc(self,func):
        self.upFuncs.append(func)
    def update(self):
        for x in self.upFuncs:
            x.update(self.cObj)
    
intersections = []
freeze = []
for x in nav.positions:
    o = h.addObject(1)
    o.setTransform_qat([1,0,0,0,x[0],0,x[1]])
    o.setProperties("static")
    pyO = pyObj(o)
    intersections.append(pyO)

objs = []
traveller = pyObj(h.addObject(1))
traveller.cObj.setProperties("nograv")
traveller.attachUpdateFunc(objTravel())

while(True):
    h.update()
    traveller.update()
