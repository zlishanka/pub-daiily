import json
import base64
from datetime import datetime
import time 
import sys 
from cryptography.fernet import Fernet

import cv2
import boto3

def print_info(msg):
    print(str(datetime.now()) + ' [Info] ' + msg)
    sys.stdout.flush() 

def overlay_boxes(image, boxes):
    ih, iw = image.shape[:2]    
    for box in boxes:
        x, y, w, h = box
        x = int(x * iw)
        y = int(y * ih)
        w = int(w * iw)
        h = int(h * ih)
        cv2.rectangle(image, (x,y), (x+w, y+h), (0,255,0), 2)
        
    alpha = 0.5 
    cv2.addWeighted(image, alpha, image, 1 - alpha, 0, image)
    return image 

img_file = '/Users/royzheng/Documents/PHIData1-1080p/test_ocr.png'

fp = open('config.json')
aws_config = json.load(fp)
key = base64.b64decode(aws_config['key'].encode())
access_key = base64.b64decode(aws_config['access_key'].encode())
access_secret = base64.b64decode(aws_config['access_secret'].encode())

f = Fernet(key)
session = boto3.Session(
    aws_access_key_id=f.decrypt(access_key).decode(),
    aws_secret_access_key=f.decrypt(access_secret).decode()
)
textract = session.client('textract', region_name='us-west-2')
comprehend = session.client('comprehend', region_name='us-west-2')


with open(img_file, 'rb') as image_file:
    image_bytes = image_file.read()
    print(image_bytes)

image = cv2.imread(img_file) 

print_info("Start to send img to textract for analysis ...")
#response = textract.detect_document_text(Document={'Bytes': image_bytes}, FeatureTypes=["TABLES", "FORMS"])
response = textract.analyze_document(Document={'Bytes': image_bytes}, FeatureTypes=["TABLES", "FORMS"])
print_info("Get textract response ")

box_idx = 0
texts = []
bboxs = []
for block in response['Blocks']:
    if block['BlockType'] == 'LINE':
        x = block['Geometry']['BoundingBox']['Left']
        y = block['Geometry']['BoundingBox']['Top']
        w = block['Geometry']['BoundingBox']['Width']
        h = block['Geometry']['BoundingBox']['Height']
        print_info(f"Text: {block['Text']}")
        print_info(f"Bounding box: ({x},{y},{w},{h})")
        bboxs.append([x,y,w,h])
        texts.append(block['Text'])
        box_idx += 1

print_info(f"Detected box={box_idx}") 

for text in texts:
    comprehend_response = comprehend.detect_entities(Text=text, LanguageCode='en') 
    for entity in comprehend_response['Entities']:
        print_info(f"- {entity['Type']} - {entity['Text']}")

image = overlay_boxes(image, bboxs)
cv2.imshow("overlayed box",image) 
cv2.waitKey(0) 

cv2.destroyAllWindows()
