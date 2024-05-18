#!/Users/royzheng/miniconda3/bin/python

import argparse
import datetime
from pytz import utc
import json
import base64

import boto3
import botocore

from utils import print_info

s3 = boto3.client('s3')
bucket_name = 'avail-cv-ml'

def main():
    # Hour limit for the file, default 6 months 
    time_limit = 183 * 24 
    file_prefix = None
    file_extension = None
    do_fetch = False
    
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--do_fetch', type=str, help='y to perform fetching, default n')
    parser.add_argument('-b', '--bucket_prefix', required=True, type=str, help='string for bucket prefix')
    parser.add_argument('-t', '--time_limit', type=int, help='previous hours, default 6 months')
    parser.add_argument('-p', '--file_prefix', type=str, help='file prefix like Input, default None')
    parser.add_argument('-e', '--file_extension', type=str, help='file extension like png, jpg, default None')

    args = parser.parse_args()
    if args.do_fetch is not None:
        do_fetch = True 
    if args.bucket_prefix is not None:
        bucket_prefix = args.bucket_prefix
    if args.time_limit is not None:
        time_limit = args.time_limit
    if args.file_prefix is not None:
        file_prefix = args.file_prefix
    if args.file_extension is not None:
        file_extension= args.file_extension

    hours_ago = datetime.datetime.now(tz=utc) - datetime.timedelta(hours=time_limit)
    keys = []
    resp = s3.list_objects_v2(Bucket=bucket_name, Prefix=bucket_prefix)
    for obj in resp['Contents']:
        if obj['LastModified'] > hours_ago:
            keys.append(obj['Key'])

    if file_extension is not None:
        keys = [k for k in keys if k.endwith('.'+file_extension)]
        
    if file_prefix is not None:
        keys = [k for k in keys if k.startswith(file_prefix)]

    for key in keys:
        print_info(f"key={key}")
        try:
            if do_fetch:
                s3.download_file(bucket_name, key, key.split('/')[-1])
        except botocore.exceptions.ClientError as e:
            if e.response['Error']['Code'] == "404":
                print("Object does not exist")
            else:
                raise
    if do_fetch:
        print_info("Download complete")

if __name__=='__main__':
    main()
