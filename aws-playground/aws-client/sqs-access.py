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
sqs_client = session.client('sqs')

queue_url = aws_config['sqs']['service']['phi-text'] 
#topic_arn = 'arn:aws:sns:us-east-1:123456789012:myTopic'

# Subscribe queue to topic
#sns.subscribe(TopicArn=topic_arn, Protocol='sqs', Endpoint=queue_url)

# Receive messages from queue
while True:
    resp = sqs_client.receive_message(QueueUrl=queue_url, MaxNumberOfMessages=1)
    
    if 'Messages' in resp:
        message = resp['Messages'][0]
        print(message['Body'])
        
        # Delete received message from queue
        sqs_client.delete_message(QueueUrl=queue_url, ReceiptHandle=message['ReceiptHandle'])
    else:
        #print("No messages in queue")
        pass

