import os
import sys
import json
import base64
import time
import traceback

import cv2
import numpy as np

import boto3

s3 = boto3.client('s3')
sns = boto3.client('sns')
sqs = boto3.client('sqs')
textract = boto3.client('textract', 'us-west-2')
s3_bucket = 'avail-cv-ml'

def unpack_img(byte_str):
    jpeg_bytes = base64.b64decode(byte_str)
    np_array = np.frombuffer(jpeg_bytes, dtype=np.uint8)
    image = cv2.imdecode(np_array, cv2.IMREAD_COLOR)
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    return jpeg_bytes

def handler(event, context):
    msg_json = event['Records'][0]['body']

    try:
        obj_key = os.path.join(msg_json['name'], msg_json['console_id'], msg_json['id'])
        response = s3.get_object(Bucket=s3_bucket, Key=obj_key)
        msg_body = response['Body'].read()
        msg_json = json.loads(msg_body)

        msg_json['sts'] = time.time()
        image_bytes = base64.b64decode(msg_json['input_data'])
        response = textract.analyze_document(Document={'Bytes': image_bytes}, FeatureTypes=["TABLES", "FORMS"])
        print("Get textract response ")

        bbox_idx = 0
        texts = []
        bboxs = []
        for block in response['Blocks']:
            if block['BlockType'] == 'LINE':
                x = block['Geometry']['BoundingBox']['Left']
                y = block['Geometry']['BoundingBox']['Top']
                w = block['Geometry']['BoundingBox']['Width']
                h = block['Geometry']['BoundingBox']['Height']
                print(f"Text: {block['Text']}")
                print(f"Bounding box: ({x},{y},{w},{h})")
                bboxs.append([x,y,w,h])
                texts.append(block['Text'])
                msg_json['result'].append({'text':block['Text'], 'bbox':[x,y,w,h]})
                bbox_idx += 1
        msg_json['ets'] = time.time()
        print(f"Detected box={bbox_idx}")
        # update s3 object
        s3.put_object(Bucket=s3_bucket, Key=obj_key, Body=json.dumps(msg_json))

    except:
        print(f"Exception: {traceback.print_exc()}")

    result = {"res":"We done!"}
    
    return {
        'statusCode': 200,
        'body': json.dumps(result)
    }
    
