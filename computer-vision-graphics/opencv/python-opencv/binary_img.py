import cv2
import numpy as np

# Create a blank white image (640x360)
width, height = 640, 360
blank_image = np.zeros((height, width, 3), dtype=np.uint8)
blank_image.fill(255)  # Fill with white color (255, 255, 255)

# Define a list of bounding boxes with (x1, y1, x2, y2) coordinates
bounding_boxes = [(100, 200, 250, 400),   # Example bounding box 1
                  (150, 250, 300, 500)]   # Example bounding box 2

# Draw bounding boxes on the blank image
for box in bounding_boxes:
    x1, y1, x2, y2 = box
    cv2.rectangle(blank_image, (x1, y1), (x2, y2), (0, 0, 0), -1)  # Draw filled black rectangles

# Convert the image to a binary image (thresholding)
gray_image = cv2.cvtColor(blank_image, cv2.COLOR_BGR2GRAY)
_, binary_image = cv2.threshold(gray_image, 128, 255, cv2.THRESH_BINARY)

# Display the binary image
cv2.imshow('Binary Image', binary_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
