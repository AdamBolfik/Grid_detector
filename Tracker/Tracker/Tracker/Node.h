//
//  Node.h
//  OpenCV
//
//  Created by Dustin on 7/28/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#ifndef __OpenCV__Node__
#define __OpenCV__Node__

#include <iostream>
#include "math.h"

class Node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority
    int dir;
public:
    Node(int xp, int yp, int d, int p, int dir = 8);
    
    int getxPos() const;
    int getyPos() const;
    int getLevel() const;
    int getPriority() const;
    
    void updatePriority(const int & xDest, const int & yDest);
    
    // give better priority to going strait instead of diagonally
    void nextLevel(const int & i); // i: direction
    
    
    // Estimation function for the remaining distance to the goal.
    const int & estimate(const int & xDest, const int & yDest) const;
};


#endif /* defined(__OpenCV__Node__) */
