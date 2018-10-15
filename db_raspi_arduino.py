import serial
import mysql.connector

bd = mysql.connector.connect(user='root', password='raspberry',
                              host='192.168.0.140',
                              database='sensores')
cursor = bd.cursor()

ser = serial.Serial("/dev/ttyS0",115200)

while(True):
	verifica_inicio = ser.read(1)
	if(verifica_inicio=='T'):
		break

while(True):
	ident = ser.read(1)
	if ident == '1':
		buf = ser.read(1)
		leitura = str(ser.read(int(buf)))
		ins = ("INSERT INTO bh1750 (COD,leitura) VALUES (uuid(),"+leitura+")")
		cursor.execute(ins)
	elif ident == '2':
		buf = ser.read(1)
		leitura = str(ser.read(int(buf)))
		ins = ("INSERT INTO bmp180 (COD,leitura) VALUES (uuid(),"+leitura+")")
		cursor.execute(ins)
	elif ident == '3':
		buf = ser.read(1)
		leitura = str(ser.read(int(buf)))
		ins = ("INSERT INTO LDR (COD,id,leitura) VALUES (uuid(),'1',"+leitura+")")
		cursor.execute(ins)
	elif ident == '4':
		buf = ser.read(1)
		leitura = str(ser.read(int(buf)))
		ins = ("INSERT INTO LDR (COD,id,leitura) VALUES (uuid(),'2',"+leitura+")")
		cursor.execute(ins)
	elif ident == '5':
		buf = ser.read(1)
		leitura = str(ser.read(int(buf)))
		ins = ("INSERT INTO LDR (COD,id,leitura) VALUES (uuid(),'3',"+leitura+")")
		cursor.execute(ins)
	elif ident == '6':
		buf = ser.read(1)
		ir = str(ser.read(int(buf))) 
		buf = ser.read(1)
		full = str(ser.read(int(buf))) 
		buf = ser.read(1)
		vi = str(ser.read(int(buf))) 
		buf = ser.read(1)
		lx = str(ser.read(int(buf)))
		ins = ("INSERT INTO tsl2561 (COD,full,infra,visivel,lux) VALUES (uuid(),"+full+","+ir+","+vi+","+lx+")") 
		cursor.execute(ins)
	elif ident == '7':
		buf = ser.read(1)
		leitura = str(ser.read(int(buf)))
		ins = ("INSERT INTO temt6000 (COD,leitura) VALUES (uuid(),"+leitura+")")
		cursor.execute(ins)
	bd.commit()

cursor.close()
bd.close()
