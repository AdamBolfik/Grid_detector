//
//  Grid.cpp
//  OpenCV
//
//  Created by Dustin on 7/21/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#include "Grid.h"
#include <vector>
#include <ctime>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/imgproc_c.h>

int da_thresh = 100,
max_length = 0,
count = 0;     // maximum length of image



// random number generator set at a state of 12345
//RNG rng = RNG(12345);

Grid::~Grid(){
    
}
Grid::Grid(){
    
}

Grid::Grid(Mat &src){
    clock_t start_time = clock();
    starter_image = src;
    clock_t end_time = clock(),
    ticks = end_time - start_time;
    
    cout << ticks / (double)CLOCKS_PER_SEC << endl;
    cout << "done" << endl;
    
}
Mat Grid::get_straightened_image(){
    
    return straightened_image;
}

/**
 * sorts the vector according to x then y
 */
void Grid::sort_points(vector<Point2f> &points){
    map<int, vector<int> > sorted_map = get_sorted_point_map(points);
    grid_intersections_map = sorted_map;
    map<int, vector<int> >::iterator map_it = sorted_map.begin();
    points.clear();
    while (map_it != sorted_map.end()) {
        vector<int>::iterator vect_it = map_it->second.begin();
        while (vect_it != map_it->second.end()) {
            points.push_back(Point2f(map_it->first, *vect_it));
            vect_it++;
        }
        map_it++;
    }
}

/**
 * locates a "blob" (the difference between the source and new image)
 */
vector<Point2f> Grid::get_blob_location(Mat &new_img){
    Mat output, temp;
    bilateralFilter(new_img, output, 5, 150, 150);
    Mat kernel_circle = (Mat_<uchar>(3, 3) << 1,1,1,1,0,1,1,1,1);
    vector<Point2f> centers;
    vector<Scalar> colors;
    //        cout << straightened_image.rows << " " << straightened_image.cols << endl;
    //        cout << output.rows << " " << output.cols << endl;
    //		cvtColor(ref, ref, CV_BGR2GRAY);
    //		cvtColor(input, input, CV_BGR2GRAY);
    temp = straightened_image - output;
    //		GaussianBlur(temp, temp, Size(15, 15), KERNEL_GENERAL);
    //		input.copyTo(frame);
    //		GaussianBlur(frame, frame, Size(15, 15), KERNEL_GENERAL);
    cvtColor(temp, temp, CV_BGR2GRAY);
    Canny(temp, temp, 50, 200);
    //		dilate(temp, temp, kernel_circle, Point(-1, -1), 10);
    //		medianBlur(input, input, 9);
    vector<vector<Point> > contours;
    findContours(temp,contours,RETR_EXTERNAL,CHAIN_APPROX_NONE);
    for(int i = 0; i < contours.size(); i++){
        Point p;
        for(int j = 0; j < contours[i].size(); j++){
            p += contours[i][j];
        }
        p.x /= contours[i].size();
        p.y /= contours[i].size();
        //			Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        //			colors.push_back(color);
        centers.push_back(p);
    }
    remove_redundant_points(centers, 40);
    //		for(int i = 0; i < centers.size(); i++){
    //			circle(new_img, centers[i], 40, colors[1], -1);
    //		}
    //		cvtColor(temp, temp, CV_GRAY2BGR);
    //		drawContours(new_img,contours,-1,Scalar(0,0,255),2);
    //		imshow("this", temp);
    
    return centers;
}

/**
 *  recursively merges entries of map whose keys are within a tolerance of one another
 *      parameters: map< int, vector<Point2f> > &in_map
 *                  int tolerance: this represents a percentage; ex: 10 means ± 10%
 */
