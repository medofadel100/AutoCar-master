from socket import *
import time
import serial

client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect(('192.168.1.24', 8002))

ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1)

try:
    while True:
        # send data to the host every 0.5 sec
        result = client_socket.recv(1024)
        print(result, type(result))
        ser.write(chr(result).encode('ascii'))
        time.sleep(0.5)
finally:
    client_socket.close()