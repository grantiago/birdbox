## kestrel box 🦅
kestrel box with esp32 cam streaming to youtube 

two esp32 cameras

#### cam50 🎥
192.168.1.50  installed sketch E14  rtsp stream suitable for youtube   
[source rtsp tutorial](https://www.hackster.io/BnBe_Club/9-rtsp-video-streamer-using-the-esp32-cam-board-8832b4)   
prints the rtsp url on the serial screen. in my case rtsp://192.168.1.50:8554/mjpeg/1   
remember!! only one client at a time. this error -- Invalid data found when processing input   
means you are connected with VLC or another client.   
https://www.youtube.com/watch?v=O4uBGZ0VhBM 

This is under development. It's live condition may be dead. 🐦  

#### cam7

~~192.168.1.7 has the standard esp32 streaming webserver installed dead. 
  I shorted this on connecting the leads. Whoops.~~


for the example esp32 webserver stream from the arduino ide examples over http 
http://192.168.x.xx:81/stream the stream without clicking on the start stream.

#### ffmpeg
See the .sh file. This actually works with the arduino E14 sketch and the ESP32 cam. I had a diffucult time finding info on the esp32 cam streaming to youtube.   
I found the answer by setting the search to -- ffmpeg to youtube site:stackoverflow.com   
Then I spent a day punching through the ffmpeg options. 

The esp32 video is identified by ffmpeg as follows: 

    Stream #0:0: Video: mjpeg (Baseline),
    yuvj422p(pc, bt470bg/unknown/unknown),
    800x600 [SAR 1:1 DAR 4:3],
    9.90 fps,
    9.90 tbr,
    90k tbn,
    90k tbc  

#### useful sources:
http upload and gallery https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/   
[long range wifi](https://www.hackster.io/news/long-range-wifi-for-the-esp32-9429ab89f450)

https://randomnerdtutorials.com/telegram-esp32-motion-detection-arduino/