void Grid::merge_close_elements_of_map(map< int, vector<int> > &in_map, float tolerance){
    map<int, vector<int> > current_map = in_map;
    map<int, vector<int> >::iterator it = in_map.begin(), beater_it;
    float new_tol = 1 + tolerance / 100.0;
    
    pair<int, vector<int> > current_pair = *it;
    it++;
    
    for (; it != in_map.end(); it++) {
        if ((it->first) * new_tol >= (current_pair.first) && (it->first) / new_tol <= (current_pair.first)) {
            int avg_key = (it->first + current_pair.first) / 2;
            vector<int> merged;
            merged.reserve((it->second).size() + (current_pair.second).size());
            merged.insert(merged.end(), (it->second).begin(), (it->second).end());
            merged.insert(merged.end(), (current_pair.second).begin(), (current_pair.second).end());
            beater_it = current_map.find(current_pair.first);
            current_map.erase(beater_it);
            beater_it = current_map.find(it->first);
            current_map.erase(beater_it);
            current_pair = pair<int, vector<int> >(avg_key, merged);
            current_map.insert(current_pair);
            break;
        }
        else current_pair = *it;
    }
    if (in_map.size() != current_map.size()) {
        merge_close_elements_of_map(current_map, tolerance);
    }
    in_map = current_map;
}

/**
 *
 *  returns map:    key: xs from points
 *                  value: vector of correspoing ys from points
 *
 */
map<int, vector<int> > Grid::get_sorted_point_map(vector<Point2f> &points, float tolerance){
    map<int, vector<int> > sorted_map;
    vector<int> ys;
    //  set of xs (keys) that will be deleted from the map
    set<int> keys;
    
    int count = 0;
    /**
     *  this is where macrosorting takes place.
     *  this does not handle 'off' lines. (points that do not exactly align
     */
    vector<Point2f> ::iterator it = points.begin();
    while(it != points.end()){
        if (sorted_map.find(static_cast<int>((*it).x)) == sorted_map.end()) {
            sorted_map.insert(pair<int, vector<int> >(static_cast<int>((*it).x), ys));
        }
        sorted_map[static_cast<int>((*it).x)].push_back(static_cast<int>((*it).y));
        keys.insert(static_cast<int>((*it).x));
        it++;
    }
    
    if(sorted_map.begin()->first == 0){
        vector<int> values = sorted_map.begin()->second;
        sorted_map.erase(0);
        keys.erase(0);
        
        (sorted_map.begin()->second).insert((sorted_map.begin()->second).end(),values.begin(), values.end());
    }
    /**
     *  are there any keys that are of a 10% proximity of one another?
     *  let's recursively find out
     */
    merge_close_elements_of_map(sorted_map, tolerance);
    
    map<int, vector<int> >::iterator    map_it = sorted_map.begin();
    
    if(sorted_map.begin()->first == 0){
        vector<int> values = sorted_map.begin()->second;
        sorted_map.erase(0);
        //        cout << "\t\t" << (sorted_map.begin()->second).size() << endl;
        //        cout << "\t\tnext: " << sorted_map.begin()->first << "\t" << (sorted_map.begin()->second).size() << " -> ";
        (sorted_map.begin()->second).insert((sorted_map.begin()->second).end(),values.begin(), values.end());
        //        cout << "\t" << (sorted_map.begin()->second).size() << endl;
    }
    
    map_it = sorted_map.begin();
    count = 1;
    while (map_it != sorted_map.end()) {
        //        cout << "\n" << count << ".\t" << (map_it->first) << " # ";
        //        count++;
        std::sort((map_it->second).begin(),(map_it->second).end());
        //        for (int i = 0; i < (map_it->second).size(); i++) {
        //            cout <<(map_it->second)[i] << " , ";
        //        }
        //        cout << endl;
        map_it++;
    }
    
    return sorted_map;
}

void Grid::set_obstacle(Point p){
    if (obst_map.find(p.x) != obst_map.end()) {
        obst_map[p.x].push_back(p.y);
    }
    else{
        obst_map.insert(pair<int, vector<int> >(p.x , vector<int>(p.y)));
    }
}

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
vector<Point2f> Grid::get_shortest_path_points(Point2i start_pt, Point2i end_point){
    return get_shortest_path_points(start_pt, end_point, grid_intersections_map);
    
}

