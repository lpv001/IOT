import cv2
import datetime

width = 720
height = 1280

cap = cv2.VideoCapture("traffic.mp4")
cap.set(3,width)
cap.set(4,height)


while(cap):
	ret, frame = cap.read()
	if ret == True:
		
		font = cv2.FONT_HERSHEY_SIMPLEX
		text = 'Width: ' + str(cap.get(3)) + ' Height: ' + str(cap.get(4))
		datet = str(datetime.datetime.now())
		cv2.putText(frame , datet , (10,50) , font , 1 , (0,255,255) , 2 , cv2.LINE_AA) 
		cv2.imshow('frame',frame)

		if cv2.waitKey(1) & 0xFF == ord('q'):
			break
	else:
		break
cap.release()
cv2.destroyAllWindows()
