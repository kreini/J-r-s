#!/usr/bin/env python
import RPi.GPIO as GPIO
from time import sleep
from mpu9250 import mpu9250
import codecs
import csv
import time
import requests

# A GPIO labak beallitasa a SoC szerint
GPIO.setmode(GPIO.BCM)


# Pin-ek sorrendje az imu-khoz
pins = [17, 27, 22, 6, 13, 19, 26]


# GPIO tipusanak meghatarozasa
for i in pins:
    GPIO.setup(i, GPIO.OUT)
    GPIO.output(i, GPIO.HIGH)
#GPIO.setup(17, GPIO.OUT)
#GPIO.setup(27, GPIO.OUT)
#GPIO.setup(22, GPIO.OUT)


# Teszt a GPIO allitasra
#GPIO.output(17, GPIO.HIGH)
GPIO.output(27, GPIO.LOW)
#GPIO.output(22, GPIO.HIGH)

# Fuggveny a kimenetek allitasara, hogy a 68-as cimen pontosan egy eszkoz maradjon
def selPin(n, pins):
    for i in pins:
        if i == n:
            GPIO.output(n, GPIO.LOW)
        else:
            GPIO.output(i, GPIO.HIGH)

# imu olvasas inicializalasa
imu = mpu9250()


# CSV-hez kello dolgok
FILENAME = "kimenet.csv"
ENCODING = 'utf-8'

# olvasas
try:
    with codecs.open(FILENAME, "w", ENCODING) as fp:
        writer = csv.writer(fp)
        writer.writerow(["t", "sensor", "ax", "ay", "az", "gx", "gy", "gz"])
        while True:
            for i in pins:
                selPin(i, pins)
                sleep(0.01)
                a = imu.accel
                g = imu.gyro
                writer.writerow([time.time(), i, a[0],a[1],a[2],g[0],g[1],g[2]])
                print i
                print a
        # print 'Accel: {:.3f} {:.3f} {:.3f} mg'.format(*a)
        # g = imu.gyro
        # print 'Gyro: {:.3f} {:.3f} {:.3f} dps'.format(*g)
        # m = imu.mag
        # print 'Magnet: {:.3f} {:.3f} {:.3f} mT'.format(*m)
        # m = imu.temp
        # print 'Temperature: {:.3f} C'.format(m)
        sleep(0.01)
except KeyboardInterrupt:
    GPIO.output(17, GPIO.HIGH)
    GPIO.output(27, GPIO.LOW)
    GPIO.output(22, GPIO.HIGH)
    print 'Meres megszakitva!'
    url = 'http://192.168.43.55:5000/success'
    files = {'file': open(FILENAME, 'rb')}
    requests.post(url, files=files)
