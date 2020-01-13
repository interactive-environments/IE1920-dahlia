import PyCmdMessenger as cmd

arduino = cmd.ArduinoBoard("COM7", baud_rate=9600)
commands = [["coords", "i*"]]
c = cmd.CmdMessenger(arduino, commands)

def sendData(data):
    args = [2*len(data)]
    for cord in data:
        args.append(cord[0])
        args.append(cord[1])
    print(args)
    c.send("coords", *args)

test = [(1,2), (3,4)]
sendData(test)
