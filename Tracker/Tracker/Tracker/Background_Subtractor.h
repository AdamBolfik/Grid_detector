//
//  Background_Subtractor.h
//  Tracker
//
//  Created by Dustin on 10/7/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#ifndef __Tracker__Background_Subtractor__
#define __Tracker__Background_Subtractor__

#include <iostream>
#include <opencv/cv.h>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv_modules.hpp>
using namespace cv;
using namespace std;
class Background_subtractor: public BackgroundSubtractorMOG2{
    // default parameters of gaussian background detection algorithm
//    static const int defaultHistory2 = 500; // Learning rate; alpha = 1/defaultHistory2
//    static const float defaultVarThreshold2 = 4.0*4.0;
//    static const int defaultNMixtures2 = 5; // maximal number of Gaussians in mixture
//    static const float defaultBackgroundRatio2 = 0.9; // threshold sum of weights for background test
//    static const float defaultVarThresholdGen2 = 3.0*3.0;
//    static const float defaultVarInit2 = 15.0; // initial variance for new components
//    static const float defaultVarMax2 = 5 * defaultVarInit2;
//    static const float defaultVarMin2 = 4.0;
};
#endif /* defined(__Tracker__Background_Subtractor__) */
