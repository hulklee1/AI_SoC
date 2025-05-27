import subprocess

# 사용자 설정

PC_IP = "192.168.137.1"  # "127.0.0.1" #
UDP_PORT = 5000          # 
FILE_PREFIX = "video"    # 

# GStreamer 
gst_cmd = [
    "gst-launch-1.0", "-e",
    "v4l2src", "!",
    "videoconvert", "!",
    "x264enc", "tune=zerolatency", "bitrate=1000", "speed-preset=ultrafast", "!",
    "tee", "name=t",
    "t.", "!", "queue", "!", "h264parse", "!", "rtph264pay", "config-interval=1", "pt=96", "!", 
    "udpsink", f"host={PC_IP}", f"port={UDP_PORT}",
    "t.", "!", "queue", "!", "h264parse", "!", 
    "splitmuxsink", f"location={FILE_PREFIX}-%03d.mp4", "max-size-time=10000000000"
]

# 
try:
    print("GStreamer 저장중...")
    print("Press Ctrl+C to stop.")
    subprocess.run(gst_cmd)
except KeyboardInterrupt:
    print("사용자에 의해 중단됨.")
