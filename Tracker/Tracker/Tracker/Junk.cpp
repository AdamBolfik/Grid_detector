////#include "opencv2/highgui/highgui.hpp"
////#include "opencv2/imgproc/imgproc.hpp"
////#include <opencv2/objdetect/objdetect.hpp>
////#include <iostream>
////#include <stdio.h>
////#include <stdlib.h>
////#include "Grid.h"
////#include "time.h"
////using namespace cv;
////using namespace std;
////#define num_robots 1
////
////Mat src;         // source image
////Mat rob_source;
////VideoCapture vcap;
////String src_window = "source";
////vector<Point2f> corners;
////
////Grid grid;
////
////static void on_mouse(int event,int x, int y, int, void* );
////
/////** @function main */
////int main( int argc, char** argv ){
////    cout << "hello" << endl;
////    //    src = imread( "/Users/Dustin/Desktop/2013-06-18 11.49.35.jpg", 1 );
////    //    resize(src, src, Size(src.size().width / 3, src.size().height / 3));
////    //    namedWindow(src_window);
////    //    grid = Grid(src);
////    //    rob_source = imread("/Users/Dustin/Documents/Robot Stuff/srcnot.jpg", 1);
////    //
////    //    setMouseCallback(src_window, on_mouse);
////    //    imshow(src_window, src);
////    //
////    //    waitKey(0);
////
////
//////    VideoCapture cap = VideoCapture(-1); // open the default camera
//////
//////    if(!cap.isOpened())  // check if we succeeded
//////        return -1;
//////
//////    Mat edges;
//////    namedWindow("edges",1);
//////    for(;;)
//////    {
//////        Mat frame;
//////        cap >> frame; // get a new frame from camera
//////        cout << frame.cols << " " << frame.rows << endl;
//////        cvtColor(frame, edges, CV_BGR2GRAY);
//////        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
//////        Canny(edges, edges, 0, 30, 3);
//////        imshow("edges", edges);
//////        if(waitKey(30) >= 0) break;
//////    }
//////    // the camera will be deinitialized automatically in VideoCapture destructor
//////    return 0;
//////    Mat back, fore, ref;
//////	int iter = 20;
//////	vector<vector<Point> > contours;
//////	RNG rng(12345);
//////
//////    vcap = VideoCapture("http://admin:robotcam1@130.254.205.27/video.cgi?.mjpg");
//////    vcap = VideoCapture(-1);
//////    vcap.set(CV_CAP_PROP_FPS, 10);
//////    vcap >> src;
//////    grid = Grid(src);
//////    imshow(src_window, src);
//////    setMouseCallback(src_window, on_mouse);
//////    imshow(src_window, src);
//////
//////    waitKey(0);
//////    //    grid.set_image_straighting(corners);
//////
//////    while (1) {
//////        if (!vcap.isOpened()) {
//////            return -1;
//////        }
//////
//////        vcap >> src;
//////
//////        grid.straighten_image(src);
//////        vector<Point2f> blobs = grid.get_blob_location(src);
//////        int robots_found = num_robots;
//////        for (vector<Point2f>::iterator blob_it = blobs.begin(); blob_it != blobs.end(); blob_it++) {
//////            if(robots_found >= 0){
//////                circle(src, *blob_it, 20, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 5);
//////                robots_found--;
//////            }
//////        }
//////
//////        imshow("straightened", src);
//////        if (waitKey(30) > 0) {
//////            break;
//////        }
//////    }
////
//////    for (int i = 0; ; i++) {
//////        vcap = VideoCapture(i);
//////
//////        if (vcap.isOpened()) {
//////            cout << "cam open " << i << endl;
//////        }
//////        else{
//////            cout << "not open " << i << endl;
//////        }
//////    }
////
////    vcap = VideoCapture(500);
////    while (1) {
////        Mat frame;
////        vcap >> frame;
////        imshow("hello", frame);
////
////        if (waitKey(30) >= 0) {
////            break;
////        }
////    }
////    return 0;
////}
////
//////  mouse event
////static void on_mouse(int event,int x, int y, int, void* ){
////    Mat temp_image;
////    src.copyTo(temp_image);
////    Point2f p(x, y);
////    if (corners.size() == 4) {
////        destroyWindow(src_window);
////        grid.set_image_straighting(corners);
////        vector<Point2f> intersections = grid.get_intersections();
////        vector<Point2f> path;
////        grid.show_image(intersections, grid.get_straightened_image(), path, 2);
////    }
////    else{
////        for (vector<Point2f>::iterator it = corners.begin(); it != corners.end(); it++) {
////            circle(temp_image, *it, 20, Scalar(255, 255, 0), 3);
////            stringstream ss;
////            ss << "(" << it->x << " , " << it->y << ")";
////            string location = ss.str();
////            putText(temp_image, location, Point((it ->x) -40, (it->y) + 30), FONT_HERSHEY_PLAIN, 1, Scalar(255, 100, 200));
////            if (it != corners.begin()) {
////                line(temp_image, *it, *(it - 1) , Scalar(255, 100, 200), 3);
////            }
////            if (it == corners.end() - 1) {
////                line(temp_image, *it, *(corners.begin()) , Scalar(255, 100, 200), 3);
////            }
////        }
////        switch (event) {
////            case  EVENT_LBUTTONDOWN:
////                corners.push_back(p);
////                cout << p << endl;
////                break;
////            case EVENT_RBUTTONDOWN:
////                if (corners.size() > 0) {
////                    for (vector<Point2f>::iterator it = corners.begin(); it != corners.end();) {
////                        Point2f diff = p - *it;
////                        int dist = cv::sqrt(::pow(diff.x, 2) + ::pow(diff.y, 2));
////                        if (dist < 40) {
////                            corners.erase(it);
////                        }
////                        else{
////                            it++;
////                        }
////                    }
////                }
////                break;
////            case EVENT_MOUSEMOVE:
////                circle(temp_image, Point(x,y), 20, Scalar(100, 100, 255), 3);
////                circle(temp_image, Point(x,y), 3, Scalar(100, 255, 255), 3);
////                stringstream ss;
////                ss << "(" << x << " , " << y << ")";
////                string location = ss.str();
////                putText(temp_image, location, Point(x - 40, y - 30), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 100));
////                break;
////
////        }
////
////        imshow(src_window, temp_image);     }
////}
////
//
////objectTrackingTutorial.cpp
//
////Written by  Kyle Hounslow 2013
//
////Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software")
////, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
////and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
////The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
////THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
////FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
////LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
////IN THE SOFTWARE.
//
//#include <sstream>
//#include <string>
//#include <iostream>
//#include <opencv2/highgui.hpp>
//#include <opencv2/core.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv/cv.h>
//
////#include <opencv2/imgproc/imgproc_c.h>
////#include <opencv2/imgproc/imgproc_c.h>
//
//using namespace cv;
//using namespace std;
////initial min and max HSV filter values.
////these will be changed using trackbars
////int H_MIN = 0;
////int H_MAX = 256;
////int S_MIN = 0;
////int S_MAX = 256;
////int V_MIN = 0;
////int V_MAX = 256;
//
////  GREEN
////int H_MIN = 45;
////int H_MAX = 80;
//
////  GREEN-BLUE
////int H_MIN = 80;
////int H_MAX = 90;
//
////  BLUE
//int H_MIN = 90;
//int H_MAX = 135;
//
////  PINK
////int H_MIN = 135;
////int H_MAX = 165;
//
////  RED
////int H_MIN = 165;
////int H_MAX = 180;
//
////  ORANGE
////int H_MIN = 0;
////int H_MAX = 20;
//
////  YELLOW
////int H_MIN = 20;
////int H_MAX = 35;
//
////  YELLOW-GREEN
////int H_MIN = 35;
////int H_MAX = 45;
//
////int H_MIN = 90;
////int H_MAX = H_MIN;
//
//int S_MIN = 75;
//int S_MAX = 256;
//int V_MIN = 0;
//int V_MAX = 256;
//
////  BLACK -------------------- NOT WORKING ----------------------
////int H_MIN = 165;
////int H_MAX = 180;
////int S_MIN = 255;
////int S_MAX = 256;
////int V_MIN = 0;
////int V_MAX = 5;
//
////default capture width and height
//const int FRAME_WIDTH = 640;
//const int FRAME_HEIGHT = 480;
////max number of objects to be detected in frame
//const int MAX_NUM_OBJECTS=50;
////minimum and maximum object area
//const int MIN_OBJECT_AREA = 20*20;
//const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
////names that will appear at the top of each window
//vector<Point> points;
//const string windowName = "Original Image";
//const string windowName1 = "HSV Image";
//const string windowName2 = "Thresholded Image";
//const string windowName3 = "After Morphological Operations";
//const string trackbarWindowName = "Trackbars";
//Point2f mouse_point;
////Matrix to store each frame of the webcam feed
//Mat cameraFeed, bgr_mat, hsv_mat, HSV;	//matrix storage for HSV image
//Mat1b mask;
//int b, g, r, h, s, v;
//Scalar color;
//Vec3b pixel;
//
//void on_trackbar( int, void* )
//{//This function gets called whenever a
//	// trackbar position is changed
//    
//    
//    
//}
//string intToString(int number){
//    
//    
//	std::stringstream ss;
//	ss << number;
//	return ss.str();
//}
//void createTrackbars(){
//	//create window for trackbars
//    
//    
//    namedWindow(trackbarWindowName,0);
//	//create memory to store trackbar name on window
//	char TrackbarName[50];
//	sprintf( TrackbarName, "H_MIN", H_MIN);
//    //	sprintf( TrackbarName, "H_MAX", H_MAX);
//    //	sprintf( TrackbarName, "S_MIN", S_MIN);
//    //	sprintf( TrackbarName, "S_MAX", S_MAX);
//    //	sprintf( TrackbarName, "V_MIN", V_MIN);
//    //	sprintf( TrackbarName, "V_MAX", V_MAX);
//	//create trackbars and insert them into window
//	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
//	//the max value the trackbar can move (eg. H_HIGH),
//	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
//	//                                  ---->    ---->     ---->
//    createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar );
//    createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar );
//    //    createTrackbar( "S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar );
//    //    createTrackbar( "S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar );
//    //    createTrackbar( "V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar );
//    //    createTrackbar( "V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar );
//    
//    
//}
//
//void drawObject(int x, int y,Mat &frame){
//    
//	//use some of the openCV drawing functions to draw crosshairs
//	//on your tracked image!
//    
//    //UPDATE:JUNE 18TH, 2013
//    //added 'if' and 'else' statements to prevent
//    //memory errors from writing off the screen (ie. (-25,-25) is not within the window!)
//    
//	circle(frame,Point(x,y),20,Scalar(0,255,0),2);
//    if(y-25>0)
//        line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
//    if(y+25<FRAME_HEIGHT)
//        line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
//    if(x-25>0)
//        line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
//    if(x+25<FRAME_WIDTH)
//        line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
//    else line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);
//    
//	putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
//    
//}
//void morphOps(Mat &thresh){
//    
//	//create structuring element that will be used to "dilate" and "erode" image.
//	//the element chosen here is a 3px by 3px rectangle
//    
//	Mat erodeElement = getStructuringElement( CV_SHAPE_RECT,Size(3,3));
//    //dilate with larger element so make sure object is nicely visible
//	Mat dilateElement = getStructuringElement( CV_SHAPE_RECT,Size(8,8));
//    
//	erode(thresh,thresh,erodeElement);
//	erode(thresh,thresh,erodeElement);
//    
//    
//	dilate(thresh,thresh,dilateElement);
//	dilate(thresh,thresh,dilateElement);
//    
//    
//    
//}
//void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){
//    
//	Mat temp;
//	threshold.copyTo(temp);
//	//these two vectors needed for output of findContours
//	vector< vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//	//find contours of filtered image using openCV findContours function
//	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
//	//use moments method to find our filtered object
//	double refArea = 30;
//	bool objectFound = false;
//	if (hierarchy.size() > 0) {
//		long numObjects = hierarchy.size();
//        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
//        if(numObjects < MAX_NUM_OBJECTS){
//			for (int index = 0; index >= 0; index = hierarchy[index][0]) {
//                
//				Moments moment = moments((cv::Mat)contours[index]);
//				double area = moment.m00;
//                
//				//if the area is less than 20 px by 20px then it is probably just noise
//				//if the area is the same as the 3/2 of the image size, probably just a bad filter
//				//we only want the object with the largest area so we safe a reference area each
//				//iteration and compare it to the area in the next iteration.
//                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area > refArea){
//					x = moment.m10/area;
//					y = moment.m01/area;
//                    
//					objectFound = true;
//                    
//				}else objectFound = false;
//                
//                
//			}
//			//let user know you found an object
//			if(objectFound ==true){
//				putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
//				//draw object location on screen
//				drawObject(x,y,cameraFeed);}
//            
//		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
//	}
//}
//
//void trackFilteredObject(vector<Point> &points, Mat threshold, Mat &cameraFeed){
//    
//	Mat temp;
//	threshold.copyTo(temp);
//	//these two vectors needed for output of findContours
//	vector< vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//	//find contours of filtered image using openCV findContours function
//	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
//	//use moments method to find our filtered object
//	double refArea = 20;
//	bool objectFound = false;
//	if (hierarchy.size() > 0) {
//		long numObjects = hierarchy.size();
//        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
//        if(numObjects < MAX_NUM_OBJECTS){
//			for (int index = 0; index >= 0; index = hierarchy[index][0]) {
//                
//				Moments moment = moments((cv::Mat)contours[index]);
//				double area = moment.m00;
//                
//				//if the area is less than 20 px by 20px then it is probably just noise
//				//if the area is the same as the 3/2 of the image size, probably just a bad filter
//				//we only want the object with the largest area so we safe a reference area each
//				//iteration and compare it to the area in the next iteration.
//                if(area > MIN_OBJECT_AREA && area < MAX_OBJECT_AREA && area > refArea){
//					int x = moment.m10 / area;
//					int y = moment.m01 / area;
//                    points.push_back(Point(x,y));
//                    
//					objectFound = true;
//                    
//				}else objectFound = false;
//                
//                
//			}
//			//let user know you found an object
//			if(objectFound ==true){
//				putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
//				//draw object location on screen
//                for (vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
//                    drawObject(it->x,it->y,cameraFeed);
//                }
//            }
//            
//		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
//	}
//}
//
//static void on_mouse(int event,int x, int y, int, void* ){
//    switch (event) {
//            //   get the "most important" Color of the area selected
//        case  EVENT_LBUTTONDOWN:
//            
//            break;
//        case EVENT_RBUTTONDOWN:
//            break;
//            //   Tracks mouse
//        case EVENT_MOUSEMOVE:
//            mouse_point.x = x;
//            mouse_point.y = y;
//            break;
//            //                default:
//            //                   imshow(windowName, cameraFeed);
//            
//    }
//    imshow(windowName, cameraFeed);
//    
//    
//}
//
//int main(int argc, char* argv[])
//{
//	//some boolean variables for different functionality within this
//	//program
//    bool trackObjects = true;
//    bool useMorphOps = true;
//    
//    
//	//matrix storage for binary threshold image
//	Mat threshold;
//	//x and y values for the location of the object
//	int x = 0,
//    y = 0;
//	//create slider bars for HSV filtering
//	createTrackbars();
//	//video capture object to acquire webcam feed
//	VideoCapture capture;
//	//open capture object at location zero (default location for webcam)
//    //	capture.open("http://admin:robotcam1@130.254.205.27/video.cgi?.mjpg");
//    capture.open(0);
//	//set height and width of capture frame
//	capture.set(CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
//	capture.set(CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
//	//start an infinite loop where webcam feed is copied to cameraFeed matrix
//	//all of our operations will be performed within this loop
//    //store image to matrix
//    capture.read(cameraFeed);
//    //    cvtColor(cameraFeed, color_mat,CV_BGR2HSV);
//    //    imshow("color" , color_mat);
//    //    imshow(windowName,cameraFeed);
//    
//    
//	while(1){
//        
//		//store image to matrix
//		capture.read(cameraFeed);
//		//convert frame from BGR to HSV colorspace
//		cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
//		/**
//         *  filter HSV image between values and store filtered image to
//         *  threshold matrix
//         */
//		inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
//        
//		/**
//         *  perform morphological operations on thresholded image to eliminate noise
//         *  and emphasize the filtered object(s)
//         */
//        setMouseCallback(windowName, on_mouse);
//		if(useMorphOps)
//            morphOps(threshold);
//		/**
//         *  pass in thresholded frame to our object tracking function
//         *  this function will return the x and y coordinates of the
//         *  filtered object
//         */
//		if(trackObjects)
//            //			trackFilteredObject(x,y,threshold,cameraFeed);
//            
//            trackFilteredObject(points,threshold,cameraFeed);
//        points.clear();
//        
//		//show frames
//		imshow(windowName2,threshold);
//        
//        imshow(windowName,cameraFeed);
//		imshow(windowName1,HSV);
//        
//        
//		//delay 30ms so that screen can refresh.
//		//image will not appear without this waitKey() command
//        if (waitKey(30) >= 0) {
//            break;
//        }
//	}
//    
//	return 0;
//}
