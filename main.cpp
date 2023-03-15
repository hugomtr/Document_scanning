#include "src/DocumentScanner.hpp"

int main() {
    
    VideoCapture cap(0);
    Mat img;

    while(true) {
        // DOCUMENT DETECTION FROM WEBCAM VIDEO
        cap.read(img);
        DocumentScanner dsc(img);

        // // DOCUMENT DETECTION FROM IMAGE
        // DocumentScanner dsc("../resources/doc.jpg");

        dsc.preProcessing();
        dsc.getContours();
        dsc.show_edges();
        if (dsc.points.size() >= 4) {
            dsc.reorder();            
            dsc.drawPoints(Scalar(255,255,0));
            dsc.show_rectangle();
            dsc.warp();
            dsc.show_result();
        } else {
            dsc.show_rectangle();
        }

        waitKey(1);
    }

    return 1;
}