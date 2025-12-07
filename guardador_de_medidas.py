from serial.tools import list_ports
import serial
import time
import json

archivo_logs = "logs.json"

#Estas línas sirven para identificar manualmente el puerto serial del arduino.
ports = list_ports.comports()
for port in ports: print(port)


#Esta línea se conecta al puerto serial. Seguramente hay que cambiarla dependiendo de la computadora.
serialCom = serial.Serial('/dev/cu.usbmodemFD131', 57600)

#Resetear el arduino
serialCom.setDTR(False)
time.sleep(1)
serialCom.flushInput()
serialCom.setDTR(True)

#Abrimos el archivo de los logs.
with open(archivo_logs, 'r') as file:
	eventosJSON = json.load(file)

#Cargamos los eventos que ya tenemos
eventos = eventosJSON['eventos']


#Definimos las llaves para el diccionario que contedrá los eventos.
llaves = ["tipo", "estado", "fecha", "hora"]


while(1):
	try:
		#Leemos una linea del serial y la decodificamoes
		s_bytes = serialCom.readline()
		decoded_bytes = s_bytes.decode("utf-8").strip('\r\n')
		datos = decoded_bytes.split(',')
		nuevo_evento = dict(zip(llaves, datos))
		eventos.append(nuevo_evento)
		print("Nuevo evento registrado")
	except Exception as e:
		print("Error: no se pudo leer una línea")
		print(e)
	#Actualizamos la lista de eventos y el archivo
	nuevos_eventos = json.dumps(dict(eventos = eventos), indent=4)
	nuevo_estado = json.dumps(dict(eventos = [eventos[-1]]), indent=4)
	with open(archivo_logs, 'w') as file:
		file.write(nuevos_eventos)
	with open("estado.json", 'w') as file:
		file.write(nuevo_estado)
