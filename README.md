# birdbox
kestrel box with webcam streaming and gallery with piwigo

or maybe just a dedicated php gallery. 

http upload and gallery https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/

[long range wifi](https://www.hackster.io/news/long-range-wifi-for-the-esp32-9429ab89f450)

two esp32 cameras

192.168.1.50  has an ftp upload script to lrio every 5 minutes /home/ftpU/birdbox

192.168.1.7 has the standard esp32 streaming webserver installed

http://192.168.1.7:81/stream the stream without clicking on the start stream.

the esp32 video is identified by ffmpeg as follows: 

Stream #0:0: Video: mjpeg (Baseline), 
yuvj422p(pc, bt470bg/unknown/unknown), 
800x600 [SAR 1:1 DAR 4:3], 
9.90 fps, 
9.90 tbr, 
90k tbn, 
90k tbc
