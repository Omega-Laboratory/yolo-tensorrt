#include <time.h>

#include <chrono>
#include <cstdlib>

#include <opencv2/opencv.hpp>

#include "class_detector.h"

int main() {
  Detector detector;
  Config config;

  config.file_model_cfg = "/home/rs/Omega/darknet/cfg/yolov3-416.cfg";
  config.file_model_weights = "/home/rs/Omega/darknet/weights/yolov3.weights";
  config.calibration_image_list_file_txt = "";
  config.precison = Config::FP32;
  config.log_level = INFO;
  config.detect_thresh = 0.9f;
  config.net_type = Config::YOLOV3;

  std::string path = "rtsp://96.89.47.33:554/live/ch00_0";
  std::string value =
      "video_codec;h264_cuvid|fflags;nobuffer|flags;low_latency|framedrop|framerate;25|rtsp_"
      "transport;tcp";

  //  setenv("OPENCV_FFMPEG_CAPTURE_OPTIONS", value.c_str(), true);
  detector.Init(config);

  cv::Mat mat_image;
  std::vector<Result> res;
  cv::VideoCapture vr;

  if (!vr.open(path, cv::CAP_FFMPEG))
    return 1;

  res.reserve(20);
  cv::namedWindow("image");

  char msg[64];
  while (true) {
    bool grabbed = vr.read(mat_image);

    if (!grabbed)
      break;

    auto start = std::chrono::steady_clock::now();
    detector.Detect(mat_image, res);
    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto fps = 1000 / duration.count();

    for (const auto& r : res)
      cv::rectangle(mat_image, r.rect, cv::Scalar(255, 0, 0), 2);

    std::sprintf(msg, "Inference FPS: %lu", fps);
    cv::putText(mat_image, msg,                //
                cv::Point(2, 50),              //
                cv::FONT_HERSHEY_DUPLEX, 0.7,  //
                cv::Scalar(0, 0, 0), 2);

    cv::imshow("image", mat_image);

    char k = cv::waitKey(5);
    if (k == 27)
      break;
  }

  cv::destroyAllWindows();
  return 0;
}
