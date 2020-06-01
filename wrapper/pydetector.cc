#include "pybind11/pybind11.h"

#include "class_detector.h"

PYBIND11_MODULE(pydetector, m) {
  m.doc() = "pybind11 yolo detector trt plugin";

  /* clang-format off */
  pybind11::class_<Config> config(m, "Config");

  config.def(pybind11::init<>())
      .def_readwrite("file_model_cfg",&Config::file_model_cfg)
      .def_readwrite("file_model_weights",&Config::file_model_weights)
      .def_readwrite("calibration_image_list_file_txt",
                     &Config::calibration_image_list_file_txt)
      .def_readwrite("detect_thresh",&Config::detect_thresh)
      .def_readwrite("gpu_id",&Config::gpu_id)
      .def_readwrite("net_type",&Config::net_type)
      .def_readwrite("precision",&Config::precison)
      .def_readwrite("log_level", &Config::log_level);

  pybind11::enum_<OmvSeverity>(config, "LogLevel")
      .value("FATAL", OmvSeverity::FATAL)
      .value("ERROR", OmvSeverity::ERROR)
      .value("WARN", OmvSeverity::WARN)
      .value("INFO", OmvSeverity::INFO)
      .value("DEBUG", OmvSeverity::DEBUG)
      .export_values();

  pybind11::enum_<Config::ModelType>(config, "ModelType")
      .value("YOLOV2", Config::ModelType::YOLOV2)
      .value("YOLOV3", Config::ModelType::YOLOV3)
      .value("YOLOV2_TINY", Config::ModelType::YOLOV2_TINY)
      .value("YOLOV3_TINY", Config::ModelType::YOLOV3_TINY)
      .export_values();

  pybind11::enum_<Config::Precision>(config, "Precision")
      .value("INT8", Config::Precision::INT8)
      .value("FP16", Config::Precision::FP16)
      .value("FP32", Config::Precision::FP32)
      .export_values();

  pybind11::class_<Detector>(m, "Detector")
      .def(pybind11::init<>())
      .def("init", &Detector::Init);

  /* clang-format on */
}
