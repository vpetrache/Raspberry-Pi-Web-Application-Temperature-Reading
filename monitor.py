#!/usr/bin/env python

import sqlite3

import os
import time
import glob

from serial import Serial
import re



serial_pattern = r"T: (\d+\.\d*)\n";
serial_pattern2 = r"W: (\d+\.\d*)\n";
serial_port = '/dev/ttyACM0';
serial_bauds = 9600;


# global variables
speriod=(15*60)-1
dbname='/var/www/templog.db'

def open_serial_port() :
  s = Serial(serial_port, serial_bauds);
  line = s.readline();
  return s

def read_temperature(s):
  line = s.readline();
  m = re.match(serial_pattern, line);
  return float(m.group(1))  
 
def read_weight(s):
  line = s.readline();
  m = re.match(serial_pattern2, line);
  return float(m.group(1))  
  
# store the temperature in the database
def log_temperature(temp):

    conn=sqlite3.connect(dbname)
    curs=conn.cursor()

    curs.execute("INSERT INTO temps values(datetime('now'), (?))", (temp,))

    # commit the changes
    conn.commit()

    conn.close()
	
def log_greutate(Kg):

    conn=sqlite3.connect(dbname)
    curs=conn.cursor()

    curs.execute("INSERT INTO greutate values(datetime('now'), (?))", (Kg,))

    # commit the changes
    conn.commit()

    conn.close()
	

# display the contents of the database
def display_data():

    conn=sqlite3.connect(dbname)
    curs=conn.cursor()

    for row in curs.execute("SELECT * FROM temps"):
        print str(row[0])+"	"+str(row[1])

    conn.close()


def main():

        # Store the temperature in the database
	temperatura=read_temperature(s)
	greutate=read_weight(s)
    log_temperatura(temperatura)
	log_greutate(greutate)

        # display the contents of the database
#        display_data()

#        time.sleep(speriod)


if __name__=="__main__":
    main()
