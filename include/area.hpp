#ifndef area_h
#define area_h

#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <iostream>

using namespace cv;

class Area {
   public:
    int x, y, w, h;
    Rect rect;
    Area(int x, int y, int w, int h);
    bool scanForColor(Mat3b frame);
};

#endif