#!/Users/royzheng/miniconda3/bin/python

import pytube 
import argparse
import sys 
import traceback 

# default download is to choose low quality for audio extraction 
# use "-q 1" to select high quality download 
parser = argparse.ArgumentParser() 
parser.add_argument('-u', '--download_url', type=str)
parser.add_argument('-q', '--high_quality_video', type=bool)

args = parser.parse_args()
high_quality = False

if args.download_url is None:
    print("down_tube.py -u <download url> -q <optional, quality, high 1, low 0>")  
    sys.exit(0) 

# we save it i the current working directory 
video_url = args.download_url

if args.high_quality_video is not None: 
    high_quality = args.high_quality_video

print("Start to download video from %s  with high video quality=%s ... "%(video_url, high_quality)) 

try: 
	# Create an instance of youtube video 
	video_instance = pytube.YouTube(video_url) 
except:
	traceback.print_exc()

if high_quality:
    stream = video_instance.streams.get_highest_resolution() 
else:
    stream = video_instance.streams.get_lowest_resolution() 

# download 
stream.download() 

print("Done.") 

