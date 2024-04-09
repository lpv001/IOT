import cv2
import numpy as np
print(cv2.__version__)
from adafruit_servokit import ServoKit
import time

kit = ServoKit(channels=16)

pan = 90
tilt = 90
kit.servo[0].angle = pan
kit.servo[1].angle = tilt

def nothing(x):
    pass

cv2.namedWindow('Trackbars')
cv2.moveWindow('Trackbars',1320,0)

cv2.createTrackbar('hueLower','Trackbars',168,179,nothing)
cv2.createTrackbar('hueUpper','Trackbars',179,179,nothing)
cv2.createTrackbar('hue2Lower','Trackbars',0,179,nothing)
cv2.createTrackbar('hue2Upper','Trackbars',0,179,nothing)
cv2.createTrackbar('satLow','Trackbars',190,255,nothing)
cv2.createTrackbar('satHigh','Trackbars',246,255,nothing)
cv2.createTrackbar('valLow','Trackbars',0,255,nothing)
cv2.createTrackbar('valHigh','Trackbars',255,255,nothing)


#dispW = 320
#dispH = 240 #60fps

dispW = 640
dispH = 480 #60fps

#dispW = 960
#dispH = 540 #60fps

#dispW = 1280
#dispH = 720 #30fps
flip = 2

cam=cv2.VideoCapture(2)
cam.set(cv2.CAP_PROP_FRAME_WIDTH,dispW)
cam.set(cv2.CAP_PROP_FRAME_HEIGHT,dispH)
pTime = time.time()
while True:
    ret, frame = cam.read()
    frame = cv2.flip(frame,flip)

    #converting color to HSV
    hsv=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

    #reading track value from trackbar
    hueLow = cv2.getTrackbarPos('hueLower','Trackbars')
    hueUp = cv2.getTrackbarPos('hueUpper','Trackbars')
    hue2Low = cv2.getTrackbarPos('hue2Lower','Trackbars')
    hue2Up = cv2.getTrackbarPos('hue2Upper','Trackbars')

    Ls = cv2.getTrackbarPos('satLow','Trackbars')
    Us = cv2.getTrackbarPos('satHigh','Trackbars')

    Lv = cv2.getTrackbarPos('valLow','Trackbars')
    Uv = cv2.getTrackbarPos('valHigh','Trackbars')

    #creating an array for the track value
    l_b = np.array([hueLow,Ls,Lv])
    u_b = np.array([hueUp,Us,Uv])
    l_b2 = np.array([hue2Low,Ls,Lv])
    u_b2 = np.array([hue2Up,Us,Uv])

    #creating FG mask in range of track value array
    FGmask = cv2.inRange(hsv,l_b,u_b) #if that pixel in range, it gonna turn white, if not, black
    FGmask2 = cv2.inRange(hsv,l_b2,u_b2)
    FGmaskComp = cv2.add(FGmask,FGmask2)
    cv2.imshow('FGmaskComp',FGmaskComp)
    cv2.moveWindow('FGmaskComp',705,0)

    #creating the contours
    contours,_ = cv2.findContours(FGmaskComp,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)

    #sort the contours, we need the bigger one! (to deal with background noise)
    contours = sorted(contours,key=lambda x:cv2.contourArea(x),reverse=True) #reverse = true means, it will start sorting from the bigger to smaller

    #To step through the list of contours. (to track more than 1 object)
    for cnt in contours:
        area = cv2.contourArea(cnt)
        (x,y,w,h) = cv2.boundingRect(cnt)
        if area >=50:
            #cv2.drawContours(frame,[cnt],0,(255,0,0),3) #now cnt is the list, better put []!
            cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),3)
            #Calculate the center of the rectangle
            objX = x + w/2
            objY = y + h/2
            #Calculate the error between center of the rectangle and the webcam center
            errorPan = objX - dispW/2
            errorTilt = objY - dispH/2
            #tracking by minimizing error, so that the center of the retangle and the center of webcam is coincidence
            #print('Error',errorPan,errorTilt)
            if abs(errorPan) > 20:
                pan = pan + errorPan/80
            if abs(errorTilt) > 20:
                tilt = tilt - errorTilt/80
            #print('pos',pan,tilt)   
            if pan > 180:
                pan = 180
                print('Pan is out of range!')
            if tilt > 180:
                tilt = 180
                print('tilt is out of range!')
            if pan < 0:
                pan = 0
                print('pan is out of range!')
            if tilt < 0:
                tilt = 0
                print('tilt is out of range!')

            kit.servo[0].angle = pan
            kit.servo[1].angle = tilt
            break

    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime
    cv2.putText(frame, f'fps: {int(fps)}', (0, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255))
    #cv2.drawContours(frame,contours,0,(255,0,0),3) #-1 to draw all the contours, 0 means the first one

    cv2.imshow('WebCam',frame)
    cv2.moveWindow('WebCam',0,0)

    if cv2.waitKey(1)==ord('q'):
        break
cam.release()
cv2.destroyAllWindows()