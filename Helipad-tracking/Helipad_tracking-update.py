import numpy as np
import argparse
import cv2
import os
import time
import matplotlib.pyplot as plt
from drawnow import *
from adafruit_servokit import ServoKit
import pickle

print(cv2.__version__)

myKit = ServoKit(channels=16) #assign all chanels

#initialize gimbal position
pan = 90
tilt = 90
myKit.servo[0].angle=pan
myKit.servo[1].angle=tilt

#creating lists for plotting a live graph
panx_e = []
tilty_e = []

plt.ion() #interactive mode to plot live data

def makeFig(): #For plotting a live graph
    plt.grid(True)
    plt.xlabel('time')
    plt.ylabel('Error')
    plt.title('Error vs time of live tracking')
    plt.plot(panx_e, label='Error_x')
    plt.legend(loc='upper right')
    plt.plot(tilty_e, label='Error_y')
    plt.legend(loc='upper right')

def extract_boxes_confidences_classids(outputs, confidence, width, height):
    boxes = []
    confidences = []
    classIDs = []

    for output in outputs:
        for detection in output:
            # Extract the scores, classid, and the confidence of the prediction
            scores = detection[5:]
            classID = np.argmax(scores)
            conf = scores[classID]

            # Consider only the predictions that are above the confidence threshold
            if conf > confidence:
                # Scale the bounding box back to the size of the image
                box = detection[0:4] * np.array([width, height, width, height])
                centerX, centerY, w, h = box.astype('int')

                # Use the center coordinates, width and height to get the coordinates of the top left corner
                x = int(centerX - (w / 2))
                y = int(centerY - (h / 2))

                boxes.append([x, y, int(w), int(h)])
                confidences.append(float(conf))
                classIDs.append(classID)

    return boxes, confidences, classIDs


def draw_bounding_boxes(image, boxes, confidences, classIDs, idxs, colors):
    if len(idxs) > 0:
        for i in idxs.flatten():
            # extract bounding box coordinates
            x, y = boxes[i][0], boxes[i][1]
            w, h = boxes[i][2], boxes[i][3]

            # draw the bounding box and label on the image
            color = [int(c) for c in colors[classIDs[i]]]
            cv2.rectangle(image, (x, y), (x + w, y + h), color, 2)
            text = "{}: {:.4f}".format(labels[classIDs[i]], confidences[i])
            cv2.putText(image, text, (x, y - 5), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)

    return image


