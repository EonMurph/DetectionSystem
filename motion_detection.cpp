#include <stdio.h>

#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

int total_color(Mat3b mat, int row, int col) {
    Vec3b values = mat(row, col);
    return values[0] + values[1] + values[2];
}

int main(int argc, char** argv) {
    Mat3b last_frame;
    Mat3b cur_frame;
    Mat1b diff_mat;
    VideoCapture cap;
    cap.open(0, CAP_ANY);
    if (!cap.isOpened()) {
        cerr << "Error! Unable to open camera.\n";
        return -1;
    }

    int jump = 2;
    while (true) {
        cap.read(cur_frame);
        if (cur_frame.empty()) {
            cerr << "ERROR! Blank frome grabbed\n";
            break;
        }
        diff_mat =
            Mat::zeros(cur_frame.rows / jump, cur_frame.cols / jump, CV_32SC1);
        if (!last_frame.empty()) {
            int total_diff = 0;
            int avg_diff = 0;
            for (int col = 0; col < cur_frame.cols; col += jump) {
                for (int row = 0; row < cur_frame.rows; row += jump) {
                    diff_mat(row / jump, col / jump) =
                        pow(abs(total_color(cur_frame, row, col) -
                                total_color(last_frame, row, col)),
                            2);
                }
            }
            for (int col = 0; col < diff_mat.cols; col++) {
                for (int row = 0; row < diff_mat.rows; row++) {
                    total_diff += diff_mat(row, col);
                }
            }
            avg_diff = total_diff / (diff_mat.rows * diff_mat.cols);
            if (avg_diff > 20) {
                cout << "Motion detected! " << avg_diff << endl;
            } else {
                cout << endl;
            }
        }
        imshow("Camera", cur_frame);
        if (waitKey(1) >= 0) {
            break;
        }
        cur_frame.copyTo(last_frame);
    }
    cap.release();

    return 0;
}