//
//  Node.cpp
//  OpenCV
//
//  Created by Dustin on 7/28/13.
//  Copyright (c) 2013 Dustin. All rights reserved.
//

#include "Node.h"
using namespace std;
Node::Node(int xp, int yp, int d, int p, int dir){
    xPos=xp;
    yPos=yp;
    level=d;
    priority=p;
    this->dir = dir;
}

int Node::getxPos() const {return xPos;}
int Node::getyPos() const {return yPos;}
int Node::getLevel() const {return level;}
int Node::getPriority() const {return priority;}

void Node::updatePriority(const int & xDest, const int & yDest)
{
    priority=level+estimate(xDest, yDest)*10; //A*
}

// give better priority to going strait instead of diagonally
void Node::nextLevel(const int & i) // i: direction
{
    level += (dir == 8 ? ( i % 2 == 0 ? 10 : 14) : 10);
}

// Estimation function for the remaining distance to the goal.
const int & Node::estimate(const int & xDest, const int & yDest) const
{
    static int xd, yd, d;
    xd=xDest-xPos;
    yd=yDest-yPos;
    
    // Euclidian Distance
    d = (int)(sqrt(xd*xd+yd*yd));
    
    // Manhattan distance
    //d=abs(xd)+abs(yd);
    
    // Chebyshev distance
    //d=max(abs(xd), abs(yd));
    
    return(d);
}




