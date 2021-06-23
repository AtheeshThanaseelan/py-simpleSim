import physicsEnv
import math

w = physicsEnv.host(False)
w.addObject(1)
o = w.getObject(0)
for x in range(10):
    print(o.getTransform_qat())
    w.update()