/**
 *  Returns a vector points for the shortest path to dst
 *  A* algm
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
 *              map<int. vector<int> > grid
 */
vector<Point2f> Grid::get_shortest_path_points(Point2i start_pt, Point2i end_pt, map<int, vector<int> > grid){
    /**
     *  In order to use the A* (A Star) algorithm, the points need to simplified.
     *  appendix holds the value of all x values; example  |0| : 3
     *                                                     |1| : 17
     *                                                     |2| : 32
     *                                                        ....
     *  the indexes of appendix are the new "simplified" x values from grid;
     */
    vector<int> appendix;
    for (map<int, vector<int> >::iterator it = grid.begin(); it != grid.end(); it++) {
        appendix.push_back(it->first);
    }
    
    //  create simplified
    int simp_sx = (int)distance(appendix.begin(), find(appendix.begin(), appendix.end(), start_pt.x)),
    simp_sy = (int)distance(grid[start_pt.x].begin(), find(grid[start_pt.x].begin(), grid[start_pt.x].end(), start_pt.y)),
    simp_ex = (int)distance(appendix.begin(), find(appendix.begin(), appendix.end(), end_pt.x)),
    simp_ey = (int)distance(grid[end_pt.x].begin(), find(grid[end_pt.x].begin(), grid[end_pt.x].end(), end_pt.y));
    
    Point2i simple_start(simp_sx, simp_sy),
    simple_end(simp_ex, simp_ey);
    
    //  create object that hold the shortest path
    A_Star path = A_Star((int)grid.size(), (int)grid.begin()->second.size(), simp_sx, simp_sy, simp_ex, simp_ey, obst_map);
    
    vector<Point2i> simp_path = path.get_path_points();
    
    vector<Point2f> path_points(simp_path.size());
    
    for (int i = 0; i < simp_path.size(); i++) {
        int old_x = simp_path[i].x,
        old_y = simp_path[i].y,
        new_x = appendix[old_x],
        new_y = grid[new_x][old_y];
        path_points[i] = Point2f(new_x, new_y);
    }
    
    return path_points;
}
/**
 *  returns vector of floating-point "Points"
 *
 */
vector<Point2f> Grid::get_intersections(){
    Mat temp;
    
    straightened_image.copyTo(temp);
    
    temp = get_contoured_image(temp);
    imshow("contour", temp);
    temp = get_skeleton(temp);
    imshow("skeleton", temp);
    vector<Point2f> intersections = get_intersections(temp);
    sort_points(intersections);
    
    return intersections;
}

Mat Grid::get_contours(){
    Mat contours;
    
    return contours;
}
//  returns basic grid from grid image
Mat Grid::get_skeleton(){
    return skeleton;
}
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
map<string, vector<Point2f> > Grid::get_corner_points(){
    map<string, vector<Point2f> > corner_points;
    
    return corner_points;
}


/**
 *  creates an image with points/ circles overlayed onto a given image
 *  Parameters: vector<Point2f> points: vector of points
 *              Mat img:                an image
 *              Scalar color:           color of circles
 */
void Grid::show_image(vector<Point2f> points, Mat img, vector<Point2f> path, int thickness, int radius, Scalar color){
    Mat new_img;
    img.copyTo(new_img);
    for (int i = 0; i < path.size(); i++) {
        if (i + 1 < path.size()) {
            line(new_img, path[i], path[i + 1], color);
        }
    }
    
    for(vector<Point2f>::iterator it = points.begin(); it != points.end(); ++it){
        circle(new_img, (*it), radius, color, thickness);
        stringstream ss;
        ss << "(" << it->x << " , " << it->y << ")";
        string location = ss.str();
        putText(new_img, location, Point((it ->x), (it->y) + 10), FONT_HERSHEY_PLAIN, 0.75, Scalar(0,0,255));
    }
    
    
    imshow("Points", new_img);
    waitKey(30);
}

