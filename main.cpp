#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

void scan_search_area(int, int, int, int, Mat);

int main() {
    VideoCapture cap;
    Mat frame;
    int search_x = 600;
    int search_y = 400;
    int search_w = 100;
    int search_h = 100;
    Rect search_area(search_x, search_y, search_w, search_h);

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

        rectangle(frame, search_area, Scalar(0, 0, 255), 3);
        scan_search_area(search_x, search_y, search_w, search_h, frame);
        imshow("Camera", frame);
        if (waitKey(1) >= 0) {
            break;
        }
    }

    cap.release();
    return 0;
}

void scan_search_area(int x, int y, int w, int h, Mat frame) {
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            Point center(i, j);
            circle(frame, center, 0, Scalar(0, 255, 0), -1);
        }
    }
}