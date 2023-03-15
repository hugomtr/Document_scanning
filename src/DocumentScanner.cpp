#include "DocumentScanner.hpp"

using namespace cv;

void DocumentScanner::preProcessing() {
    cvtColor(src,imgGray, COLOR_BGR2GRAY);
    GaussianBlur(src,imgBlur, Size(5,5),0);
    Canny(imgBlur,imgCanny, 50, 105);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    Mat imgDil;
//    imgErode = imgCanny;
    dilate(imgCanny,imgDil,kernel);
    erode(imgDil,imgErode, kernel);
}

void DocumentScanner::getContours() {
    imgRectangle = src;
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;

    findContours(imgErode,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    std::vector<std::vector<Point>> conPoly(contours.size());

    uint max_area = 0;

    for (uint i = 0; i < contours.size(); i++){
        uint area = contourArea(contours[i]);

        std::string objectType;

        if (area > 1000) {
            float peri = arcLength(contours[i],true);
            approxPolyDP(contours[i], conPoly[i], 0.04*peri,true);

            if (area > max_area && conPoly[i].size()==4) {
                drawContours(imgRectangle, conPoly,i, Scalar(255,0,0),2);
                points = {conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3]};
                max_area = area;
                return;
            } 
        }
    }
}

void DocumentScanner::drawPoints(Scalar&& color){
    for (int i = 0; i < points.size(); i++){
        circle(imgRectangle,points[i],10,color,FILLED);
        putText(imgRectangle, std::to_string(i), points[i],FONT_HERSHEY_PLAIN, 4, Scalar(255,255,0), 4);
    }
}

void DocumentScanner::reorder(){
    std::vector<Point> orderedPoints(4);
    std::vector<int> sumPoints(4);
    std::vector<int> subPoints(4);

    sumPoints[0] = points[0].x + points[0].y;
    sumPoints[1] = points[1].x + points[1].y;
    sumPoints[2] = points[2].x + points[2].y;
    sumPoints[3] = points[3].x + points[3].y;

    subPoints[0] = points[0].x - points[0].y;
    subPoints[1] = points[1].x - points[1].y;
    subPoints[2] = points[2].x - points[2].y;
    subPoints[3] = points[3].x - points[3].y;
    
    
    orderedPoints[0] = points[std::min_element(sumPoints.begin(),sumPoints.end()) - sumPoints.begin()];
    orderedPoints[1] = points[std::max_element(subPoints.begin(),subPoints.end()) - subPoints.begin()];
    orderedPoints[2] = points[std::min_element(subPoints.begin(),subPoints.end()) - subPoints.begin()];
    orderedPoints[3] = points[std::max_element(sumPoints.begin(),sumPoints.end()) - sumPoints.begin()];

    points = orderedPoints;
}

void DocumentScanner::warp(){
    Point2f dst_points[4] = {{0.0,0.0},{width_dst,0.0},{0.0,height_dst},{width_dst,height_dst}};
    Point2f src_points[4] = {points[0],points[1],points[2],points[3]};

    Mat matrix = getPerspectiveTransform(src_points,dst_points);

    warpPerspective(src, result, matrix, Point(width_dst,height_dst));
}