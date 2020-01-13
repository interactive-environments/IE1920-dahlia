from pykinect2 import PyKinectV2 as pk
from pykinect2 import PyKinectRuntime as pkr

import sys
import numpy as np
np.set_printoptions(threshold=sys.maxsize)
import cv2 as cv

import PyCmdMessenger as cmd

class TrackerIR(object):
    def __init__(self):
        # IR frame source
        self.kinect = pkr.PyKinectRuntime(pk.FrameSourceTypes_Infrared)
        # current IR frame
        # always a binary uint8 matrix (512x424)
        self.frame = None
        # coords of the white pixels
        self.xy = []

        # CmdMessenger init
        arduino = cmd.ArduinoBoard("COM8", baud_rate=9600)
        commands = [["coords", "i*"],
                    ["num", "i"],
                    ["unblock", ""]]
        self.c = cmd.CmdMessenger(arduino, commands)


    def printDim(self):
        print(self.kinect.infrared_frame_desc.Height, self.kinect.infrared_frame_desc.Width)

    def updateFrame(self):
        self.frame = self.kinect.get_last_infrared_frame().reshape(
                (self.kinect.infrared_frame_desc.Height, self.kinect.infrared_frame_desc.Width)
            )
        _, self.frame = cv.threshold(self.frame, 15000, 255, cv.THRESH_BINARY)
        self.frame = self.frame.astype(np.uint8)

    def enlarge(self):
        kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, (9, 9))
        self.frame = cv.dilate(self.frame, kernel)

    def output(self):
        data = np.where(self.frame == 255)
        self.xy = list(zip(data[1], data[0]))

    def printXY(self):
        print("coordinates:")
        for cord in self.xy:
            print(cord)

    def sendData(self, data):
        args = [2 * len(data)]
        for cord in data:
            args.append(int(cord[0]))
            args.append(int(cord[1]))
        self.c.send("coords", *args)

    def sendNum(self, data):
        self.c.send("num", len(data))
        block = self.c.receive()
        while(block == None):
            block = self.c.receive()


    def show(self):
        while True:
            self.updateFrame()
            self.output()
            cv.imshow("frame", self.frame)
            if cv.waitKey(1) & 0xFF == ord('q'):
                break
        cv.destroyAllWindows()

    def send(self):
        while True:
            self.updateFrame()
            self.output()
            cv.imshow("frame", self.frame)
            self.sendNum(self.xy)
            if cv.waitKey(1) & 0xFF == ord('q'):
                break
        cv.destroyAllWindows()


    def record(self, fps):
        fourcc = cv.VideoWriter_fourcc(*'DIVX')
        out = cv.VideoWriter('output.avi', fourcc, fps, (512, 424), False)
        while True:
            self.updateFrame()
            cv.imshow("frame", self.frame)
            out.write(self.frame)
            if cv.waitKey(1) & 0xFF == ord('q'):
                break
        out.release()
        cv.destroyAllWindows()


tracker = TrackerIR()
tracker.printDim()
tracker.send()
