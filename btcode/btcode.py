import urllib.request

hostname = "localhost:8000"
package = "initial/"

def httpSend(pitch,roll, yaw):
    return urllib.request.url(hostname + "/" + package + str(float(pitch)) + "/"+ str(float(roll)) + "/"+ str(float(yaw)) + "/").read()

def do_nothing():
    return

def bluetooth_client():
    w = 1
    while (w):
        pitch = 0
        roll = 0
        yaw = 0
        #get bluetooth data
        #while Not Recive Data and connected device
        while(1):
            do_nothing()#wait for data
        #if disconnected device
        if(1):
            w = 0
        else:
            httpSend(pitch,roll,yaw)
        #data recived
        

#bluetooth_client()
