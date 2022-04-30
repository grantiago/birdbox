#!/bin/bash
#########
# for youtube livestream 
# https://stackoverflow.com/questions/39660547/how-to-live-stream-youtube-without-audio
# script template here: 
# https://www.nemdub.com/video-live-stream-on-youtube-from-a-raspberry-pi 
# ubuntu 20. lamp stack 
#########

STREAM_KEY="key" # YouTube Stream Key
CAMERA_USERNAME="test"
CAMERA_PASSWORD="test"
CAMERA_IP_ADDRESS="192.168.1.50"
CAMERA_PORT="8554"
CAMERA_DIR="mjpeg/1"
RTSP_SOURCE="rtsp://$CAMERA_IP_ADDRESS:8554/mjpeg/1"
YOUTUBE_URL="rtmp://a.rtmp.youtube.com/live2" # Base YouTube RTMP URL
VBR="5200k" # Bitrate

args()
#args+=('-hide_banner')
#args+=('-loglevel debug')
args+=('-re')
args+=('-thread_queue_size 512') 
args+=('-rtsp_transport tcp')
args+=('-i rtsp://192.168.1.50:8554/mjpeg/1')
args+=('-f lavfi') # this makes it work on youtube. youtube requires an audio channel 
args+=('-i anullsrc') # this makes it work on youtube as well. fake audio channel
args+=('-pix_fmt yuv420p')
args+=('-profile:v baseline')
args+=('-s 426x240')
args+=('-bufsize 2048k')
args+=('-vb 400k')
args+=('-maxrate 800k')
args+=('-deinterlace')
args+=('-vcodec libx264')
args+=('-preset medium')
args+=('-g 30')
args+=('-r 30')
args+=('-acodec libmp3lame')
args+=('-ar 44100')
args+=('-b:a 128k')
args+=('-use_editlist 0') 
args+=('-flvflags no_duration_filesize') # nope failed to update header ...
args+=('-strict experimental')
args+=('-f flv' $YOUTUBE_URL/$STREAM_KEY)

echo "Starting ffmpeg ${args[@]}"
ffmpeg ${args[@]}
