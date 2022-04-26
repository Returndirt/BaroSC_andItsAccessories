from posixpath import split
from turtle import write_docstringdict
import xml.etree.ElementTree as TREE
import os
from matplotlib import scale

from numpy import float


def getXmls(path):
    fline = os.listdir(path)
    oFileNameLine = []
    for i in fline:
        if os.path.splitext(i)[1]=='.xml':
            oFileNameLine.append(os.path.splitext(i)[0])
    return oFileNameLine

print("Standardized submarine wiring")
#dir = os.path.dirname(os.path.realpath(__file__))
dir = os.getcwd()
print("work dir = "+ dir)
fileLine = getXmls(dir)
for i in fileLine:
    print("get " +i+ ".xml") 
    scl = input("he?")
    scl = float(scl)
    infTree = TREE.parse(dir +"\\"+i+ ".xml")
    infRoot = infTree.getroot()
    for thing in infRoot:
        if(thing.tag == "Structure"):
            x = thing.get("rect")
            marks = x.split(",")
            marks[0] = str(int(float(marks[0])*scl))
            marks[1] = str(int(float(marks[1])*scl))
            marks[2] = str(int(float(marks[2])*scl))
            marks[3] = str(int(float(marks[3])*scl))
            thing.set("rect",str(",".join(marks)))
            x = str(thing.get("texturescale"))
            marks = x.split(",")
            marks[0] = str(float(marks[0])*scl)
            marks[1] = str(float(marks[1])*scl)
            thing.set("texturescale",str(",".join(marks)))
        if(thing.tag == "Item"):
            x = thing.get("rect")
            marks = x.split(",")
            marks[0] = str(int(float(marks[0])*scl))
            marks[1] = str(int(float(marks[1])*scl))
            if(thing.get("identifier")=="ladder"):
                marks[3] = str(int(float(marks[3])*scl))
            thing.set("rect",str(",".join(marks)))
            x = thing.get("scale")
            x = str(float(x)*scl)
            thing.set("scale",x)
            if(thing.get("identifier").find("wire")>-1):
                print("is a wire")
                for j in thing:
                    if(j.tag == "Wire"):
                        print("got nodes")
                        walkWire = j.get("nodes")
                        wireFootMarks = walkWire.split(";")
                        print(wireFootMarks)
                        for k in range(len(wireFootMarks)):
                            wireFootMarks[k] = str(int(float(wireFootMarks[k])*scl))
                        print(wireFootMarks)
                        j.set("nodes",";".join(wireFootMarks))
        if(thing.tag == "WayPoint"):
            x =thing.get("x")
            x = str(int(float(x)*scl))
            thing.set("x",x)
            x =thing.get("y")
            x =str(int(float(x)*scl))
            thing.set("y",x)
        if(thing.tag == "Hull"):
            x = thing.get("rect")
            marks = x.split(",")
            marks[0] = str(int(float(marks[0])*scl))
            marks[1] = str(int(float(marks[1])*scl))
            marks[2] = str(int(float(marks[2])*scl))
            marks[3] = str(int(float(marks[3])*scl))
            thing.set("rect",str(",".join(marks)))
        if(thing.tag == "Gap"):
            x = thing.get("rect")
            marks = x.split(",")
            marks[0] = str(int(float(marks[0])*scl))
            marks[1] = str(int(float(marks[1])*scl))
            marks[2] = str(int(float(marks[2])*scl))
            marks[3] = str(int(float(marks[3])*scl))
            thing.set("rect",str(",".join(marks)))
#            if(Item.get("identifier").find("wire")>-1):
#                for j in Item:
#                    if(j.tag == "Wire"):
#                        walkWire = j.get("nodes")
#                        wireFootMarks = walkWire.split(";")
#                        end = len(wireFootMarks)
#                        newWireFootMarks = [wireFootMarks[0],wireFootMarks[1],wireFootMarks[end-2],wireFootMarks[1],wireFootMarks[end-2],wireFootMarks[end-1]]
#                        j.set("nodes",str(";".join(newWireFootMarks)))   
    fileDir = str(dir) +"\\"+str(i)+ ".xml"
#    print(fileDir)
    infTree.write( fileDir )

os.system('pause')




