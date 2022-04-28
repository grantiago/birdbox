| flag         | desc     |
|--------------|-----------|
**-formats**|   print the list of supported file formats
**-codecs**|    print the list of supported codecs (E=encode,D=decode)
**-i**|         set the input file. Multiple -i switchs can be used
**-f**|         set video format (for the input if before of -i, for output otherwise)
**-an**|        ignore audio
**-vn**|        ignore video
**-ar**|       set audio rate (in Hz)
**-ac**|        set the number of channels
**-ab**|        set audio bitrate
**-acodec**|    choose audio codec or use “copy” to bypass audio encoding
**-vcodec**|    choose video codec or use “copy” to bypass video encoding
**-r**|         video fps. You can also use fractional values like 30000/1001 instead of 29.97
**-s**|         frame size (w x h, ie: 320x240)
**-aspect**|    set the aspect ratio i.e: 4:3 or 16:9
**-sameq**|     ffmpeg tries to keep the visual quality of the input
**-t**| N       encode only N seconds of video (you can use also the hh:mm:ss.ddd format)
**-croptop,**| -cropleft, -cropright, -cropbottom,   crop input video frame on each side
**-y**|         automatic overwrite of the output file
**-ss**|        select the starting time in the source file
**-vol**|       change the volume of the audio
**-g**|         Gop size (distance between keyframes)
**-b**|         Video bitrate
**-bt**|        Video bitrate tolerance
**-metadata**|  add a key=value metadata