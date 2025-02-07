
#include "NodeList.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>


NodeList::NodeList(){
   
}


NodeList::~NodeList(){
}

NodeList::NodeList(NodeList& other){

   for (int i = 0; other.nodes[i] != NULL; i++) {
   this->nodes[i] = new Node(*other.nodes[i]);
   }
}



int NodeList::getLength(){
   bool exit = false;
   int i = 0;
   int counter = 0;
   do {
      if (nodes[i] != NULL){
         counter ++;
         i++;
      }
      else{
         exit = true;
      }
   }
   while(!exit);
   return counter;
  
}


NodePtr NodeList::get(int i){
    return nodes[i];
}

void NodeList::addBack(NodePtr newNode){
   nodePtr = newNode;

      for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++) {
         if (nodes[i] == NULL) {
         nodes[i] = nodePtr;
         break;
         }
      }
   }


bool NodeList::containsNode(NodePtr node){
   bool contains = false;

   for (int i = 0; nodes[i] != NULL; i++){
      if (nodes[i]->getCol() == (node->getCol()) && nodes[i]->getRow() == (node->getRow())){
         contains = true;
      }
   }
   return contains;
}

void NodeList::clear(){
   for(int i = 0; nodes[i] != NULL; i++) {
      nodes[i] = NULL;
   }
}

void NodeList::printNodeList(){
   std::cout << "List of all nodes:" << std::endl;
   for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++) {
      if (nodes[i] != NULL) {
         NodePtr node = nodes[i];
         std::cout << "Node: Row " << node->getRow() << ", Column " << node->getCol() << ", Distance " << node->getDistanceToS() << std::endl;   
      }
   }
}