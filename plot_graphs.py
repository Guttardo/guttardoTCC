import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import time
import mysql.connector
import datetime

bd_cloud = mysql.connector.connect(user='root', password='q1w2e3rtghnjmk,.;!',host='35.198.12.124',database='sensores')
cursor = bd_cloud.cursor()

sensor = "LDR"

if(sensor=="LDR"):
    ins = "SELECT leitura, data from "+ sensor +" where id=1 order by data"
    cursor.execute(ins)
    ldr1 = cursor.fetchall()
    ins = "SELECT leitura, data from "+ sensor +" where id=2 order by data"
    cursor.execute(ins)
    ldr2 = cursor.fetchall()
    ins = "SELECT leitura, data from "+ sensor +" where id=3 order by data"
    cursor.execute(ins)
    ldr3 = cursor.fetchall()
    plt.plot([data for leitura, data in ldr1], [leitura for leitura,data in ldr1],label='LDR 1')
    plt.plot([data for leitura, data in ldr2], [leitura for leitura,data in ldr2],label='LDR 2')
    plt.plot([data for leitura, data in ldr3], [leitura for leitura,data in ldr3],label='LDR 3')
    plt.legend()
elif (sensor=="tsl2561"):
    ins = "SELECT full, infra, lux, visivel, data from "+ sensor +" order by data"
    cursor.execute(ins)
    dados = cursor.fetchall()
else:
    ins = "SELECT leitura, data from "+ sensor +" order by data"
    cursor.execute(ins)
    dados = cursor.fetchall()
    plt.plot([data for leitura, data in dados], [leitura for leitura,data in dados])

plt.gcf().autofmt_xdate()
plt.xlabel('Hora')
plt.ylabel('Leitura')
plt.title(sensor)
plt.show()