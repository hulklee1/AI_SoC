import torch

model = torch.hub.load('ultralytics/yolov5', 'yolov5n')
print(model)
r=model('/home/pi/Pictures/K1.jpg')
r.print()
r.show()
