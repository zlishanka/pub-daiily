import os
import json
import base64
import time
from cryptography.fernet import Fernet
import traceback

import boto3

s3_client = boto3.client('s3')
sqs_client = boto3.client('sqs')
textract_client = boto3.client('textract', 'us-west-2') 

sqs_url = 'avail-cv-ml-service-phi-text-queue'
s3_bucket = 'avail-cv-ml'

# Receive messages from queue
while True:
    resp = sqs_client.receive_message(QueueUrl=sqs_url, MaxNumberOfMessages=1)
    
    if 'Messages' in resp:
        message = resp['Messages'][0]
        msg_json = json.loads(message['Body'])
        print(msg_json)
        sqs_client.delete_message(QueueUrl=sqs_url, ReceiptHandle=message['ReceiptHandle'])
       
        try:
            obj_key = os.path.join(msg_json['name'], msg_json['console_id'], msg_json['id'])
            response = s3_client.get_object(Bucket=s3_bucket, Key=obj_key)
            msg_body = response['Body'].read()
            msg_json = json.loads(msg_body) 
            
            msg_json['sts'] = time.time()
        
            image_bytes = base64.b64decode(msg_json['input_data']) 
            response = textract_client.analyze_document(Document={'Bytes': image_bytes}, FeatureTypes=["TABLES", "FORMS"])
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
            s3_client.put_object(Bucket=s3_bucket, Key=obj_key, Body=json.dumps(msg_json)) 
             
        except:
            print(f"Exception: {traceback.print_exc()}")
            #print(error.response['Error']['Code'])
            #print(error.response['Error']['Message'])  
        
    else:
        #print("No messages in queue")
        pass

