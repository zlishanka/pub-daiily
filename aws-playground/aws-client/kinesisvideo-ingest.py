import json
import base64
from cryptography.fernet import Fernet

import boto3

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
kvs_client = session.client('kinesisvideo', region_name='us-west-2')

stream_name = 'my-video-stream'

# Get Kinesis Video Stream handle
stream_handle = kvs_client.get_data_endpoint(
    StreamName=stream_name,
    APIName='PUT_MEDIA'
)['DataEndpoint']

# Open video capture device
cap = cv2.VideoCapture(0) 

while True:
    # Capture each frame
    ret, frame = cap.read() 
    
    # Convert to bytes
    _, image_bytes = cv2.imencode('.jpg', frame) 
    
    # Put frame into Kinesis Video Stream
    kvs_client.put_media(
        StreamName=stream_name,
        FragmentTimecodeType='ABSOLUTE',
        ProducerStartTime=0,
        Data=image_bytes.tostring(),
        StreamARN=stream_handle['ResourceARN']
    )

# Release video capture  
cap.release()
