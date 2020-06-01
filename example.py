from pydetector import Config, Detector, Result
import cv2
import os

config = Config()

config.file_model_cfg = "/home/rs/Omega/darknet/cfg/yolov3-416.cfg"
config.file_model_weights = "/home/rs/Omega/darknet/yolov3.weights"
config.detect_thresh = 0.9
config.gpu_id = 0
config.net_type = Config.YOLOV3
config.precision = Config.FP32
config.log_level = Config.INFO

yolo = Detector()
yolo.init(config)

os.environ["OPENCV_FFMPEG_CAPTURE_OPTIONS"] = "video_codec;h264_cuvid|fflags;nobuffer|flags;low_latency|framedrop|framerate;15|rtsp_transport;tcp"
cap = cv2.VideoCapture("rtsp://96.89.47.33:554/live/ch00_0", cv2.CAP_FFMPEG)

color = (255, 0, 0)
thickness = 2

while(True):
    ret, frame = cap.read()

    if not ret:
        break

    res = yolo.detect(frame)

    for r in res:
        start_point = (r.rect[0], r.rect[1])
        end_point = (r.rect[0]+r.rect[2], r.rect[1]+r.rect[3])
        cv2.rectangle(frame, start_point, end_point, color, thickness)

    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
