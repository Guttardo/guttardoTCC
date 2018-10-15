import mysql.connector
import datetime

bd_local = mysql.connector.connect(user='root', password='raspberry',host='192.168.0.140',database='sensores', buffered=True)
cursor = bd_local.cursor()

bd_cloud = mysql.connector.connect(user='root', password='q1w2e3rtghnjmk,.;!',host='35.198.62.39',database='sensores', buffered=True)
cursor2 = bd_cloud.cursor()

query = ("SELECT COD, leitura, data FROM bh1750 ")

cursor.execute(query)

for (COD, leitura, data) in cursor:
    ins = "INSERT INTO bh1750 (COD,leitura, data, sync) VALUES (uuid(),"+str(leitura)+",'"+data.strftime("%Y-%m-%d %H:%M:%S")+"', 1)"
    cursor2.execute(ins)
    bd_cloud.commit()
    delet = "DELETE FROM bh1750 WHERE `COD` = '"+COD+"' "
    cursor.execute(delet)
    bd_local.commit()

cursor.close()
cursor2.close()
bd_local.close()
bd_cloud.close()