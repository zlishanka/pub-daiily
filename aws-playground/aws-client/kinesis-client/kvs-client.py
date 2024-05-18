import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst

#import gst 

import boto3
import sys
import json
import base64
import subprocess
from cryptography.fernet import Fernet 

fp = open('config.json')
aws_config = json.load(fp)
key = base64.b64decode(aws_config['key'].encode())
access_key = base64.b64decode(aws_config['access_key'].encode())
access_secret = base64.b64decode(aws_config['access_secret'].encode())
kinesis_stream_name = aws_config['kvs-stream']

f = Fernet(key)
session = boto3.Session(
    aws_access_key_id=f.decrypt(access_key).decode(),
    aws_secret_access_key=f.decrypt(access_secret).decode()
)
aws_access_key_id=f.decrypt(access_key).decode(),
aws_secret_access_key=f.decrypt(access_secret).decode()
#kinesis_client = session.client('kinesisvideo', region_name='us-west-2')

'''

# Initialize GStreamer
Gst.init(None)

# Create a GStreamer pipeline
pipeline = Gst.Pipeline()

# GStreamer pipeline definition for capturing video and audio and sending to Kinesis

# Set up webcam video source
video_source = Gst.ElementFactory.make("avfvideosrc", "video_source")
video_source.set_property("device-index", 0) 

# Set up audio source from default microphone
#audio_source = Gst.ElementFactory.make("avfaudiosrc", "audio_source")
#audio_source.set_property("device-index", 0) 

# Encode video as H.264
video_encoder = Gst.ElementFactory.make("x264enc", "video_encoder")
video_encoder.set_property("tune", "zerolatency")
video_encoder.set_property("bitrate", 2000)

# Encode audio with OPUS
#audio_encoder = Gst.ElementFactory.make("opusenc", "audio_encoder")

# KVS sink to ingest stream
# Create elements for video source, video converter, video encoder, and video sink
# Add elements to the pipeline
pipeline.add(video_source)
pipeline.add(videoconvert)
pipeline.add(x264enc)
pipeline.add(videosink)

# Link elements in the pipeline
videosrc.link(videoconvert)
videoconvert.link(x264enc)
x264enc.link(videosink)

# Set the pipeline to the PLAYING state
pipeline.set_state(Gst.State.PLAYING)

# Start the GStreamer main loop
main_loop = Gst.MainLoop.new(None, False)
main_loop.run()

# Clean up when done
pipeline.set_state(Gst.State.NULL)

'''

# Create a GStreamer pipeline
Gst.init(None)
pipeline = Gst.Pipeline()

# Create the video source element
video_source = Gst.ElementFactory.make('autovideosrc', 'video_source')
pipeline.add(video_source)

# Create the audio source element
audio_source = Gst.ElementFactory.make('autoaudiosrc', 'audio_source')
pipeline.add(audio_source)

# Create the Kinesis Video Stream sink element
kinesis_sink = Gst.ElementFactory.make('kvssink', 'kinesis_sink')
if kinesis_sink is None:
    print('Failed to create Kinesis Video Stream sink element.')
    exit(1)

kinesis_sink.set_property('stream-name', 'avail-cv-ml-streaming-test1')
kinesis_sink.set_property(Gst.caps_from_string('access-key-id="%s"' % (aws_access_key_id)))
kinesis_sink.set_property(Gst.caps_from_string('secret-access-key="%s"' % (aws_secret_access_key)))
kinesis_sink.set_property(Gst.caps_from_string('region="%s"' % 'us-west-2'))
#kinesis_sink.set_property('access-key-id', aws_access_key_id)
#kinesis_sink.set_property('secret-access-key', aws_secret_access_key)
#kinesis_sink.set_property('region', 'us-west-2')
pipeline.add(kinesis_sink)

# Link the elements together
video_source.link(kinesis_sink)
audio_source.link(kinesis_sink)

# Set the pipeline to state PLAYING
pipeline.set_state(Gst.State.PLAYING)

# Start streaming
pipeline.get_by_name('video_source').set_property('num-buffers', 10)
pipeline.get_by_name('audio_source').set_property('num-buffers', 10)

# Wait for the pipeline to finish
pipeline.wait_for_state(Gst.State.NULL)

# Clean up
pipeline.set_state(Gst.State.NULL)
