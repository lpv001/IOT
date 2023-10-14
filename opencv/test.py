import cv2

def filter_img(frame):
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	blur = cv2.GaussianBlur(gray, (5,5), 0)
	_, thresh = cv2.threshold(blur, 20 , 255 , cv2.THRESH_BINARY)
	dilated = cv2.dilate(thresh, None, iterations = 3 )
	return dilated

cap = cv2.VideoCapture("para.mp4")


ret, frame1 = cap.read()
ret, frame2 = cap.read()

while cap.isOpened():
	diff = cv2.absdiff(frame1 , frame2)
	mask = filter_img(diff)	

	contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	for contour in contours:
		(x, y, w, h) = cv2.boundingRect(contour)
		if cv2.contourArea(contour) < 2000:
			continue
		cv2.rectangle(frame1, pt1 = (x, y), pt2 = (x+w,y+h), color=(0,255,0), thickness=2)
	

	cv2.imshow("Frame", frame1)
	cv2.imshow("Mask",diff)

	frame1 = frame2
	ret, frame2 = cap.read()

	if cv2.waitKey(50) == ord("q"):
		break

cap.release()
cv2.destroyAllWindows()
