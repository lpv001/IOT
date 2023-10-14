import cv2
import numpy as np

cap = cv2.imread('rocket.jpg')

lower_pin = np.array([0, 0, 0])
upper_pin = np.array([50, 100, 55])

#lower_pin = np.array([135, 50, 20])
#upper_pin = np.array([170, 400, 255])
# width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
# height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

while True:
	frame = cv2.imread('rocket.jpg')
	dimensions = frame.shape
	height = frame.shape[0]
	width = frame.shape[1]
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

	mask = cv2.inRange(hsv, lower_pin, upper_pin)
	contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	contours = sorted(contours,key=lambda x:cv2.contourArea(x),reverse=True)
	
	# if len(contours) != 0:
	# 	for contour in contours:	
	# 		if cv2.contourArea(contour) > 1000:
	# 			x, y, w, h = cv2.boundingRect(contour)
	# 			cv2.rectangle(frame, (x,y), (x+w,y+h), (0,255,0), 3)
	# 			font = cv2.FONT_HERSHEY_SIMPLEX
	# 			strXY = str(x+w/2) + ', ' + str(y+h/2)
	# 			cv2.putText(frame, strXY, (20,40), font, 1, (0,255,40), 2)
	# 			Center_ObjectX = int(x + w/2)
	# 			Center_ObjectY = int(y + h/2)

	if len(contours) != 0:
		area = [cv2.contourArea(c) for c in contours]
		max_index = np.argmax(area)
		cnt = contours[max_index]
		x, y, w, h = cv2.boundingRect(cnt)
		cv2.rectangle(frame, (x,y), (x+w,y+h), (0,255,0), 3)
		font = cv2.FONT_HERSHEY_SIMPLEX
		strXY = str(x+w/2) + ', ' + str(y+h/2)
		cv2.putText(frame, strXY, (20,40), font, 1, (0,255,40), 2)
				
				
    
				
				

	cv2.imshow("Frame",frame)
	cv2.imshow("Mask",mask)
	
	
	key = cv2.waitKey(1)
	if key == ord('q'):
		break

frame.release()
cv2.destroyAllWindows()
