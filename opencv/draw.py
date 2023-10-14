import cv2

img = cv2.imread('Unknown.jpeg',1)

img = cv2.line(img , (0,0) , (255,255) , (0 , 255 , 0) , 1)
img = cv2.rectangle(img , (20,0) , (50,12) ,  (0,0,266), 1)

cv2.imshow('image',img)

cv2.waitKey(0)
cv2.destroyAllWindows()
