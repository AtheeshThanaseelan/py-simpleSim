#Modified reader specifically for reading json objects
#Get current property-> there may be multiple properties, keep them in a list
#Level 1:root
#Level 2: object (get name)
#Level 3: none yet
#ITEM is an object that has a {} property
    #Assume all ITEMS are at root level
#Property is an object that has a non-object value
    #Assume all objects in an ITEM are properties
#Value is a value
    #Assume values are strings, numbers, or arrays

class simple_object:
    name = ""
    obj_type = ""
    obj_shape = ""
    obj_size = []
    transform_pos = []
    transform_qat = []


level=0
in_quote = 0
in_list = 0
is_property = 0
level_list = []

item_list = []
item_id = -1

property_list = []
property_id = -1

string_value = ""
list_value = []

def print_lists():
    print(item_list[0].name)
    print(item_list[0].obj_type)
    print(item_list[0].obj_shape)
    print(item_list[0].obj_size)
    print(item_list[0].transform_pos)
    print(item_list[0].transform_qat)

    print(item_list[1].name)
    print(item_list[1].obj_type)
    print(item_list[1].obj_shape)
    print(item_list[1].obj_size)
    print(item_list[1].transform_pos)
    print(item_list[1].transform_qat)

    print(item_list[2].name)
    print(item_list[2].obj_type)
    print(item_list[2].obj_shape)
    print(item_list[2].obj_size)
    print(item_list[2].transform_pos)
    print(item_list[2].transform_qat)

file = open("import.json", "r")

for line in file:
  for current_char in line:
    if in_quote == 1:
        if current_char == '"':
            in_quote = 0
            if in_list == 1:
                list_value.append(string_value)
            else:
                if is_property == 1:
                    property_list.append(string_value)
                    is_property = 0
                else:
                    if level == 1:
                        item_list.append(simple_object())
                        property_list.append(string_value)
                        item_id = item_id + 1
            string_value=""    
        else:
            string_value = string_value + current_char
    else:
        if current_char == "{":
            is_property = 0
            level= level+1
            if level == 1:
                level_list.append("root")
            else:
                level_list.append(string_value)
        if current_char == "}":
            level= level-1
            level_list.pop()
            if level != 0:
                item_list[item_id].name = property_list[0]
                item_list[item_id].obj_type = property_list[1]
                item_list[item_id].obj_shape = property_list[2]
                item_list[item_id].obj_size = property_list[3]
                item_list[item_id].transform_pos = property_list[4]
                item_list[item_id].transform_qat = property_list[5]
                property_list = []
                property_id = -1
        if current_char == '"':
            in_quote = 1
            string_value = ""
        if current_char == '[':
            is_property = 1
            list_value = []
            in_list = 1
            string_value = ""
        if current_char == ']':
            if in_list == 1 and string_value!="":
                list_value.append(float(string_value))
                string_value="" 
            is_property = 0
            property_list.append(list_value) 
            in_list = 0
        if current_char == ':':
            is_property = 1
        if current_char == ',':
            print(string_value)
            if in_list == 1 and string_value!="":
                list_value.append(float(string_value))
                string_value=""  
        if in_list ==1 and current_char != '[' and current_char != ',':
            string_value = string_value + current_char

file.close()

print_lists()
