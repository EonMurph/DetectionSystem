#include "area.hpp"

using namespace cv;
using namespace std;

Area::Area(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    Rect r(x, y, w, h);
    this->rect = r;
}

bool Area::scanForColor(Mat3b frame) {
    Mat hsv;
    Mat dst;
    uchar cur_pixel;
    int green_count = 0;
    int non_green = 0;
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(35, 50, 40), Scalar(85, 255, 255), dst);
    for (int i = this->x; i < this->x + this->w; i++) {
        for (int j = this->y; j < this->y + this->h; j++) {
            cur_pixel = dst.at<uchar>(j, i);
            if (cur_pixel == 255) {
                Point pt1(i, j);
                circle(frame, pt1, 0, Scalar(255, 255, 255), -1);
                green_count++;
                non_green = 0;
                if (green_count == 30) {
                    cout << "green detected " << i << endl;
                    return true;
                }
            } else {
                non_green++;
                if (non_green == 20) {
                    green_count = 0;
                }
            }
        }
    }
    return false;
}