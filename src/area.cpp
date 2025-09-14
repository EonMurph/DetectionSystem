#include "area.hpp"

using namespace cv;

Area::Area(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    Rect r(x, y, w, h);
    this->rect = r;
}

void Area::scanArea(Mat frame) {
    for (int i = this->x; i < this->x + this->w; i++) {
        for (int j = this->y; j < this->y + this->h; j++) {
            Point center(i, j);
            circle(frame, center, 0, Scalar(0, 255, 0), -1);
        }
    }
}