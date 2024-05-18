#!/usr/bin/python
'''
import numpy as np
import cv2
import sys
# Load image as string from file/database    
fd = open('IM1')
img_str = fd.read()
fd.close()

#img_array = np.asarray(bytearray(img_str), dtype=np.uint8)
#print("image h,w=%s"%(img_array.shape)) 
#img = ... Conversion to Mat graycolor

#cv2.imshow('rawgrayimage', img)
#cv2.waitKey(0)
''' 

import cv2
import numpy as np

#read the data from the file
with open('IM1', 'rb') as infile:
     buf = infile.read()

#use numpy to construct an array from the bytes
x = np.fromstring(buf, dtype='uint8')

#decode the array into an image
img = cv2.imdecode(x, cv2.IMREAD_UNCHANGED)

#show it
cv2.imshow("some window", img)
cv2.waitKey(0)
