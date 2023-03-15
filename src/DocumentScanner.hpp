#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

#pragma once

using namespace cv;

class DocumentScanner {
protected:
    Mat src;
    Mat imgGray;
    Mat imgCanny;
    Mat imgBlur;    
    Mat imgErode; /* image edge detection + dilatation + erosion */
    Mat imgRectangle; /* image with detected rectangle */
    Mat result; 
    float width_dst;
    float height_dst;
public:
    std::vector<Point> points;

    DocumentScanner(const char * path,float _width_dst = 200.0,float _height_dst = 300.0){
        src = imread((std::string)path);
        width_dst = _width_dst;
        height_dst = _height_dst;
        this->preProcessing();
    };

    DocumentScanner(Mat & img_src,float _width_dst = 200.0,float _height_dst = 300.0){
        src = img_src;
        width_dst = _width_dst;
        height_dst = _height_dst;
        this->preProcessing();
    };

    void preProcessing();
    void getContours();
    void drawPoints(Scalar&& color);
    void reorder();
    void warp();

    void show_gray() { imshow("gray",imgGray);};
    void show_canny() { imshow("canny",imgCanny);};
    void show_blur() { imshow("blur",imgBlur);};
    void show_edges() { imshow("edges",imgErode);};
    void show_rectangle() { imshow("rectangle",imgRectangle);};
    void show_result() { imshow("result",result);};
};