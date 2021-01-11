import physicsEnv
import time

w = physicsEnv.worldComposite()
#b = physicsEnv.create_complex(w)
#b = physicsEnv.generic_obj(w)

#time.sleep(1000)

pos = [1,1,1]
size = [2,2,2]
b = physicsEnv.create_complex(w,size,pos)
#t = sample.terrain_obj(w)

choice = "run"
while choice != "quit":
    choice = input("Choice: ")

    if choice[:6] == "update":
        for x in range(int(choice[6:])):
            #start = time.time()
            w.update()
            #end = time.time()
            #calc_time = end - start
            #time.sleep(1-calc_time)

    if choice == "properties":
        print(b.getProperties())
    if choice == "set_transform":
        print(b.setTransform_qat())
    if choice == "get_transform":
        print(b.getTransform_qat())
    if choice == "quit":
        #del b
        del w
        
