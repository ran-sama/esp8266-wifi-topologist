# esp8266-wifi-topologist
Use the power of Graphviz and Espressif to map wifi-networks.

## Motivation:

So I found Ray's "ESP8266 Mini Sniff" (check out his work in the link below) and felt I could help my mind create the connections between clients and APs to make it easier for myself to see the connections. The ESP8266 WiFi-Topologist was born.
```
https://www.hackster.io/rayburne/projects
```

## What it outputs:

![alt text](https://raw.githubusercontent.com/ran-sama/esp8266_python_wifi_topologist/master/20180521-213837_censored.png)

## Requirements:

On your Linux box please install:
```
sudo apt install python-pyserial
sudo apt install python-graphviz
```
Inside Arduini IDE v1.8.5 it will successfully compile with v2.4.0, no other versions tested.

Connect the flashed esp8266 over USB and run it simply like:
```
python serialgrapher.py
```
or manually
```
watch -n 1200 python serialgrapher.py
```
To re-run at 20 minute intervals. Also there is a line in the python sketch to run infinitely, don't use with watch :)

## Thoughts and limitations:

1) M̶y̶ ̶v̶e̶n̶d̶o̶r̶ ̶l̶i̶s̶t̶ ̶i̶s̶ ̶i̶n̶c̶o̶m̶p̶l̶e̶t̶e̶ ̶s̶i̶n̶c̶e̶ ̶l̶i̶c̶e̶n̶s̶i̶n̶g̶ ̶o̶f̶ ̶b̶e̶t̶t̶e̶r̶ ̶o̶n̶e̶s̶ ̶w̶a̶s̶ ̶n̶o̶t̶ ̶a̶l̶w̶a̶y̶s̶ ̶c̶l̶e̶a̶r̶.̶ (fixed)
2) Nodes repulse like particles carrying the same charge, connections occasionally overlap.
3) R̶a̶r̶e̶l̶y̶ ̶t̶w̶o̶ ̶M̶A̶C̶-̶a̶d̶d̶r̶e̶s̶s̶e̶s̶ ̶c̶a̶n̶ ̶"̶b̶a̶k̶e̶"̶ ̶t̶o̶g̶e̶t̶h̶e̶r̶,̶ ̶I̶ ̶h̶a̶v̶e̶ ̶n̶o̶t̶ ̶y̶e̶t̶ ̶f̶o̶u̶n̶d̶ ̶t̶h̶e̶ ̶r̶o̶o̶t̶ ̶c̶a̶u̶s̶e̶.̶ (fixed)
4) It runs completely passive, no packets are emitted! Also be surprised to even detect cars in wifi.


## License
Licensed under the WTFPL license.
