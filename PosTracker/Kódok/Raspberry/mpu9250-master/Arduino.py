import serial
import codecs
import csv
import time
import requests

FILENAME = "kimenet.csv"
ENCODING = 'utf-8'
i = 0
try:
    with codecs.open(FILENAME, "w", ENCODING) as fp:
        writer = csv.writer(fp)
	ser = serial.Serial('/dev/ttyUSB0',115200)
        print("Start")
	while True:
                i += 1
		read_serial=ser.readline() 
                print(i)
		#print(read_serial)
		writer.writerow([read_serial])

except KeyboardInterrupt:
    print 'Meres megszakitva!'
    print i
    url = 'http://192.168.43.55:5000/success'
    files = {'file': open(FILENAME, 'rb')}
    requests.post(url, files=files)