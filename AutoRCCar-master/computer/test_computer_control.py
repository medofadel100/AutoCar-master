from firebase import firebase
import serial
import time

firebase = firebase.FirebaseApplication("https://self-drive-car.firebaseio.com/", None)

run = True


ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1)
while run:
    
    result = int(firebase.get('/self-drive-car/control', ''))
    print(result, type(result))
    ser.write(chr(result).encode('ascii'))
    
    #ser.write(b"" + result +"\n")
    #if result == 'q': 
    #    break
        