/**
 *  removes redundancy from a vector of points (removes clusters)
 *  parameter:  vector<Point2f> &points
 *              int tolerance
 */
void Grid::remove_redundant_points(vector<Point2f> &points, int tolerance = 90){
    vector<Point2f> new_intersections, temp_intersections;
    new_intersections = get_essential_points(points, tolerance);
    points.clear();
    points = new_intersections;
}
/**
 *  returns the essential points from a vector of points by removing redundancy
 *  (removes clusters)
 *
 */
vector<Point2f> Grid::get_essential_points(vector<Point2f> points, int tolerance){
    vector<Point2f> points_remaining,
    points_final;
    unsigned long num_of_points = points.size();
    
    if (num_of_points >= 1) {
        vector<Point2f>::iterator it = points.begin();
        
        Point2f head = (*it);
        it++;
        
        for(; it != points.end(); it++){
            int diff_x = abs(abs((*it).x) - abs(head.x)),
            diff_y = abs(abs((*it).y) - abs(head.y));
            
            if(diff_x > tolerance || diff_y > tolerance){
                points_remaining.push_back((*it));
            }
        }
        
        points_final = get_essential_points(points_remaining, tolerance);
        points_final.push_back(head);
        
        return points_final;
    }
    return points;
    
}

/**
 *  returns vector of floating-point "Points"
 *  Parameter:  Mat skeleton: a skeleton-like(bare-bones) representation of image
 *
 */
vector<Point2f> Grid::get_intersections(Mat skeleton){
    Mat kernel = (Mat_<uchar>(3,3) << 1,1,1,1,0,1,1,1,1);
    //    dilate(skeleton, skeleton, kernel, Point(-1,-1), 2);
    //    // thickness of border/ edges
    //    int top = (int)(skeleton.rows * 0.01),
    //    bottom = top,
    //    left = (int)skeleton.cols * 0.01,
    //    right = left;
    //    // put a border around image (makes sure it still has one)
    //    copyMakeBorder(skeleton, skeleton, top, bottom, left, right, BORDER_CONSTANT, Scalar(255,255,255));
    
    Mat cannied_image;
    Canny(skeleton, cannied_image, 50, 200, 3);
    cvtColor(cannied_image, cannied_image, CV_GRAY2BGR);
    
    vector<Point2f> intersections;
    vector<Vec4i> lines;
    // get the lines in the image
    HoughLinesP(skeleton, lines, 1, CV_PI / 180, 180, 30, 10);
    // gets the inserctions points of all the lines.
    Size skel_size = skeleton.size();
    
    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < lines.size();j++){
            Point   p1 = Point(lines[i][0], lines[i][1]),
            p2 = Point(lines[i][2], lines[i][3]),
            p3 = Point(lines[j][0], lines[j][1]),
            p4 = Point(lines[j][2], lines[j][3]);
            if(i != j){
                Point2f intersection = get_intersection(p1, p2, p3, p4);
                if(intersection.x >= 0 && intersection.y >= 0 && intersection.x <= skel_size.width * 1.1 && intersection.y <= skel_size.height * 1.1)
                    intersections.push_back(intersection);
            }
        }
    }
    // remove some of the redudandant points from the above process.
    remove_redundant_points(intersections);
    return intersections;
}
//  gets intersection point of two lines
Point2f Grid::get_intersection(Point2f o1, Point2f o2, Point2f p1, Point2f p2){
    
    Point2f x = p1 - o1;
    Point2f d1 = o2 - o1;
    Point2f d2 = p2 - p1;
    Point2f r(-1,-1);
    
    float cross = d1.x*d2.y - d1.y*d2.x;
    if(abs(cross) >= 1e-8){
        double t1 = (x.x * d2.y - x.y * d2.x) / cross;
        r = o1 + d1 * t1;
    }
    
    return r;
}
void Grid::set_image_straighting(vector<Point2f> &input_corners){
    warped_corners = input_corners;
    straightened_corners.push_back(cv::Point2f(0, 0));
    straightened_corners.push_back(cv::Point2f(600, 0));
    straightened_corners.push_back(cv::Point2f(600, 600));
    straightened_corners.push_back(cv::Point2f(0, 600));
    Point2f center(0,0);
    for (int i = 0; i < input_corners.size(); i++) {
        center += input_corners[i];
    }
    center.x /= warped_corners.size();
    center.y /= warped_corners.size();
    sort_corners(warped_corners, center);
    perspective_transform_matrix = getPerspectiveTransform(warped_corners, straightened_corners);
    straightened_image = Mat::zeros(600, 600, CV_8UC3);
    warpPerspective(starter_image, straightened_image, perspective_transform_matrix, straightened_image.size());
    //    int top = (int)straightened_image.rows * 0.01,
    //    bottom = top,
    //    left = (int)straightened_image.cols * 0.01,
    //    right = left;
    //    copyMakeBorder(straightened_image, straightened_image, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0));
    
}
void Grid::straighten_image(Mat &img){
    Mat quad = Mat::zeros(600, 600, CV_8UC3);
    warpPerspective(img, quad, perspective_transform_matrix, quad.size());
    //    int top = (int)quad.rows * 0.01,
    //        bottom = top,
    //        left = (int)quad.cols * 0.01,
    //        right = left;
    //    copyMakeBorder(quad, quad, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0));
    img = quad;
    
}


