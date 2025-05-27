import cv2

pipeline = (
    "v4l2src device=/dev/video0 ! "
    "video/x-raw, width=640, height=480 ,framerate=30/1 ! " 
    "videoconvert ! "
    " appsink"
)

print (pipeline)
cap = cv2.VideoCapture(pipeline, cv2.CAP_GSTREAMER)
if cap.isOpened() != True:
	print(cap)
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break
    cv2.imshow("GStreamer + OpenCV", frame)
    if cv2.waitKey(1) == 27:
        break

cap.release()
cv2.destroyAllWindows()


