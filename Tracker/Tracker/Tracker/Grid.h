//
//  Grid.h
//  OpenCV
//
//  Created by Dustin on 7/21/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#ifndef __OpenCV__Grid__
#define __OpenCV__Grid__

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include "A_Star.h"
using namespace cv;
using namespace std;

class Grid{
private:
    Mat starter_image,
    skeleton,
    straightened_image,
    perspective_transform_matrix;
    string source_window;
    
    vector<Point> grid_intersections;
    vector<Point2f> warped_corners,
    straightened_corners;
    map<int, vector<int> > grid_intersections_map, obst_map;
    
    
    /**
     *  removes redundancy from a vector of points (removes clusters)
     *  parameter:  vector<Point2f> &points
     *              int tolerance
     */
    void remove_redundant_points(vector<Point2f> &points, int tolerance);
    
    
    /**
     *  recursively merges entries of map whose keys are within a tolerance of one another
     *      parameters: map< int, vector<Point2f> > &in_map
     *                  int tolerance: this represents a percentage; ex: 10 means ± 10%
     */
    void merge_close_elements_of_map(map< int, vector<int> > &in_map, float tolerance = 10);
    /**
     *  returns the essential points from a vector of points by removing redundancy
     *  (removes clusters)
     *
     */
    vector<Point2f> get_essential_points(vector<Point2f> points, int tolerance);
    
    
public:
    
    //  constructors
    Grid(Mat &src);
    Grid();
    ~Grid();
    /**
     * locates a "blob" (the difference between the source and new image)
     */
    vector<Point2f> get_blob_location(Mat &new_img);
    Mat get_contoured_image(Mat img);
    //  returns basic grid from grid image
    Mat get_skeleton(Mat contoured_img);
    /**
     * sorts the vector according to x then y
     */
    void sort_points(vector<Point2f> &points);
    
    /**
     * this returns a map that is
     */
    map<int, vector<int> > get_sorted_point_map(vector<Point2f> &points, float tolerance = 10);
    /**
     *  Returns a vector points for the shortest path to dst
     *
     *             ^
     *             |  —–>
     *             *     *    *    *   *>F
     *             *|—-—-|—-—-|—-—-|—-—-|
     *              |    |    |    |    |
     *             *|—-—-|—-—-|—-—-|—-—-|
     *              |    |    |    |    |
     *             *|—-—-|—-—-|—-—-|—-—-|
     *              |    |    |    |    |
     *             *|—-—-|—-—-|—-—-|—-—-|
     *              |    |    |    |    |
     *             *|—-—-|—-—-|—-—-|—-—-|
     *             S
     *
     *  parameters: Point2f start_pt
     *              Point2f end_point
     *              vector<Point2f> points
     */
    vector<Point2f> get_shortest_path_points(Point2i start_pt, Point2i end_point, map<int, vector<int> > grid);
    /**
     *  returns vector of floating-point "Points"
     *  Parameter:  Mat skeleton: a skeleton-like(bare-bones) representation of image
     *
     */
    vector<Point2f> get_intersections(Mat skeleton);
    //  gets intersection point of two lines
    Point2f get_intersection(Point2f o1, Point2f o2, Point2f p1, Point2f p2);
    
    
    
    
    void set_image_straighting(vector<Point2f> &input_corners);
    void straighten_image(Mat &img);
    
    Mat get_straightened_image();
    
    void sort_corners(std::vector<cv::Point2f>& corners, cv::Point2f center);
    /**
     *  creates an image with points/ circles, and lines overlayed onto a given image
     */
    void show_image(vector<Point2f> points, Mat img, vector<Point2f> path, int thickness = -1, int radius = 20, Scalar color = Scalar(255,255,0));
    
    void set_obstacle(Point p);
    /**
     *  returns the essential points from a vector of points by removing redundancy
     *  (removes clusters)
     *
     */
    vector<Point2f> get_essential_points();
    /**
     *  Returns a vector points for the shortest path to dst
     *
     *             ^
     *             |  —–>
     *             *     *    *    *   *>F
     *             *|—-—-|—-—-|—-—-|—-—-|
     *              |    |    |    |    |
     *             *|—-—-|—-—-|—-—-|—-—-|
     *              |    |    |    |    |
     *             *|—-—-|—-—-|—-—-|—-—-|
     *              |    |    |    |    |
     *             *|—-—-|—-—-|—-—-|—-—-|
     *              |    |    |    |    |
     *             *|—-—-|—-—-|—-—-|—-—-|
     *             S
     */
    vector<Point2f> get_shortest_path_points(Point2i start_pt, Point2i end_point);
    /**
     *  returns vector of floating-point "Points"
     *
     */
    vector<Point2f> get_intersections();
    //  gets intersection point of two lines
    Mat get_contours();
    //  returns basic grid from grid image
    Mat get_skeleton();
    /**
     *  returns a map of containg the corners of: source image
     *                                            straightened image
     *      vector<points> |  key
     *      ———————————————|———————
     *      source         | "src"
     *      straightened   | "dst"
     *  Procedure:  -Use HoughLines to get distinctive lines in image
     *              -merge the lines that are close to on another/ similar
     *              -use process of elimination discover the edges of main object
     *              -get intercepts of edges
     *              -get endpoints of edges
     *              -get intersections of edges
     *              -approximate new dimensions of straightened image
     *              -return map of both source and straightened endpoints
     */
    map<string, vector<Point2f> > get_corner_points();
    map<string, vector<Point2f> > get_corner_points(vector<Point2f> corners);
};


#endif /* defined(__OpenCV__Grid__) */
