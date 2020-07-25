
from firebase import firebase

firebase = firebase.FirebaseApplication("https://self-drive-car.firebaseio.com/", None)

run = True

while run:
    result = firebase.get('/self-drive-car/control', '')
    print(result)
    if result == 'q': 
        break
        