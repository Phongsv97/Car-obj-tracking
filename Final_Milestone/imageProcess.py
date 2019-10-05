import cv2
import numpy as np
import serial
import sys
import os

RANGE = 20

ser = serial.Serial(
    port='/dev/ttyMCC',
    baudrate=115200,
    parity=serial.PARITY_ODD, 
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS 
)

if ser.isOpen():
    ser.close()
ser.open()

def inRange(left,right,top,bottom):
    if left < RANGE:
        if right < RANGE:
            if top < RANGE:
                if bottom < RANGE:
                    return 1

    return 0

video = cv2.VideoCapture(1)
video.set(3, 320)
video.set(4, 240)
screen_width = video.get(3)
screen_height = video.get(4)

y_coord = int(screen_height / 2)
x_coord = int(screen_width / 2)

def main():
    while True:
        if ser.in_waiting > 0:
            print("read: " + str(ser.read()))

        _, frame = video.read()

        hsv = cv2.cvtColor(frame, cv2.COLOR_RGB2HSV)

        low = np.array([50, 100, 75])
        high = np.array([95, 255, 255])
        # create mask
        mask = cv2.inRange(hsv, low, high)
        median = cv2.medianBlur(mask, 15)

        # perfom mask
        kernel = np.ones((10, 10), np.uint8)/225
        dilation = cv2.dilate(median, kernel, iterations=1)
        opening = cv2.morphologyEx(dilation, cv2.MORPH_OPEN, kernel)
        closing = cv2.morphologyEx(dilation, cv2.MORPH_CLOSE, kernel)
        erosion = cv2.erode(closing, kernel, iterations=1)
        
        _, contours, _ = cv2.findContours(erosion, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)
        #get centroid
        if len(contours) > 0:
            c = max(contours, key=cv2.contourArea)
            ((x_object, y_object), radius) = cv2.minEnclosingCircle(c)

            # find
            if(x_object == 0 and y_object == 0):
                ser.write(b'0')
                print('0')
            else:   
                # computing deviation
                x = x_coord - x_object
                y = y_coord - y_object

                # detect object is beyond boundary
                right_band = x_object - x_coord
                left_band = x_coord - x_object
                top_band = y_coord - y_object
                bottom_band = y_object - y_coord

                if(inRange(left_band, right_band, top_band, bottom_band) == 0):
                    # 1 to turn right, 2 to turn left, 3 stop
                    if right_band > RANGE:
                        ser.write(b'1')
                        print('1')
                    elif left_band > RANGE:
                        ser.write(b'2')
                        print('2')

                    # 4 xuong, 5 len
                    if bottom_band > RANGE:
                        ser.write(b'4')
                        print('4')
                    elif top_band > RANGE:
                        ser.write(b'5')
                        print('5')
                else:
                    ser.write(b'0')
                    print('0')

                cv2.circle(frame, (int(x_object), int(y_object)), int(radius), (0, 255, 255), 2)
                cv2.circle(frame, (int(x_object), int(y_object)), 5, (255, 0, 0), -1)
                cv2.circle(frame, (x_coord, y_coord), 5, (0, 0, 255), -1)
                cv2.rectangle(frame, (x_coord - RANGE, y_coord - RANGE),
                            (x_coord + RANGE, y_coord + RANGE), (0, 255, 0), 1)

        cv2.imshow('frame', frame)

        key = cv2.waitKey(1)
        if key == 27:
            break

    video.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()