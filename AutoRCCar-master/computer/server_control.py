import socket
import time
import pygame
from pygame.locals import *

class SensorStreamingTest(object):
    def __init__(self, host, port):

        self.server_socket = socket.socket()
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind((host, port))
        self.server_socket.listen(0)
        self.connection, self.client_address = self.server_socket.accept()
        self.host_name = socket.gethostname()
        self.host_ip = socket.gethostbyname(self.host_name)

        pygame.init()
        pygame.display.set_mode((250, 250))
        
        self.send_inst = True
        self.steer()
    
    def steer(self):

        while self.send_inst:
            

            for event in pygame.event.get():
                if event.type == KEYDOWN:
                    key_input = pygame.key.get_pressed()

                    # simple orders
                    if key_input[pygame.K_UP]:
                        print("Forward")
                        #self.fb_address.put('/self-drive-car', 'control', '8')
                        self.connection.send(str('8').encode('ascii'))

                    elif key_input[pygame.K_DOWN]:
                        print("Reverse")
                        #self.fb_address.put('/self-drive-car', 'control', '2')
                        self.connection.send(str('2').encode('ascii'))

                    elif key_input[pygame.K_RIGHT]:
                        print("Right")
                        #self.fb_address.put('/self-drive-car', 'control', '6')
                        self.connection.send(str('6').encode('ascii'))

                    elif key_input[pygame.K_LEFT]:
                        print("Left")
                        #self.fb_address.put('/self-drive-car', 'control', '4')
                        self.connection.send(str('4').encode('ascii'))

                    elif key_input[pygame.K_SPACE]:
                        print("Stop")
                        #self.fb_address.put('/self-drive-car', 'control', '0')
                        self.connection.send(str('0').encode('ascii'))
                        
                    # exit
                    elif key_input[pygame.K_x] or key_input[pygame.K_q]:
                        print("Exit")
                        self.send_inst = False
                        #self.fb_address.put('/self-drive-car', 'control', 'q')
                        self.connection.send(str('q').encode('ascii'))
                        self.connection.close()
                        self.server_socket.close()
                        break

                elif event.type == pygame.KEYUP:
                    print("Stop")
                    #self.fb_address.put('/self-drive-car', 'control', '0')
                    self.connection.send(str('0').encode('ascii'))

if __name__ == '__main__':
    h, p = "192.168.1.24", 8002
    SensorStreamingTest(h, p)