#include "pybind11/pybind11.h"

#include "class_detector.h"

PYBIND11_MODULE(pydetector, m) {
  m.doc() = "pybind11 yolo detector trt plugin";

  /* clang-format off */
  pybind11::class_<Detector>(m, "Detector")
      .def(pybind11::init<>());

  /* clang-format on */
}
