import os
import sys 
import base64
import json
import subprocess
from cryptography.fernet import Fernet
import time
from datetime import datetime
 
import boto3

def print_info(msg):
    print(str(datetime.now()) + ' [Info] ' + msg)
    sys.stdout.flush()

def exec_command(cmd):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, \
                       stderr=subprocess.PIPE, shell=True)
    text = p.stdout.read()
    retcode = p.wait()
    return retcode == 0, text.decode("utf-8")


fp = open('../config.json')
aws_config = json.load(fp)
key = base64.b64decode(aws_config['key'].encode())
access_key = base64.b64decode(aws_config['access_key'].encode())
access_secret = base64.b64decode(aws_config['access_secret'].encode())



jobj1 = {
    "cts": 1697148498.8260355,
    "ets": 0,
    "id": "3fbf3d37-2f9b-4f75-9e00-9f72d84419d1",
    "name": "phi-text",
    "result": [],
    "sts": 0
}

console_id = 'rzheng-laptop'
bucket_prefix = 'phi-text'

# write first jobj1 with key filename
filename = os.path.join(bucket_prefix,console_id, jobj1['id']+'.json')
print_info("Sending jobj1 to s3 key=%s..."%(filename))
s3.put_object(Bucket=bucket_name, Key=filename, Body=json.dumps(jobj1))
print_info("Done sending to s3 key=%s."%(filename))

# retrieve with key
json_obj = json.loads(s3.get_object(Bucket=bucket_name, Key=filename)['Body'].read())
print_info("fetching from s3 key=%s, body=%s"%(filename, json_obj))

# update s3 previous key filename with jobj2 
print_info("Updating json in s3 key=%s..."%(filename))
s3.put_object(Bucket=bucket_name, Key=filename, Body=json.dumps(jobj2))
print_info("Done sending to s3 key=%s."%(filename))

# retrieve with key
json_obj = json.loads(s3.get_object(Bucket=bucket_name, Key=filename)['Body'].read())
print_info("fetching from s3 key=%s, body=%s"%(filename, json_obj))
