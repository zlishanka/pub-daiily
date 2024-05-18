import json
import base64
from datetime import datetime
import time
import sys
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
ec2_client = session.client('ec2', region_name='us-west-2')

# Describe the instances.
response = ec2_client.describe_instances()

# Extract the current state of the instance from the response.
instances = response['Reservations'][0]['Instances']

# Print the instance ID and status.
for instance in instances:
    instance_id = instance['InstanceId']
    instance_state = instance['State']['Name']
    print(f"{instance_id} - {instance_state}")
