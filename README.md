# DAHLIA
The DAHLIA project was created for the Interactive Environments minor 2019-2020 at the TU Delft (Delft Univercity of Technology). This repository holds the software which makes  the DAHLIA floor work. The Python code enables a computer to collect depth frames from a Kinect v2 and process them. After processing the frames, it sends data to an Arduino with the Arduino code in this repository installed on it. The Arduino code uses the data send to it to display different patterns on the floor.

## Getting Started
These instructions should enable you to set up DAHLIA after the phisical structure has been build. 

### Setting Up the Hardware
To run the software the hardware should be connected properly to the computer you want to use. This computer should have an USB 3.0 port, because the Kinect v2 needs to be connected via USB 3.0 to function. The Arduino should be connected via some other USB port. 
Since the Arduino needs to control 467 LEDs it needs a lot of memory. The original project used an Arduino Due, but another board with similar hardware should work fine.

### Setting Up the Arduino Code
To be able to edit and upload code to the Arduino you can use the standard IDE provided by Arduino (https://www.arduino.cc/en/main/software). To calibrate 

