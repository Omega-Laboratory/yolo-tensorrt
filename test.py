from pydetector import Config, Detector, Result

config = Config()

config.file_model_cfg = "/home/rs/Omega/darknet/cfg/yolov3.cfg"
config.file_model_weights = "/home/rs/Omega/darknet/yolov3.weights"
config.detect_thresh = 0.9
config.gpu_id = 0
config.net_type = Config.YOLOV3
config.precision = Config.FP32
config.log_level = Config.INFO

yolo = Detector()
yolo.init(config)


res = yolo.detect()

for r in res:
    print("%s %f %s" % (r.id, r.prob, r.rect))

# help("pydetector")
