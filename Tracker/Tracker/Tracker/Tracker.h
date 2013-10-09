//
//  Tracker.h
//  Grid
//
//  Created by Dustin on 9/6/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#ifndef __Grid__Tracker__
#define __Grid__Tracker__

#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.h>


using namespace std;
using namespace cv;


class Tracker{

private:
    //initial min and max HSV filter values.
    //these will be changed using trackbars
    int H_MIN;
    int H_MAX;
    int S_MIN;
    int S_MAX;
    int V_MIN;
    int V_MAX;
    //default capture width and height
    int FRAME_WIDTH;
    int FRAME_HEIGHT;
    //max number of objects to be detected in frame
    int MAX_NUM_OBJECTS;
    //minimum and maximum object area
    int MIN_OBJECT_AREA;
    int MAX_OBJECT_AREA;
    //names that will appear at the top of each window
    string windowName;
    string windowName1;
    string windowName2;
    string windowName3;
    string trackbarWindowName;
    Mat HSV, threshold;
    
    
public:
    static const int RED = 0;
    static const int ORANGE = 1;
    static const int YELLOW = 2;
    static const int GREEN = 3;
    static const int BLUE = 4;
    static const int VIOLET = 5;
    
    Tracker();
    ~Tracker();
    
    vector<Point2f> get_positions(Mat &img, const int color);
    void morphOps(Mat &thresh);
    void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed);
    void drawObject(int x, int y,Mat &frame);
    static void on_trackbar( int, void* );
    string intToString(int number);
    void createTrackbars();
    
};


#endif /* defined(__Grid__Tracker__) */
