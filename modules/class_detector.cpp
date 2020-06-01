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
  omv::Logger::Instance().Init(config.log_level);

  _impl->_detector.init(config);
}

std::vector<Result> Detector::Detect(/*const cv::Mat& mat_image*/) {
  std::vector<Result> vec_result;
  //  _impl->_detector.detect(mat_image, vec_result);

  Result r1, r2;

  r1.id = 1;
  r1.prob = 0.1f;
  r1.rect = cv::Rect(1, 1, 10, 10);

  r2.id = 2;
  r2.prob = 0.2f;
  r2.rect = cv::Rect(2, 2, 20, 20);

  vec_result.push_back(r1);
  vec_result.push_back(r2);

  return vec_result;
}
