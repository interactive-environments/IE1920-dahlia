from pykinect2 import PyKinectV2 as pk
from pykinect2 import PyKinectRuntime as pkr

import sys
import numpy as np

np.set_printoptions(threshold=sys.maxsize)
import cv2 as cv

import PyCmdMessenger as cmd


class TrackerDepth(object):
    def __init__(self):
        # depth frame source
        self.kinect = pkr.PyKinectRuntime(pk.FrameSourceTypes_Depth)
        # current depth frame
        self.frame = None
        # binarized frame
        # always a binary uint8 matrix (512x424)
        self.bin = None
        # coords of the white pixels in the binarized frame
        self.data = []

        # CmdMessenger init
        arduino = cmd.ArduinoBoard("COM8", baud_rate=9600)
        commands = [["coords", "i*"],
                    ["num", "l"],
                    ["unblock", ""]]
        self.c = cmd.CmdMessenger(arduino, commands)

    def printDim(self):
        print(self.kinect.depth_frame_desc.Height, self.kinect.depth_frame_desc.Width)

    def updateFrame(self):
        self.frame = self.kinect.get_last_depth_frame().reshape(
            (self.kinect.depth_frame_desc.Height, self.kinect.depth_frame_desc.Width)
        )

    def toUint8(self):
        return np.uint8(self.frame * 0.032)

    def updateBin(self):
        t0 = 1900
        t1 = 2600
        ret0, bin0 = cv.threshold(self.frame, t0, 127, cv.THRESH_BINARY)
        ret1, bin1 = cv.threshold(self.frame, t1, 127, cv.THRESH_BINARY_INV)
        bin0 = np.uint8(bin0)
        bin1 = np.uint8(bin1)
        self.bin = (cv.add(bin0, bin1) - 127) * 2

    def updateData(self):
        coords = np.where(self.bin == 254)
        self.data = list(zip(coords[1], coords[0]))

    def sendNum(self):
        self.c.send("num", len(self.data))
        block = self.c.receive()
        while (block == None):
            block = self.c.receive()

    def printData(self):
        print("coordinates:")
        for cord in self.data:
            print(cord)

    def show(self):
        while True:
            self.updateFrame()
            self.updateBin()
            cv.imshow("frame", self.toUint8())
            if cv.waitKey(1) & 0xFF == ord('q'):
                break
        cv.destroyAllWindows()

    def send(self):
        while True:
            self.updateFrame()
            self.updateBin()
            self.updateData()
            self.sendNum()
            cv.imshow("frame", self.bin)
            if cv.waitKey(1) & 0xFF == ord('q'):
                break
        cv.destroyAllWindows()


tracker = TrackerDepth()
tracker.printDim()
tracker.send()
