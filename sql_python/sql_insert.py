#!/usr/bin/python2

import datetime, time
import mysql.connector as sql

q = "INSERT INTO test_data (time, d1, d2) VALUES (%s, %s, %s)"
conn = sql.connect(host="localhost", user="aziro", password="aziro@123", database="robot_logger")
cursor = conn.cursor()

start = time.time()

for i in range(1000):
    fmt = (str(datetime.datetime.now()), "teshan"+str(i), "somwtha aisdf asb"+str(i))
    cursor.execute(q, fmt)
conn.commit()

print(time.time() - start)
