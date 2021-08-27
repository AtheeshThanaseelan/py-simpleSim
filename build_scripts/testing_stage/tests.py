import physicsEnv

def collisions():
    host = physicsEnv.host(False)
    o = host.addObject(1)
    o2 = host.addObject(1)
    o2.setProperties("static")
    o.setTransform_qat([0.5,0.5,0.5,0.5,0,4,0])
    for x in range(0,600):
        host.update()   
    x = o.getTransform_qat()
    return x

def setTransform():
    host = physicsEnv.host(False)
    o = host.addObject(1)
    o.setTransform_qat([0.5,0.5,0.5,0.5,3.0,1.0,3.0])  
    x = o.getTransform_qat()
    return x

def test_collisions():
    result = collisions()
    assert ((result[0] - 0.5) < 0.001)
    assert ((result[1] - 0.5) < 0.001)
    assert ((result[2] - 0.5) < 0.001)
    assert ((result[3] - 0.5) < 0.001)
    assert ((result[4] - 0) < 0.001)
    assert ((result[5] - 2) < 0.001)
    assert ((result[6] - 0.001) < 0.001)
    #assert #1 == 0
    #assert #collisions() == [0.5000028014183044, 0.4999975562095642, 0.49999725818634033, 0.500002384185791, 0.0002511556085664779, 1.9999995231628418, 0.0012792845955118537]

def test_setTransform():
    assert setTransform() == [0.5,0.5,0.5,0.5,3.0,1.0,3.0]
