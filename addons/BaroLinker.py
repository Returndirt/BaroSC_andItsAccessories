import xml.etree.ElementTree as TREE
import os


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
    infTree = TREE.parse(dir +"\\"+i+ ".xml")
    infRoot = infTree.getroot()
    for Item in infRoot:
        if(Item.tag == "Item"):
            if(Item.get("identifier").find("wire")>-1):
                for j in Item:
                    if(j.tag == "Wire"):
                        walkWire = j.get("nodes")
                        wireFootMarks = walkWire.split(";")
                        end = len(wireFootMarks)
                        newWireFootMarks = [wireFootMarks[0],wireFootMarks[1],wireFootMarks[end-2],wireFootMarks[1],wireFootMarks[end-2],wireFootMarks[end-1]]
                        j.set("nodes",str(";".join(newWireFootMarks)))   
    fileDir = str(dir) +"\\"+str(i)+ ".xml"
#    print(fileDir)
    infTree.write( fileDir )

os.system('pause')