Mat Grid::get_contoured_image(Mat img){
    Mat img_gray,
    canny_output;
    img.copyTo(img_gray);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    cvtColor(img_gray, img_gray, CV_BGR2GRAY);
    
    dilate(img_gray, img_gray, KERNEL_GENERAL, Point(-1,-1));
    //    erode(img_gray, img_gray, KERNEL_GENERAL);
    
    
    
    
    //  detect edges
    Canny(img_gray, canny_output, da_thresh, da_thresh * 2, 3);
    imshow("img gray", img_gray);
    
    // find countours
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
    
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    
    for( int i = 0; i< contours.size(); i++ ){
//        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        Scalar color = Scalar(255, 255, 0);
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }
    
    return drawing;
}
//  returns basic grid from grid image
Mat Grid::get_skeleton(Mat contoured_img){
    Mat mask = Mat::zeros(contoured_img.rows + 2, contoured_img.cols + 2, CV_8U);
    floodFill(contoured_img, mask, Point(0,0), 255, 0, Scalar(),Scalar(), 4 + (255 << 8) + FLOODFILL_MASK_ONLY);
    Mat kernel = (Mat_<uchar>(3,3) << 1,1,1,1,0,1,1,1,1);
    dilate(mask, mask, kernel);
    erode(mask, mask, kernel, Point(-1, -1), 2);
    return mask;
    
}
/**
 *  Determine top-left, bottom-left, top-right, and bottom-right corner
 *  Given the four corner points, we have to determine the top-left, bottom-left, top-right, and bottom-right corner so we can apply the perspective
 *  correction.
 *  To determine the top-left, bottom-left, top-right, and bottom right corner, we’ll use the simplest method:
 *      Get the mass center.
 *      Points that have lower y-axis than mass center are the top points, otherwise they are bottom points.
 *      Given two top points, the one with lower x-axis is the top-left. The other is the top-right.
 *      Given two bottom points, the one with lower x-axis is the bottom-left. The other is the bottom-right.
 */
void Grid::sort_corners(std::vector<cv::Point2f>& corners, cv::Point2f center){
    std::vector<cv::Point2f> top, bot;
    
    for (int i = 0; i < corners.size(); i++)
    {
        if (corners[i].y < center.y)
            top.push_back(corners[i]);
        else
            bot.push_back(corners[i]);
    }
    
    cv::Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
    cv::Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
    cv::Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
    cv::Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];
    
    corners.clear();
    corners.push_back(tl);
    corners.push_back(tr);
    corners.push_back(br);
    corners.push_back(bl);
}