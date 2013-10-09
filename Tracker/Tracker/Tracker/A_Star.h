//
//  A_Star.h
//  OpenCV
//
//  Created by Dustin on 7/28/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#ifndef __OpenCV__A_Star__
#define __OpenCV__A_Star__

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <map>
#include "Node.h"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
class A_Star{
private:
    int n; // horizontal size of the map
    int m; // vertical size size of the map
    vector<vector<int> > base_map;
    vector<vector<int> > closed_nodes_map;
    vector<vector<int> > open_nodes_map;
    vector<vector<int> > dir_map;
    vector<vector<int> > vect_path;
    vector<cv::Point2i> path;
    map<string, vector<int> > point_map;
    int dir; // number of possible directions to go at any position
    vector<int> dx, dy;
    // A-star algorithm.
    // The route returned is a string of direction digits.
    string pathFind( const int & xStart, const int & yStart, const int & xFinish, const int & yFinish );
    bool is_neighbor(vector<int> pt);
    
public:
    A_Star(int width, int height, int start_x, int start_y, int end_x, int end_y, map<int, vector<int> > obst_map, int dir = 4);
    A_Star(int width, int height, cv::Point2i start_pt, cv::Point2i end_pt, map<int, vector<int> > obst_map, int dir = 4);
    vector<vector<int> > get_path_vectors();
    vector<cv::Point2i> get_path_points();
    
    
    
};
#endif /* defined(__OpenCV__A_Star__) */
