#include "class_detector.h"

#include "class_yolo_detector.hpp"
#include "logger.h"

class Detector::Impl {
 public:
  Impl() = default;
  ~Impl() = default;

  YoloDectector _detector;
};

Detector::Detector() { _impl = new Impl(); }
Detector::~Detector() {
  if (_impl != nullptr)
    delete _impl;
}

void Detector::Init(const Config& config) {
  omv::Logger::Instance().Init(config.log_level);

  _impl->_detector.init(config);
}

std::vector<Result> Detector::Detect(const cv::Mat& mat_image) {
  std::vector<Result> vec_result;
  _impl->_detector.detect(mat_image, vec_result);
  return vec_result;
}
