#__author__ = 'Ahmed Fadel'

#import serial
import pygame
from pygame.locals import *
from firebase import firebase

class RCTest(object):

    def __init__(self):
        pygame.init()
        pygame.display.set_mode((250, 250))
        self.fb_address = firebase.FirebaseApplication("https://self-drive-car.firebaseio.com/", None)
        #self.ser = serial.Serial("/dev/tty.usbmodem1421", 115200, timeout=1)    # mac
        # self.ser = serial.Serial("/dev/ttyACM0", 115200, timeout=1)           # linux
        #self.ser = serial.Serial('COM8', 115200, timeout=1)                     #windows
        self.send_inst = True
        #self.steer()

    def steer(self):

        while self.send_inst:
            

            for event in pygame.event.get():
                if event.type == KEYDOWN:
                    key_input = pygame.key.get_pressed()

                    # simple orders
                    if key_input[pygame.K_UP]:
                        print("Forward")
                        self.fb_address.put('/self-drive-car', 'control', '8')

                    elif key_input[pygame.K_DOWN]:
                        print("Reverse")
                        self.fb_address.put('/self-drive-car', 'control', '2')

                    elif key_input[pygame.K_RIGHT]:
                        print("Right")
                        self.fb_address.put('/self-drive-car', 'control', '6')

                    elif key_input[pygame.K_LEFT]:
                        print("Left")
                        self.fb_address.put('/self-drive-car', 'control', '4')

                    elif key_input[pygame.K_SPACE]:
                        print("Stop")
                        self.fb_address.put('/self-drive-car', 'control', '0')
                        
                    # exit
                    elif key_input[pygame.K_x] or key_input[pygame.K_q]:
                        print("Exit")
                        self.send_inst = False
                        break

                # elif event.type == pygame.KEYUP:
                #     print("Stop")
                #     self.fb_address.put('/self-drive-car', 'control', '0')


if __name__ == '__main__':
    RCTest().steer()
