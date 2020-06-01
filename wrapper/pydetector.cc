#include "pybind11/pybind11.h"

#include "class_detector.h"

PYBIND11_MODULE(pydetector, m) {
  m.doc() = "pybind11 yolo detector trt plugin";

  /* clang-format off */
  pybind11::class_<Config>(m, "Config")
      .def(pybind11::init<>())
      .def_readwrite("file_model_cfg",&Config::file_model_cfg)
      .def_readwrite("file_model_weights",&Config::file_model_weights)
      .def_readwrite("calibration_image_list_file_txt",
                     &Config::calibration_image_list_file_txt)
      .def_readwrite("detect_thresh",&Config::detect_thresh)
      .def_readwrite("gpu_id",&Config::gpu_id);
  pybind11::class_<Detector>(m, "Detector")
      .def(pybind11::init<>())
      .def("init", &Detector::Init);

  /* clang-format on */
}
