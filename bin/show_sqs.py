#!/Users/royzheng/miniconda3/bin/python
import json
import boto3

sqs = boto3.client('sqs')

queue_url = 'avail-cv-ml-service-phi-text-queue'

# Receive messages from queue
while True:
    resp = sqs.receive_message(QueueUrl=queue_url, MaxNumberOfMessages=1)
    
    if 'Messages' in resp:
        print("SQS message - ")
        message = resp['Messages'][0]
        # Delete received message from queue
        sqs.delete_message(QueueUrl=queue_url, ReceiptHandle=message['ReceiptHandle'])
        print(json.dumps(message['Body']))
        print("Enter y to continue and other key to exit: ")
        user_input = input()
        if user_input != 'y':
            break
    else:
        print("No messages in queue")
        break
