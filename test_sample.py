def collisions(x):
    return x + 1

def setProp_gravity(x):
	return x

def setTransform(x):
	return x


def test_collisions():
    assert collisions(3) == 4

def test_setGrav():
    assert setProp_gravity(3) == 3

def test_setTransform():
    assert setTransform(3) == 3
