
//
//  A_Star.cpp
//  OpenCV
//
//  Created by Dustin on 7/28/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#include "A_Star.h"
#include <iostream>
#include <vector>
using namespace std;

// Determine priority (in the priority queue)
bool operator<(const Node & a, const Node & b)
{
    return a.getPriority() > b.getPriority();
}
vector<vector<int> > A_Star::get_path_vectors(){
    if (vect_path.size() == 0) {
        vect_path = vector<vector<int> >(path.size(), vector<int>(2));
        for(int i = 0; i < path.size(); i++) {
            vect_path[i][0] = path[i].x;
            vect_path[i][1] = path[i].y;
        }
    }
    return vect_path;
}
vector<cv::Point2i> A_Star::get_path_points(){
    return path;
}

A_Star::A_Star(int width, int height, int start_x, int start_y, int end_x, int end_y, map<int, vector<int> > obst_map, int dir)
{
    n = width;
    m = height;
    this->dir = dir;
    if (dir == 8) {
        dx.push_back(1);
        dx.push_back(1);
        dx.push_back(0);
        dx.push_back(-1);
        dx.push_back(-1);
        dx.push_back(-1);
        dx.push_back(0);
        dx.push_back(1);
        
        dy.push_back(0);
        dy.push_back(1);
        dy.push_back(1);
        dy.push_back(1);
        dy.push_back(0);
        dy.push_back(-1);
        dy.push_back(-1);
        dy.push_back(-1);
    }
    else{
        dx.push_back(1);
        dx.push_back(0);
        dx.push_back(-1);
        dx.push_back(0);
        
        dy.push_back(0);
        dy.push_back(1);
        dy.push_back(0);
        dy.push_back(-1);
    }
    base_map = vector<vector<int> >(n, vector<int>(m, 0));
    closed_nodes_map = vector<vector<int> >(n, vector<int>(m));
    open_nodes_map = vector<vector<int> >(n, vector<int>(m));
    dir_map = vector<vector<int> >(n, vector<int>(m));
    for(map<int, vector<int> >::iterator map_it = obst_map.begin(); map_it != obst_map.end(); map_it++) {
        if (map_it->first < n) {
            for (vector<int>::iterator vect_it = (map_it->second).begin() ; vect_it != (map_it->second).end(); vect_it++){
                if (*vect_it < m) {
                    base_map[n][m] = 1;
                }
            }
        }
    }
    // get the route
    string route = pathFind(start_x, start_y, end_x, end_y);
    
    // follow the route on the map and display it
    if(route.length() > 0){
        int j;
        char c;
        int x = start_x;
        int y = start_y;
        base_map[x][y] = 2;
        path.push_back(cv::Point2i(x, y));
        
        for(int i = 0;i < route.length(); i++){
            c = route.at(i);
            j = atoi(&c);
            x = x + dx[j];
            y = y + dy[j];
            path.push_back(cv::Point2i(x, y));
            base_map[x][y] = 3;
        }
        base_map[x][y] = 4;
        path.push_back(cv::Point2i(x, y));
        
        //        // display the map with the route
        //        for(int y = 0; y < m; y++){
        //            for(int x = 0; x < n; x++)
        //                if(base_map[x][y] == 0)
        //                    cout << ".";
        //                else if(base_map[x][y] == 1)
        //                    cout << "O"; //obstacle
        //                else if(base_map[x][y] == 2)
        //                    cout << "S"; //start
        //                else if(base_map[x][y] == 3)
        //                    cout << "R"; //route
        //                else if(base_map[x][y] == 4)
        //                    cout << "F"; //finish
        //            cout << endl;
        //        }
    }
}

// A-star algorithm.
// The route returned is a string of direction digits.
string A_Star::pathFind( const int & xStart, const int & yStart, const int & xFinish, const int & yFinish ){
    priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
    int pqi = 0; // pq index
    Node* n0;
    Node* m0;
    static int j, x, y, xdx, ydy;
    char c;
    
    // reset the node maps
    for(y = 0; y < m; y++){
        for(x = 0; x < n; x++){
            closed_nodes_map[x][y] = 0;
            open_nodes_map[x][y] = 0;
        }
    }
    
    // create the start node and push into list of open nodes
    n0 = new Node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[xStart][yStart]= (n0->getPriority()); // mark it on the open nodes map
    
    // A* search
    while(!pq[pqi].empty()){
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0 = new Node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
                      pq[pqi].top().getLevel(), pq[pqi].top().getPriority());
        
        x = n0->getxPos();
        y = n0->getyPos();
        
        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y]=1;
        
        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x == xFinish && y == yFinish){
            // generate the path from finish to start
            // by following the directions
            string path = "";
            while(!(x == xStart && y == yStart)){
                j = dir_map[x][y];
                c = '0' + (j + dir / 2) % dir;
                path = c + path;
                x += dx[j];
                y += dy[j];
            }
            
            // garbage collection
            delete n0;
            // empty the leftover nodes
            while(!pq[pqi].empty())
                pq[pqi].pop();
            
            return path;
        }
        
        // generate moves (child nodes) in all possible directions
        for(int i = 0; i < dir ; i++){
            xdx = x + dx[i];
            ydy = y + dy[i];
            
            if(!(xdx < 0 || xdx > n - 1 || ydy < 0 || ydy > m - 1 || base_map[xdx][ydy] == 1 || closed_nodes_map[xdx][ydy] == 1)){
                // generate a child node
                m0 = new Node(xdx, ydy, n0->getLevel(), n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);
                
                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy] == 0){
                    open_nodes_map[xdx][ydy] = m0->getPriority();
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    dir_map[xdx][ydy] = (i + dir / 2) % dir;
                }
                else if(open_nodes_map[xdx][ydy] > m0->getPriority()){
                    // update the priority info
                    open_nodes_map[xdx][ydy] = m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy] = (i + dir / 2) % dir;
                    
                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().getxPos() == xdx && pq[pqi].top().getyPos() == ydy)){
                        pq[1 - pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pq[pqi].pop(); // remove the wanted node
                    
                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
                    while(!pq[pqi].empty()){
                        pq[1 - pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pqi = 1 - pqi;
                    pq[pqi].push(*m0); // add the better node instead
                }
                else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    return ""; // no route found
}