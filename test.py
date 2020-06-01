from pydetector import Config, Detector

# net_type: YoloV2 = 0, YoloV3 = 1, YoloV2_Tiny = 2, YoloV2_Tiny = 3
# precision: INT8 = 0, FP16 = 1, FP32 = 2

config = Config()

config.file_model_cfg = "/home/rs/Omega/darknet/cfg/yolov3.cfg"
config.file_model_weights = "/home/rs/Omega/darknet/yolov3.weights"
config.detect_thresh = 0.9
config.gpu_id = 0
config.net_type = Config.YOLOV3
config.precision = Config.FP32
config.log_level = Config.DEBUG

yolo = Detector()
yolo.init(config)

# help("pydetector")
