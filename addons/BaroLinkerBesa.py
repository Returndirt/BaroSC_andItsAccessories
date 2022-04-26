import xml.etree.ElementTree as TREE
import os

from numpy import choose, double


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
                        print("get:"+wireFootMarks[1]+","+wireFootMarks[end-1])
                        if double(wireFootMarks[1])<double(wireFootMarks[end-1]):
                            p3s = [wireFootMarks[0],wireFootMarks[1],wireFootMarks[end-2],wireFootMarks[1],wireFootMarks[end-2],wireFootMarks[end-1]]    
                        if double(wireFootMarks[end-1])<=double(wireFootMarks[1]):
                            p3s = [wireFootMarks[0],wireFootMarks[1],wireFootMarks[0],wireFootMarks[end-1],wireFootMarks[end-2],wireFootMarks[end-1]]
                        print("choose "+p3s[3])
                        outline = []
                        outline.clear()
                        for ind in range(0,101):
                            outline.append( round( (((100.0-float(ind))/100.0)*((100.0-float(ind))/100.0))*float(p3s[0]) + 2.0*((float(ind)/100.0)*((100.0-float(ind))/100.0)*float(p3s[2]))+ (float(ind)/100.0)*(float(ind)/100.0)*float(p3s[4]) ))
                            outline.append( round( (((100.0-float(ind))/100.0)*((100.0-float(ind))/100.0))*float(p3s[1]) + 2.0*((float(ind)/100.0)*((100.0-float(ind))/100.0)*float(p3s[3]))+ (float(ind)/100.0)*(float(ind)/100.0)*float(p3s[5]) ))
                        outline=list(map(str,outline))
                        j.set("nodes",';'.join(outline))
    fileDir = str(dir) +"\\"+str(i)+ ".xml"
#    print(fileDir)
    infTree.write( fileDir )

os.system('pause')




