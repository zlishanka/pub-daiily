import cv2
import glob

# Load the cascade
#face_cascade = cv2.CascadeClassifier('../opencv/data/haarcascades/haarcascade_frontalface_alt_tree.xml')
face_cascade = cv2.CascadeClassifier('../opencv/data/haarcascades/haarcascade_frontalface_default.xml')

for file in glob.glob("*.jpg"):
    
    # Read the input image
    img = cv2.imread(file)
    print("file %s, width=%s, height = %s"%(file, img.shape[1], img.shape[0]))
    # Convert into grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Detect faces
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)
    # Draw rectangle around the faces
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        
    # Display the output
    cv2.imshow('img', img)
    cv2.waitKey(0)
    cv2.waitKey(1)
    

cv2.destroyAllWindows()
cv2.waitKey(1)
cv2.waitKey(1)