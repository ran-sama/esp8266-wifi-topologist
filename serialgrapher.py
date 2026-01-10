#!/usr/bin/env python
import serial, pygraphviz, time#, os

f = open("vendors.csv", 'r')
ser = serial.Serial('/dev/ttyUSB0', 115200) 

A=pygraphviz.AGraph(overlap=False)
A.node_attr['style']='filled'
A.node_attr['fillcolor']='lemonchiffon'

def getvalues(client_mac):
    mac_storage = "Unknown"
    for line in f:
        if client_mac[0:6] in line:
            vendors = line.split(",")
            mac_storage = vendors[1]
    f.seek(0)
    return(mac_storage)

for x in xrange(1, 1001):
    my_string = ser.readline()
    my_list = my_string.split(",")
    client_mac = str(my_list[0])
    ap_ssid = str(my_list[1])
    mac_vendor = str(getvalues(client_mac)[:20].rstrip() + "\n" + client_mac)
    if (x % 10 == 0): print(str(x / 10) + "% scanning done")
    #print(client_mac,mac_vendor,ap_ssid)
    A.add_edge(ap_ssid,mac_vendor)
    A.add_edge("sniffer",ap_ssid)

filenames = time.strftime("%Y%m%d-%H%M%S")

A.add_edge(my_list)
#uncomment below if you want to backup a graph in the editable dot-format
#A.write(filenames + '.dot')
A.draw(filenames + '.png',prog='twopi')
f.close()
print("closing python instance")
#uncomment below and in imports to run infinitely
#os.system("/home/pi/serialgrapher.py")
