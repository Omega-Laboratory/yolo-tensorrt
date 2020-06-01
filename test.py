from pydetector import Config, Detector

config = Config()

config.file_model_cfg = "/home/rs/Omega/darknet/cfg/yolov3.cfg"
config.file_model_weights = "/home/rs/Omega/darknet/yolov3.weights"
config.detect_thresh = 0.9
config.gpu_id = 0

yolo = Detector()
yolo.init(config)

# help("pydetector")
