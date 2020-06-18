#!/usr/bin/python

import pandas as pd
import mysql.connector as sql
import pickle
import os, sys

#os.remove(pfile)
conn = sql.connect(host="localhost", user="root", password="password", database="RFID_cache")

if len(sys.argv) == 1:
	print("Specify a file name")
	sys.exit()
else:
	q = "select * from RFID_Data" 
	pfile = "rfid_{}.pickle".format(sys.argv[1])

df = pd.read_sql(q, con=conn)
pickle.dump(df, open(pfile, 'wb'))
