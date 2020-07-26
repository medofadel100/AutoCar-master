#__author__ = 'Ahmed Fadel'

import socket
import time
import pygame
from pygame.locals import *
import numpy as np
import cv2
import threading
import os

class CollectTrainingData(object):
    def __init__(self, input_size):
        self.input_size = input_size
        self.temp_array = []
        self.saved_frame = 0
        self.total_frame = 0
        self.frame = 0
        print("Start collecting images...")
        print("Press 'q' or 'x' to finish...")

        self.X = np.empty((0, self.input_size))
        self.y = np.empty((0, 4))

        # create labels
        self.k = np.zeros((4, 4), 'float')
        for i in range(4):
            self.k[i, i] = 1

    def temp(self, array):
        self.temp_array = array

    def save_frame(self, label):
        self.saved_frame += 1
        self.X = np.vstack((self.X, self.temp_array))
        self.y = np.vstack((self.y, self.k[label]))

    def save_file(self):
        file_name = str(int(time.time()))
        directory = "training_data"
        print("trying to save")
        if not os.path.exists(directory):
            print("making dir")
            os.makedirs(directory)
        
        print("saving file")
        print(self.X)
        print(self.y)
        np.savez(directory + file_name + 'test.npz', train=self.X, train_labels=self.y)
        
s = 120 * 320
collected_data = CollectTrainingData(s)


class ControlStreamingTest(object):
    def __init__(self, host, port):

        self.server_socket = socket.socket()
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind((host, port))
        self.server_socket.listen(0)
        self.connection, self.client_address = self.server_socket.accept()
        self.host_name = socket.gethostname()
        self.host_ip = socket.gethostbyname(self.host_name)

        # vector size, half of the image
        

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
                        collected_data.save_frame(2)
                        self.connection.send(str('8').encode('ascii'))

                    elif key_input[pygame.K_DOWN]:
                        print("Reverse")
                        self.connection.send(str('2').encode('ascii'))

                    elif key_input[pygame.K_RIGHT]:
                        print("Right")
                        collected_data.save_frame(1)
                        self.connection.send(str('6').encode('ascii'))

                    elif key_input[pygame.K_LEFT]:
                        print("Left")
                        collected_data.save_frame(0)
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

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

class VideoStreamingTest(object):
    def __init__(self, host, port):

        self.server_socket = socket.socket()
        self.server_socket.bind((host, port))
        self.server_socket.listen(0)
        self.connection, self.client_address = self.server_socket.accept()
        self.connection = self.connection.makefile('rb')
        self.host_name = socket.gethostname()
        self.host_ip = socket.gethostbyname(self.host_name)
        self.streaming()

    def streaming(self):

        try:
            print("Host: ", self.host_name + ' ' + self.host_ip)
            print("Connection from: ", self.client_address)
            print("Streaming...")
            print("Press 'q' to exit")

            # need bytes here
            stream_bytes = b' '
            while True:
                stream_bytes += self.connection.read(1024)
                first = stream_bytes.find(b'\xff\xd8')
                last = stream_bytes.find(b'\xff\xd9')
                if first != -1 and last != -1:
                    jpg = stream_bytes[first:last + 2]
                    stream_bytes = stream_bytes[last + 2:]
                    image = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_GRAYSCALE)
                    print(image.shape)
                    height, width = image.shape
                    roi = image[int(height/2):height, :]
                    cv2.imshow('image', image)

                    collected_data.temp(roi.reshape(1, int(height/2) * width).astype(np.float32))
                
                    collected_data.frame += 1
                    collected_data.total_frame += 1

                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        collected_data.save_file()
                        break
        finally:
            self.connection.close()
            self.server_socket.close()


if __name__ == '__main__':
    distance_thread = threading.Thread(target=VideoStreamingTest, args=('192.168.1.24', 8004))
    distance_thread.start()
    video_thread = threading.Thread(target=ControlStreamingTest, args=('192.168.1.24', 8002))
    video_thread.start()
    