import mysql.connector

bd_local = mysql.connector.connect(user='root', password='raspberry',host='192.168.0.140',database='sensores')
cursor = bd_local.cursor()

bd_cloud = mysql.connector.connect(user='root', password='q1w2e3rtghnjmk,.;!',host='35.198.62.39',database='sensores')
cursor2 = bd_cloud.cursor()

query = ("SELECT COD, leitura, data FROM bh1750 ")

cursor.execute(query)

for (COD, leitura, data) in cursor:
  print("{}, {}, {:%d %b %Y}".format(COD, leitura, data))

cursor.close()
cursor2.close()
bd_local.close()
bd_cloud.close()