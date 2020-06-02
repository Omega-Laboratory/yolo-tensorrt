from pydetector import Config, Detector, Result
import cv2
import os
import time
from concurrent.futures import ThreadPoolExecutor
from threading import Thread, Condition, Event
from queue import Queue

YOLO_CONFIG = Config()

YOLO_CONFIG.file_model_cfg = "/home/rs/Omega/darknet/cfg/yolov3-416.cfg"
YOLO_CONFIG.file_model_weights = "/home/rs/Omega/darknet/weights/yolov3.weights"
YOLO_CONFIG.detect_thresh = 0.9
YOLO_CONFIG.gpu_id = 0
YOLO_CONFIG.net_type = Config.YOLOV3
YOLO_CONFIG.precision = Config.FP32
YOLO_CONFIG.log_level = Config.INFO
YOLO_CONFIG.max_workspace_size = 1 << 30


def producer(cv, queue, stopped):
    os.environ["OPENCV_FFMPEG_CAPTURE_OPTIONS"] = "video_codec;h264_cuvid|fflags;nobuffer|flags;low_latency|framedrop|framerate;15|rtsp_transport;tcp"
    cap = cv2.VideoCapture("rtsp://96.89.47.33:554/live/ch00_0", cv2.CAP_FFMPEG)

    while(not stopped.is_set()):
        ret, frame = cap.read()

        if not ret:
            break

        with cv:
            if queue.qsize() >= 4:
                queue.get()

            queue.put(frame)
            cv.notify_all()

    cap.release()


def consumer(cv, queue, stopped):
    yolo = Detector()
    yolo.init(YOLO_CONFIG)

    while(not stopped.is_set()):
        with cv:
            cv.wait()

            if(queue.empty()):
                break

            frame = queue.get()

        if frame is not None:
            start = time.time()
            res = yolo.detect(frame)
            end = time.time()

            for r in res:
                start_point = (r.rect[0], r.rect[1])
                end_point = (r.rect[0]+r.rect[2], r.rect[1]+r.rect[3])
                cv2.rectangle(frame, start_point, end_point, (255, 0, 0), 2)

            ms = int((end - start)*1000)
            fps = int(1000/ms)

            cv2.putText(frame, f"INFERENCE TIME/FPS: {ms} ms/{fps} fps", (2, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2, cv2.FILLED)
            cv2.imshow('frame', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            stopped.set()


if __name__ == "__main__":
    condition = Condition()
    queue = Queue()
    stopped = Event()

    cs = Thread(name="consumer", target=consumer, args=(condition, queue, stopped))
    pd = Thread(name="producer", target=producer, args=(condition, queue, stopped))

    threads = [cs, pd]

    for thr in threads:
        thr.start()
    for thr in threads:
        thr.join()

    cv2.destroyAllWindows()
