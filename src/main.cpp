#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include "area.hpp"

using namespace cv;
using namespace std;


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
        search_area.scanArea(frame);
        imshow("Camera", frame);
        if (waitKey(1) >= 0) {
            break;
        }
    }

    cap.release();
    return 0;
}