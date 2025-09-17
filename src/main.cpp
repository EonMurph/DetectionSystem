#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "area.hpp"
#include "face.hpp"

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap;
    Mat3b frame;
    int frames_since_color = 0;
    bool scanning;

    cap.open(0, CAP_ANY);
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera." << endl;
        return -1;
    }
    cap.read(frame);
    Area search_area(0, 800, frame.cols, 100);

    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            cerr << "ERROR! Empty frame read." << endl;
            return -1;
        }

        if (scanning) {
            if (find_face()) {
                scanning = false;
            } else {
                frames_since_color++;
                if (frames_since_color == 60) {
                    scanning = false;
                    // run empty room code
                }
            }
        } else {
            if (search_area.scanForColor(frame)) {
                frames_since_color = 0;
                scanning = true;
            }
        }
        rectangle(frame, search_area.rect, Scalar(0, 0, 255), 3);
        imshow("Camera", frame);
        if (waitKey(1) >= 0) {
            break;
        }
    }

    cap.release();
    return 0;
}