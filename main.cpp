#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

class Area {
   public:
    int x, y, w, h;
    Rect rect;
    Area(int x, int y, int w, int h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        Rect r(x, y, w, h);
        this->rect = r;
    }

    void scan_area(Mat frame) {
        for (int i = this->x; i < this->x + this->w; i++) {
            for (int j = this->y; j < this->y + this->h; j++) {
                Point center(i, j);
                circle(frame, center, 0, Scalar(0, 255, 0), -1);
            }
        }
    }
};

int main() {
    VideoCapture cap;
    Mat frame;
    Area search_area(1000, 600, 100, 100);

    cap.open(0, CAP_ANY);
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera." << endl;
        return -1;
    }

    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            cerr << "ERROR! Empty frame read." << endl;
            return -1;
        }

        rectangle(frame, search_area.rect, Scalar(0, 0, 255), 3);
        search_area.scan_area(frame);
        imshow("Camera", frame);
        if (waitKey(1) >= 0) {
            break;
        }
    }

    cap.release();
    return 0;
}