import cv2
import glob
import time 

# Load the cascade
#face_cascade = cv2.CascadeClassifier('../opencv/data/haarcascades/haarcascade_frontalface_alt_tree.xml')
face_cascade = cv2.CascadeClassifier('../opencv/data/haarcascades/haarcascade_frontalface_default.xml')
eyes_cascade = cv2.CascadeClassifier('../opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml')

for file in glob.glob("input/*.jpg"):
    
    # Read the input image
    t1 =  time.time()*1000.0 
    img = cv2.imread(file)
    
    height, width = img.shape[:2] 
    
    # resize image to width=640 
    scaling_factor = 640./width 
    img = cv2.resize(img, None, fx=scaling_factor, fy=scaling_factor, interpolation=cv2.INTER_AREA) 
    # Convert into grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Detect faces
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)
    # Draw rectangle around the faces
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        faceROI = gray[y:y+h,x:x+w]
        #-- In each face, detect eyes
        eyes = eyes_cascade.detectMultiScale(faceROI)
        for (x2,y2,w2,h2) in eyes:
            eye_center = (x + x2 + w2//2, y + y2 + h2//2)
            radius = int(round((w2 + h2)*0.25))
            frame = cv2.circle(img, eye_center, radius, (255, 0, 0 ), 4)
    t_diff = time.time() * 1000.0 - t1 
    print("file %s, width=%s, height =%s, detect_time=%s ms"%(file, width, height, t_diff))
    # save image to result directory s
    cv2.imwrite('result/'+file.split('/')[1],img)
    cv2.imshow('img', img)
    cv2.waitKey(0)
    cv2.destroyWindow('img')
    cv2.waitKey(1)
    
    
cv2.destroyAllWindows()
cv2.waitKey(1)
