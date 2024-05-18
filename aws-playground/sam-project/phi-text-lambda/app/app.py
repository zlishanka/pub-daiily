import os
import time
import base64
import json
import numpy as np
import traceback
from cryptography.fernet import Fernet

import boto3

fp = open('config.json')
aws_config = json.load(fp)
key = base64.b64decode(aws_config['key'].encode())
access_key = base64.b64decode(aws_config['access_key'].encode())
access_secret = base64.b64decode(aws_config['access_secret'].encode())
s3_bucket = aws_config['s3_bucket']

f = Fernet(key)
session = boto3.Session(
    aws_access_key_id=f.decrypt(access_key).decode(),
    aws_secret_access_key=f.decrypt(access_secret).decode()
)

s3 = session.client('s3')
sqs = session.client('sqs')
textract = session.client('textract', 'us-west-2')


class PhiTextResult():
    def __init__(self, bbox, text, ocr_s, tag_list, ner_s, idx):
        self.bbox = bbox
        self.text = text
        self.ocr_s = ocr_s
        self.tag_list = tag_list
        self.ner_s = ner_s
        self.idx = idx

    def to_json(self):
        return {
            'bbox' : self.bbox,
            'text' : self.text,
            'ocr_s' : self.ocr_s,
            'tag_list' : self.tag_list,
            'ner_s' : self.ner_s,
            'idx' : self.idx
        }

def unpack_img(byte_str):
    jpeg_bytes = base64.b64decode(byte_str)
    np_array = np.frombuffer(jpeg_bytes, dtype=np.uint8)
    return jpeg_bytes

def lambda_handler(event, context):

    msg_json = event
    try:
        msg_json['sts'] = time.time()
        image_bytes = base64.b64decode(msg_json['input_data'])
        response = textract.analyze_document(Document={'Bytes': image_bytes}, FeatureTypes=["TABLES", "FORMS"])
        print("Get textract response ")

        bbox_idx = 0
        results = []
        for block in response['Blocks']:
            if block['BlockType'] == 'LINE':
                x = block['Geometry']['BoundingBox']['Left']
                y = block['Geometry']['BoundingBox']['Top']
                w = block['Geometry']['BoundingBox']['Width']
                h = block['Geometry']['BoundingBox']['Height']
                results.append(PhiTextResult([x,y, x+w, y+h], block['Text'], 0, [], 0, bbox_idx).to_json())
                bbox_idx += 1
        msg_json['ets'] = time.time()
        msg_json['result'] = results
        # update s3 object
        s3_key = os.path.join(msg_json['name'], msg_json['console_id'], msg_json['id'])
        s3.put_object(Bucket=s3_bucket, Key=s3_key, Body=json.dumps(msg_json))
        msg_json['input_data'] = '' 
        
    except:
        print(f"Exception: {traceback.print_exc()}")

    return {
        'statusCode': 200,
        'body': json.dumps(
            {
                "result": json.dumps(msg_json),
            }
        )
    }
