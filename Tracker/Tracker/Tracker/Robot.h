//
//  Robot.h
//  Grid
//
//  Created by Dustin on 9/1/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#ifndef __Grid__Robot__
#define __Grid__Robot__

#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.h>

using namespace std;
using namespace cv;

class Robot{
private:
    vector<Point2f> path;
    Scalar color;
    RNG rng;
    string name;
    
public:
    Robot();
    Robot(string name);
    Robot(Point2f point, string name);
    Robot(Point2f point);
    ~Robot();
    void update_current_position(Point2f point);
    vector<Point2f> get_path();
    string get_name();
    Point2f get_nearest_bot(vector<Point2f> bot_locations);
    void show_bot_location(Mat &image);
    void show_bot_path(Mat &image);
    Scalar get_bot_color();
    
    
    
};
#endif /* defined(__Grid__Robot__) */