def make_prediction(net, layer_names, labels, image, confidence, threshold):
    height, width = image.shape[:2]

    # Create a blob and pass it through the model
    blob = cv2.dnn.blobFromImage(image, 1 / 255.0, (416, 416), swapRB=True, crop=False)
    net.setInput(blob)
    outputs = net.forward(layer_names)

    # Extract bounding boxes, confidences and classIDs
    boxes, confidences, classIDs = extract_boxes_confidences_classids(outputs, confidence, width, height)

    # Apply Non-Max Suppression
    idxs = cv2.dnn.NMSBoxes(boxes, confidences, confidence, threshold)

    return boxes, confidences, classIDs, idxs


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-w', '--weights', type=str, default='custom_yolov4-tiny_4000.weights', help='Path to model weights')
    parser.add_argument('-cfg', '--config', type=str, default='yolov4-tiny-custom.cfg', help='Path to configuration file')
    #parser.add_argument('-l', '--labels', type=str, default='data/obj.names', help='Path to label file')
    parser.add_argument('-c', '--confidence', type=float, default=0.7, help='Minimum confidence for a box to be detected.')
    parser.add_argument('-t', '--threshold', type=float, default=0.5, help='Threshold for Non-Max Suppression')
    #parser.add_argument('-u', '--use_gpu', default=True, action='store_true', help='Use GPU (OpenCV must be compiled for GPU)
    parser.add_argument('-s', '--save', default=True, action='store_true', help='Whether or not the output should be saved')
    parser.add_argument('-sh', '--show', default=True, action="store_false", help='Show output')

    input_group = parser.add_mutually_exclusive_group()
    input_group.add_argument('-i', '--image_path', type=str, default='', help='Path to the image file.')
    input_group.add_argument('-v', '--video_path', type=str, default='', help='Path to the video file.')

    args = parser.parse_args()

    # Get the labels
    #labels = open(args.labels).read().strip() #split('\n')
    labels = ['Landing site']
    # Create a list of colors for the labels
    colors = np.random.randint(0, 255, size=(len(labels), 3), dtype='uint8')

    # Load weights using OpenCV
    net = cv2.dnn.readNetFromDarknet(args.config, args.weights)

    #Use GPU to run the model
    print('Using GPU')
    net.setPreferableBackend(cv2.dnn.DNN_BACKEND_CUDA)
    net.setPreferableTarget(cv2.dnn.DNN_TARGET_CUDA)

    if args.save:
        print('Creating output directory if it doesn\'t already exist')
        os.makedirs('output', exist_ok=True)

    # Get the ouput layer names
    layer_names = net.getLayerNames()
    layer_names = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]


    if args.image_path != '':
        image = cv2.imread(args.image_path)

        boxes, confidences, classIDs, idxs = make_prediction(net, layer_names, labels, image, args.confidence, args.threshold)

        image = draw_bounding_boxes(image, boxes, confidences, classIDs, idxs, colors)

        # show the output image
        if args.show:
            cv2.imshow('Helipad tracking', image)
            cv2.waitKey(0)

        if args.save:
            cv2.imwrite(f'output/{args.image_path.split("/")[-1]}', image)
    else:
        if args.video_path != '':
            cap = cv2.VideoCapture(args.video_path)
        else:
            cap = cv2.VideoCapture(3)
            cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
            cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

        if args.save:
            width = int(cap.get(3))
            height = int(cap.get(4))
            fps = cap.get(cv2.CAP_PROP_FPS)
            name = args.video_path.split("/")[-1] if args.video_path else 'camera.avi'
            out = cv2.VideoWriter(f'output/{name}', cv2.VideoWriter_fourcc('M','J','P','G'), fps, (width, height))
        
        #Loop
        pTime = time.time()
        while cap.isOpened():      
            ret, image = cap.read()
            image = cv2.flip(image,2)
            dispH = image.shape[0]
            dispW = image.shape[1]
            #print("dispH: ", dispH, "dispW: ", dispW)
            if not ret:
                print('Video file finished.')
                break

            #Make prediction on object (Helipad)
            boxes, confidences, classIDs, idxs = make_prediction(net, layer_names, labels, image, args.confidence, args.threshold)

            if len(idxs) > 0:
                for i in idxs.flatten():
                    #extract bounding box coordinates
                    x, y = boxes[i][0], boxes[i][1]
                    w_bbox, h_bbox = boxes[i][2], boxes[i][3]
                    #Calculate center of the bounding box
                    x_c = x + w_bbox//2
                    y_c = y + h_bbox//2
                    #print("x: ", x_c, "y: ", y_c, "w: ", w_bbox, "h: ", h_bbox)
                    #Calculate area of the bounding box
                    Area = w_bbox * h_bbox
                    #Tracking
                    if Area >= 50:
                        errorPan = x_c - dispW//2
                        errorTilt = y_c - dispH//2
                        #Live graph plotting
                        panx_e.append(errorPan)
                        tilty_e.append(errorTilt)
                        #save to txt fileq
                        with open("data.txt", 'wb') as fp:
                            pickle.dump(panx_e, fp)
                        with open("data1.txt", 'wb') as fp:
                            pickle.dump(tilty_e, fp)
                        #Proprtional controller
                        if abs(errorPan) > 13:
                            pan = pan + errorPan/62
                            #print('pan: ',pan)
                        if abs(errorTilt) > 13:
                            tilt = tilt - errorTilt/62
                            #print('tilt: ', tilt)
                        #Putting limitation of servo angle
                        
                        if  pan > 180:
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

                        myKit.servo[0].angle = pan
                        myKit.servo[1].angle = tilt
                        #drawnow(makeFig)
                        break

            #Draw bounding box
            image = draw_bounding_boxes(image, boxes, confidences, classIDs, idxs, colors)
            #Calculate inference time
            t, _ = net.getPerfProfile()
            label = 'Inference time: %.2f ms' % (t * 1000.0 / cv2.getTickFrequency())
            cv2.putText(image, label, (0, 15), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255))

            #Calculate fps
            cTime = time.time()
            fps = 1 / (cTime - pTime)
            pTime = cTime
            cv2.putText(image, f'fps: {int(fps)}', (0, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255))

            #Press q to close the live video
            if args.show:
                cv2.imshow('Helipad tracking', image)
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break

            if args.save:
                out.write(image)

        cap.release()
        if args.save:
            out.release()
    cv2.destroyAllWindows()
