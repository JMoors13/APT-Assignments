
#include "Node.h"


Node::Node(int row, int col, int distanceToS){
   this->row = row;
   this->col = col;
   this->distanceToS = distanceToS;
}
    
Node::~Node(){
}

int Node::getRow(){  //Return row of node
   return row;
}

int Node::getCol(){ //Return column of node
   return col;
}

int Node::getDistanceToS(){ //Return distance to S
   return distanceToS;
}

void Node::setDistanceToS(int distanceToS){
}
