#!/usr/bin/env python
import RPi.GPIO as GPIO
from time import sleep
from mpu9250 import mpu9250
GPIO.setmode(GPIO.BCM)

GPIO.setup(17, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)

GPIO.output(27, GPIO.HIGH)
GPIO.output(17, GPIO.LOW)
GPIO.output(22, GPIO.HIGH)

def selPin(n, pins):
	for i in pins:
		if i == n:
			GPIO.output(n, GPIO.LOW)
		else:
			GPIO.output(i, GPIO.HIGH)

imu = mpu9250()

pins = [17, 27, 22]

try:
	while True:
		for i in pins:
			selPin(i, pins)
			sleep(0.05)			
			a = imu.accel
			print i
			print a
		# print 'Accel: {:.3f} {:.3f} {:.3f} mg'.format(*a)
		# g = imu.gyro
		# print 'Gyro: {:.3f} {:.3f} {:.3f} dps'.format(*g)
		# m = imu.mag
		# print 'Magnet: {:.3f} {:.3f} {:.3f} mT'.format(*m)
		# m = imu.temp
		# print 'Temperature: {:.3f} C'.format(m)
		sleep(0.05)
except KeyboardInterrupt:
	print 'bye ...'
