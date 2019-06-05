import serial
import time
import datetime
import csv
import _thread as thread
from flask import Flask, render_template
import os, sys

ser = serial.Serial('/dev/ttyUSB0', 9600) #set baudrate and source device
os.system("echo '' > /home/pi/Documents/python/test_data.csv") #clear csv file with each restart
#ser.flushInput()
os.system("sudo service apache2 start")
ser.flushOutput()
def runcomms(): #this is in development right now the strings must be in this order:
    #first 7 letters name sensor ten a space then value is in hex so max 3 digits up to 255
    #like this Serial.println("sensor1 " + String(sensor1)); sensor is a byte
    while True:
        line = ser.readline()
        #print(line)
        length = len(line)
        try:
            line = line.decode("utf-8")
        except:
            print("could not decode with utf8")
        #print(ser.readline())
        #log the line to the file
        decodedline = line[0: len(line) -2]
        print(decodedline[0: 7], decodedline[7: length])
        with open("test_data.csv","a") as f:
            writer = csv.writer(f,delimiter=",")
            writer.writerow([decodedline[0: 7], decodedline[7: length]])
    #endif
#endwhile

#create a thread that runs the commlink and let the main thread run the flask server
thread.start_new_thread(runcomms, ())
#now use the main thread to run a flask server

print("main thread ends here")