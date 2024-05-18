import boto3
import time

s3 = boto3.client('s3')

bucket = 'avail-cv-ml'
key = 'original-operating-room-1080p/latency-test'
data = b'0123456789' * 1000 # 10KB of data

start_time = time.time()

#s3.put_object(Bucket=bucket, Key=key, Body=data)
s3.get_object(Bucket=bucket, Key=key) 
end_time = time.time()

latency = end_time - start_time

print(f"S3 upload latency: {latency:.2f} seconds")
