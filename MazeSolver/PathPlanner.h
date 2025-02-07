
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathPlanner {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);
   // Clean-up
   ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);

   // Method for Milestone 2
   // Return a DEEP COPY of the NodeList of all node's
   //    that the robot can reach with distances
   NodeList* getReachableNodes();


   // Method for Milestone 3
   // Get the path from the starting position to the given goal co-ordinate
   //    The path should be a DEEP COPY
   NodeList* getPath();
   
   //Find the location of S and set that node to the return value
   NodePtr findS(Env env);

   NodeList* extractList();


private:
   NodeList* open = new NodeList();
   NodeList* closed = new NodeList();
   NodeList* copyPtr = new NodeList();
   NodeList* a;
   int row;
   int col;
   int gRow;
   int gCol;
   int nextNode;
   int sDistance;
   Env envCopy;
   int x = 0;
   bool exit = false;
   NodePtr nodePtr;
   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

};

#endif // COSC_ASS_ONE_PATH_PLANNING
