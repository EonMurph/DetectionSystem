#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap;
    cap.open(0, CAP_ANY);
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera." << endl;
        return -1;
    }

    Mat frame;
    cap.read(frame);
    imshow("Camera", frame);
    waitKey(0);
}