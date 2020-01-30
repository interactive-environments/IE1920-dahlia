# DAHLIA
The DAHLIA project was created for the Interactive Environments minor 2019-2020 at the TU Delft (Delft Univercity of Technology). This repository holds the software which makes  the DAHLIA floor work. The Python code enables a computer to collect depth frames from a Kinect v2 and process them. After processing the frames, it sends data to an Arduino with the Arduino code in this repository installed on it. The Arduino code uses the data it received to display different patterns on the floor.

## Getting Started
These instructions should enable you to set up DAHLIA after the phisical structure has been build. 

### Setting Up the Hardware
To run the software the hardware should be connected properly to the computer you want to use. This computer should have an USB 3.0 port, because the Kinect v2 needs to be connected via USB 3.0 to function. The Arduino should be connected via some other USB port. 
Since the Arduino needs to control 467 LEDs it needs a lot of memory. The original project used an Arduino Due, but another board with similar hardware should work fine. 
Note the pins to which the floor is connected. Those pin numbers need to be filled in in the arduino code later on.

### Setting Up the Arduino Code
To be able to edit and upload code to the Arduino you can use the standard IDE provided by Arduino (https://www.arduino.cc/en/main/software).
Install the following libraries: 
- Adafruit_Neopixel (https://github.com/adafruit/Adafruit_NeoPixel)
- CmdMessenger (https://github.com/thijse/Arduino-CmdMessenger)
Via the IDE the Arduino code can be uploaded to the board. Remember the pin numbers you used when setting up the hardware. These numbers should be filled in on line 39-40 of the Dahlia.ino file:
'''
int pin1 = 5;   // Edit pin numbers here!
int pin2 = 7;   // Edit pin numbers here!
'''
If the animations seem a bit funky when the floor is fully set up, you can try to swap the port numbers, because when they are the wrong way around that is what happens then.
Note the port to which the arduino is connected to your computer. This is needed for setting up the Python code.

### Setting Up the Python Code
To set up the Python code an IDE which can run Python is necessary, since there is no executable provided for teh code (This should be added in the future if the project is continued). The original project was written using jetbrains PyCharm (https://www.jetbrains.com/pycharm/). 
Install the following libraries:
- PyCmdMessenger (https://github.com/harmsm/PyCmdMessenger)
- PyKinect2 (https://github.com/Kinect/PyKinect2)
To make sure the Python code can communicate with the Arduino, the correct port should be filled in the Python file named trackDepth.py. On line 26 the port can be changed to the correct port you noted during the set up of the Arduino code:
'''
port = "COM8" # Edit the port to which the Arduino is connected here
'''

### Calibrating DAHLIA
There are two main spots where DAHLIA can be calibrated. One in the Python code and one in the Arduino code. 
In the Pyhon code the height where people and objects are detected can be edited. To do that you need to change the variables t0 and t1 in the updateBin() function in the trackDepth.py file (line 46-47). 
'''
t0 = 1900   # Edit the upper threshold of the camera here.
t1 = 2600   # Edit the lower threshold of the camera here.
'''
The meaning of these thresholds is as follows. The numbers represent the distance from the Kinect V2 in millimeters. In the original project the Kinect V2 hung at a height of 4,2 meters. This means that with the thresholds in the example the kinect can detect objects that are between (4200 - 2600 =) 1600 and (4200 - 1900 =) 2300 millimeters from the ground. 
To calibrate on the Arduino side you need a little information from the Python code. Uncomment line 83 in the trackDepth.py file. This prints the value that is sent to the Arduino.
'''
# print(len(self.data)) # Uncomment this line for calibration.
'''
Now we can turn to the Arduino code. Go to line 23-24 in the animate.ino file. 
'''
int low_threshold = 21500;  // Calibrate lower pixel threshold here.
int high_threshold = 30000; // Calibrate upper pixel threshold here.
'''
These thresholds mark the borders between the different anmations. These are based on the value sent by the computer to which the Arduino is connected. The lower threshold should be a little higher than the value sent when nobody is on the floor, such that when somebody enters the floor and the value increases it goes over the threshold. The upper threshold should be a little lower then the value when the desired amount of people are on the floor for the celebration to trigger. To find these values you should run the full system with the print line in the python code uncommented. Now you can see the values that are send to the Arduino printed in the terminal. Note the values that are sent when no one is one the floor and when the desired amount of people are on the floor.
When this is done DAHLIA should be properly calibrated and is ready for use.



















