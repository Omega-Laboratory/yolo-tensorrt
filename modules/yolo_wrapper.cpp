#include "yolo_wrapper.h"

Detector* CreateDetector() { return new Detector(); }

void DeleteDetector(Detector* detector) {
  if (detector)
    delete detector;
}

void InitDetector(Detector* detector, Config* config) {
  if (detector && config)
    detector->init(*config);
}

void Predict(Detector*, Result*, size_t) {}
