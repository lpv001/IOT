import cv2
import numpy as np
import time



# Load Yolo
net = cv2.dnn.readNet("yolov4-tiny-custom_final.weights", "yolov4-tiny-custom.cfg")
classes = []
with open("obj.names", "r") as f:
    classes = [line.strip() for line in f.readlines()]
layer_names = net.getLayerNames()
output_layers = [layer_names[i-1] for i in net.getUnconnectedOutLayers()]
colors = np.random.uniform(0, 255, size=(len(classes), 3))


# Loading image
cap = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_PLAIN
starting_time = time.time()
frame_id = 0



#record
width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

fourcc = cv2.VideoWriter_fourcc(*'XVID')
data = cv2.VideoWriter('your_video.mp4', fourcc, 20.0, (width,height))
while True:
    # net.setPreferableBackend(cv2.dnn.DNN_BACKEND_CUDA)
    # net.setPreferableTarget(cv2.dnn.DNN_TARGET_CUDA)
    _, frame = cap.read()
#    frame = cv2.flip(frame,2)
    frame_id += 1

    height, width, channels = frame.shape

    # Detecting objects
    blob = cv2.dnn.blobFromImage(frame, 0.00392, (416, 416), (0, 0, 0), True, crop=False)

    net.setInput(blob)
    outs = net.forward(output_layers)

    # Showing informations on the screen
    class_ids = []
    confidences = []
    boxes = []
    for out in outs:
        for detection in out:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0:
                # Object detected
                center_x = int(detection[0] * width)
                center_y = int(detection[1] * height)
                w = int(detection[2] * width)
                h = int(detection[3] * height)

                # Rectangle coordinates
                x = int(center_x - w / 2)
                y = int(center_y - h / 2)
                
                boxes.append([x, y, w, h])
                confidences.append(float(confidence))
                class_ids.append(class_id)

    indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.8, 0.3)

    for i in range(len(boxes)):
        if i in indexes:
            x, y, w, h = boxes[i]
            label = str(classes[class_ids[i]])
            confidence = confidences[i]
            #color = colors[class_ids[i]]
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255,51,153), 2)
            cv2.putText(frame, label + " " + str(round(confidence, 2)), (x, y - 10), font, 1.5, (153,0,76), 1)
            
            Center_x = boxes[i][0] + boxes[i][2]//2
            Center_y = boxes[i][1] + boxes[i][3]//2
            # cv2.line(frame, (0,height//2), (width,height//2), (192,192,192), 1)
            # cv2.line(frame, (width//2,0), (width//2,height), (192,192,192), 1)
            
            Area = boxes[i][2]*boxes[i][3]

            print("-->    " + str(Center_x) + "\t" + str(Center_y))


    cTime = time.time()
    fps = 1 / (cTime - starting_time)
    starting_time = cTime
    cv2.putText(frame, "FPS: " + str(round(fps, 2)), (10, 30), font, 2, (0, 0, 255), 1)
    cv2.imshow("Image", frame)
    #data.write(frame)
    key = cv2.waitKey(1)
    if key == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
