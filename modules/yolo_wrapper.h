#ifndef YOLO_WRAPPER_H
#define YOLO_WRAPPER_H

#include "class_detector.h"

extern "C" {
Detector* CreateDetector();
void DeleteDetector(Detector*);
void InitDetector(Detector*, Config*);
void Predict(Detector*, Result*, size_t);
}

#endif // YOLO_WRAPPER_H
