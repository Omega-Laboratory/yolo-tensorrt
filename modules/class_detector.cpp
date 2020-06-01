#include "class_detector.h"

#include "class_yolo_detector.hpp"
#include "logger.h"

class Detector::Impl {
 public:
  Impl() {}
  ~Impl() {}

  YoloDectector _detector;
};

Detector::Detector() { _impl = new Impl(); }

Detector::~Detector() {
  if (_impl) {
    delete _impl;
    _impl = nullptr;
  }
}

void Detector::Init(const Config& config) {
  omv::Logger::Instance().Init(3);
  LOG(INFO) << config.file_model_cfg;

  _impl->_detector.init(config);
}

void Detector::Detect(const cv::Mat& mat_image, std::vector<Result>& vec_result) {
  _impl->_detector.detect(mat_image, vec_result);
}
