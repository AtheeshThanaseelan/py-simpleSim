import physicsEnv
import math


g = physicsEnv.irr_btDebug(True)
w = physicsEnv.host(g)
w.addObject(1)
o = w.getObject(0)
for x in range(10):
    print(o.getTransform_qat())
    w.update()