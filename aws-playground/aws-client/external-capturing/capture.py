import os
import sys
import subprocess
import argparse
import time
import json
import base64
import shlex
from datetime import datetime


import cv2
import boto3
import objc
from cryptography.fernet import Fernet

# sample interval (10 sec)
sample_interval = 10 

bucket_name = 'avail-cv-ml'
bucket_prefix = 'console-capture'

def print_info(msg):
    print(str(datetime.now()) + ' [Info] ' + msg)
    sys.stdout.flush()

def print_warning(msg):
    print(str(datetime.now()) + ' [Warning] ' + msg)
    sys.stdout.flush()

def print_error(msg):
    print(str(datetime.now()) + ' [Error] ' + msg)
    sys.stdout.flush()

def exec_command(cmd):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, \
                       stderr=subprocess.PIPE, shell=True)
    text = p.stdout.read()
    retcode = p.wait()
    return retcode, text.decode("utf-8")

# Get the mapping device mapping 
def get_device_mapping():

    objc.loadBundle('AVFoundation', bundle_path='/System/Library/Frameworks/AVFoundation.framework', module_globals=globals())
    devices = AVCaptureDevice.devices()

    cam_idx = 0
    device_mapping = {}
    for i, device in enumerate(devices):
        name = device.localizedName()
        if name in ['MINRRAY-TOP','MINRRAY-FRONT']:
            cam_idx += 1
            continue
        if name in ['AV.io 4K Video','AV.io SDI Video','AV.io HD','UVCHDCAP']:
            name = name.strip().replace(' ', '').replace('.','')
            device_mapping[cam_idx] = name
            cam_idx += 1

    return device_mapping

def main():

    # 30 minutes
    captured_duration = 30
    console_id = None
    console_type = None

    parser = argparse.ArgumentParser()
    parser.add_argument('-c', '--console_id', type=str)
    parser.add_argument('-d', '--captured_duration', type=int)

    args = parser.parse_args()

    if args.console_id is None:
        ret, out = exec_command('echo $HOSTNAME')
        if ret != 0:
            console_id = 'generic'
        else:
            console_id = out.strip()
    else:
        console_id = args.console_id

    if args.captured_duration is not None:
        captured_duration = int(args.captured_duration)

    device_map = get_device_mapping()
    if len(device_map) == 0:
        print_error("Cannot find camera devices, exit!")
        sys.exit(0)
 
    print_info("Console ID=%s"%(console_id)) 
    print_info("Captured duration=%s minutes"%(captured_duration)) 
    print_info("External devices map=%s"%(device_map))
    print_info("About to start capture in few seconds..."%(device_map))
    time.sleep(3)

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
    s3 = session.client('s3')
    time_s = time.time()
    time_n = time.time()
    captured_duration = captured_duration * 60
    video_cap = {}
    for idx in device_map.keys():
        video_cap[idx] = cv2.VideoCapture(idx)

    while time_n - time_s < captured_duration:
        time_n = time.time()
        try:
            for idx in device_map.keys():
                if video_cap[idx].isOpened():
                    ret, frame = video_cap[idx].read()
                    if not ret:
                        print_error("Capture fails on device=%s"%(idx))
                        continue
                    if frame is None:
                        print_warning("Empty frame on device=%s"%(idx))
                        continue
                    success, encoded_frame = cv2.imencode('.png', frame)
                    if success:
                        filename = os.path.join(bucket_prefix,console_id, device_map[idx]+'_'+str(int(time_n))+'.png')
                        print_info("Sending capture to s3 key=%s..."%(filename))
                        s3.put_object(Bucket=bucket_name, Key=filename, Body=encoded_frame.tobytes())
                        print_info("Done sending to s3 key=%s."%(filename))
                    else:
                        print_error("Fails to encode frame on device=%s"%(idx))
                        continue
                else:
                    print_warning("device=%s is not opened"%(idx))

            time_e = time.time()
            time.sleep(sample_interval-(time_e-time_n))

        except KeyboardInterrupt:
            print_info("KeyboardInterrupt received. Exiting...")
            for idx in device_map.keys():
                video_cap[idx].release()
            sys.exit(0)

    for idx in device_map.keys():
        video_cap[idx].release()

if __name__ == '__main__':
    main()
