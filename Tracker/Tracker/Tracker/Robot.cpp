//
//  Robot.cpp
//  Grid
//
//  Created by Dustin on 9/1/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#include "Robot.h"

vector<Point2f> path;
string name;


Robot::Robot(){
    this->name = "bot";
    rng = RNG(12345);
    color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
}
Robot::Robot(string name){
    this->name = name;
    rng = RNG(12345);
    color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
}
Robot::Robot(Point2f point, string name){
    this->name = name;
    path.push_back(point);
    rng = RNG(12345);
    color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
}
Robot::Robot(Point2f point){
    name = "bot";
    path.push_back(point);
    rng = RNG(12345);
    color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
}
Robot::~Robot(){
    
}
void Robot::update_current_position(Point2f point){
    path.push_back(point);
}
vector<Point2f> Robot::get_path(){
    return path;
}
string Robot::get_name(){
    return name;
}
Point2f Robot::get_nearest_bot(vector<Point2f> bot_locations){
    Point2f this_bot = *path.rbegin(),
    closest_bot = *bot_locations.begin(),
    diff_point;
    diff_point = this_bot - closest_bot;
    diff_point.x *= diff_point.x;
    diff_point.y *= diff_point.y;
    double dist = sqrt(diff_point.x + diff_point.y);
    
    for (vector<Point2f>::iterator it = (bot_locations.begin() + 1); it != bot_locations.end(); it++) {
        diff_point = this_bot - *it;
        diff_point = this_bot - closest_bot;
        diff_point.x *= diff_point.x;
        diff_point.y *= diff_point.y;
        double temp_dist = sqrt(diff_point.x + diff_point.y);
        if (temp_dist < dist) {
            dist = temp_dist;
        }
    }
    return this_bot;
}
void Robot::show_bot_location(Mat &image){
    circle(image, *(path.rbegin()), 10, color);
}
void Robot::show_bot_path(Mat &image){
    for (vector<Point2f>::iterator it = path.begin(); it != path.end() - 1; it++) {
        line(image, *it, *(it + 1), color);
    }
}

Scalar Robot::get_bot_color(){
    return color;
}