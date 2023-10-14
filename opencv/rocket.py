import cv2
import numpy as np

cap = cv2.VideoCapture(0)

lower_pin = np.array([155, 135, 55])
upper_pin = np.array([175, 255, 255])

#lower_pin = np.array([135, 50, 20])
#upper_pin = np.array([170, 400, 255])
width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
#fourcc = cv2.VideoWriter_fourcc(*'XVID')
#out = cv2.VideoWriter('your_video.mp4', fourcc, 20.0, (width,height))
while True:
	ret, frame = cap.read()
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
	mask = cv2.inRange(hsv, lower_pin, upper_pin)
	contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	contours = sorted(contours,key=lambda x:cv2.contourArea(x),reverse=True)
	
	if len(contours) != 0:
		for contour in contours:	
			if cv2.contourArea(contour) > 60:
				x, y, w, h = cv2.boundingRect(contour)
				#cv2.rectangle(frame, (x,y), (x+w,y+h),(0,255,0), 2)
				font = cv2.FONT_HERSHEY_SIMPLEX
				strXY = str(x+w/2) + ', ' + str(y+h/2)
				cv2.putText(frame, strXY, (20,40), font, 1, (0,255,40), 2)
				Center_ObjectX = int(x + w/2)
				Center_ObjectY = int(y + h/2)

				Center_frameX = int(width/2)
				Center_frameY = int(height/2)
				#cv2.line(frame, (0,Center_ObjectY), (width,Center_ObjectY), (123,213,123), 1)
				#cv2.line(frame, (Center_ObjectX,0), (Center_ObjectX,height), (123,213,123), 1)
				#cv2.line(frame, (0,Center_ObjectY+2), (width,Center_ObjectY+2), (123,213,123), 1)
				#cv2.line(frame, (Center_ObjectX+2,0), (Center_ObjectX+2,height), (123,213,123), 1)
				
				

	cv2.imshow("Frame",frame)
	cv2.imshow("Mask",mask)
#	out.write(frame)
	
	key = cv2.waitKey(1)
	if key == ord('q'):
		break

cap.release()
cv2.destroyAllWindows()
