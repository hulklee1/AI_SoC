import cv2

print(cv2.__version__)

print(cv2.getBuildInformation())

gst = "v4l2src device=/dev/video0 " \
	  "! video/x-raw,width=640,height=480,framerate=30/1 " \
	  "! videoconvert " \
	  "! appsink"

cap = cv2.VideoCapture(gst, cv2.CAP_GSTREAMER)

if cap.isOpened():
	print("Sucess...Opened.")
else:
	print("Failed.")
	
