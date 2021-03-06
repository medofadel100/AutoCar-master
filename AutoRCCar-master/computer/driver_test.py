
import cv2
import sys
import threading
import socket
import numpy as np


from model import NeuralNetwork
from driver_helper_test import *

class VideoStreamHandler(object):
    def __init__(self, host, port1, port2):
        self.server_socket = socket.socket()
        self.server_socket.bind((host, port1))
        self.server_socket.listen(0)
        self.connection, self.client_address = self.server_socket.accept()
        self.connection = self.connection.makefile('rb')
        self.host_name = socket.gethostname()
        self.host_ip = socket.gethostbyname(self.host_name)

        self.rc_car = RCControl(host, port2)
    # h1: stop sign, measured manually
    # h2: traffic light, measured manually
    h1 = 5.5  # cm
    h2 = 5.5

    # load trained neural network
    nn = NeuralNetwork()
    nn.load_model("saved_model/nn_model.xml")
    print(nn)
    
    obj_detection = ObjectDetection()
     

    # cascade classifiers
    stop_cascade = cv2.CascadeClassifier("cascade_xml/stop_sign.xml")
    light_cascade = cv2.CascadeClassifier("cascade_xml/traffic_light.xml")

    d_to_camera = DistanceToCamera()
    # hard coded thresholds for stopping, other two 25cm
    d_stop_light_thresh = 25
    d_stop_sign = d_stop_light_thresh
    d_light = d_stop_light_thresh

    stop_start = 0  # start time when stop at the stop sign
    stop_finish = 0
    stop_time = 0
    drive_time_after_stop = 0

    def handle(self):

        stream_bytes = b' '
        stop_flag = False
        stop_sign_active = True

        try:
            # stream video frames one by one
            while True:
                stream_bytes += self.connection.read(1024)
                first = stream_bytes.find(b'\xff\xd8')
                last = stream_bytes.find(b'\xff\xd9')
                if first != -1 and last != -1:
                    jpg = stream_bytes[first:last + 2]
                    stream_bytes = stream_bytes[last + 2:]
                    gray = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_GRAYSCALE)
                    image = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)

                    # lower half of the image
                    height, width = gray.shape
                    roi = gray[int(height/2):height, :]

                    # object detection
                    v_param1 = self.obj_detection.detect(self.stop_cascade, gray, image)
                    v_param2 = self.obj_detection.detect(self.light_cascade, gray, image)

                    # distance measurement
                    if v_param1 > 0 or v_param2 > 0:
                        d1 = self.d_to_camera.calculate(v_param1, self.h1, 300, image)
                        d2 = self.d_to_camera.calculate(v_param2, self.h2, 100, image)
                        self.d_stop_sign = d1
                        self.d_light = d2

                    cv2.imshow('image', image)
                    # cv2.imshow('mlp_image', roi)

                    # reshape image
                    image_array = roi.reshape(1, int(height/2) * width).astype(np.float32)

                    # neural network makes prediction
                    prediction = self.nn.predict(image_array)

                    # stop conditions

                    if 0 < self.d_stop_sign < self.d_stop_light_thresh and stop_sign_active:
                        print("Stop sign ahead")
                        self.rc_car.stop()

                        # stop for 5 seconds
                        if stop_flag is False:
                            self.stop_start = cv2.getTickCount()
                            stop_flag = True
                        self.stop_finish = cv2.getTickCount()

                        self.stop_time = (self.stop_finish - self.stop_start) / cv2.getTickFrequency()
                        print("Stop time: %.2fs" % self.stop_time)

                        # 5 seconds later, continue driving
                        if self.stop_time > 5:
                            print("Waited for 5 seconds")
                            stop_flag = False
                            stop_sign_active = False

                    elif 0 < self.d_light < self.d_stop_light_thresh:
                        # print("Traffic light ahead")
                        if self.obj_detection.red_light:
                            print("Red light")
                            self.rc_car.stop()
                        elif self.obj_detection.green_light:
                            print("Green light")
                            pass
                        elif self.obj_detection.yellow_light:
                            print("Yellow light flashing")
                            pass

                        self.d_light = self.d_stop_light_thresh
                        self.obj_detection.red_light = False
                        self.obj_detection.green_light = False
                        self.obj_detection.yellow_light = False

                    else:
                        self.rc_car.steer(prediction)
                        self.stop_start = cv2.getTickCount()
                        self.d_stop_sign = self.d_stop_light_thresh

                        if stop_sign_active is False:
                            self.drive_time_after_stop = (self.stop_start - self.stop_finish) / cv2.getTickFrequency()
                            if self.drive_time_after_stop > 5:
                                stop_sign_active = True

                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        print("car stopped")
                        self.rc_car.stop()
                        break
        finally:
            cv2.destroyAllWindows()
            sys.exit()

if __name__ == '__main__':
    video_thread = threading.Thread(target=VideoStreamHandler, args=('192.168.1.24', 8000, 8004))
    video_thread.start()
    # distance_thread = threading.Thread(target=SensorStreamingTest, args=('192.168.1.24', 8002))
    # distance_thread.start()