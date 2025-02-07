#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
void printPath(Env env, NodeList *solution);

void printReachablePositions(Env env, NodeList *reachablePositions);

int main(int argc, char **argv)
{

    Env env;
    readEnvStdin(env);                                          // Load Environment
    PathPlanner *path = new PathPlanner(env, ENV_DIM, ENV_DIM); // Create new pathplanner object

    NodeList *nodeList = new NodeList(); // Create new nodelist object

    NodePtr startingNode = path->findS(env); // Find the starting point, 'S', of the maze

    path->initialPosition(startingNode->getRow(), startingNode->getCol()); // Pass in the starting point

    path->getReachableNodes(); // Search through all connecting nodes

    nodeList = path->extractList(); // Get the 'closed' nodelist from the path object

    printReachablePositions(env, nodeList);

    NodeList *solution = path->getPath(); // Get the path

    printPath(env, solution); // Print the path

    delete path; // Clean up
}

void readEnvStdin(Env env)
{
    char c;
    int x = 0, y = 0;
    std::cout << "Please enter the 20 x 20 maze:" << std::endl;
    do
    {
        std::cin >> c;
        if (y < 20)
        {
            env[x][y] = c;
            y++;
        }
        if (x < 20 && y == 20)
        {
            x++;
            y = 0;
            env[x][y] = c;
        }
    } while (x != 20 && y != 20);
}

void printPath(Env env, NodeList *solution)
{
    int var = 0;
    int x = 0;
    bool exit = false;
    do
    {
        if (env[solution->get(var + 1)->getRow()][solution->get(var + 1)->getCol()] == 'S')
        { // If the location is the start lcoation, don't update the map
        }
        else
        {
            if (solution->get(var)->getRow() > solution->get(var + 1)->getRow())
            {
                env[solution->get(var + 1)->getRow()][solution->get(var + 1)->getCol()] = 'V'; // Update location symbols to create a path back to the start from the end
            }
            if (solution->get(var)->getRow() < solution->get(var + 1)->getRow())
            {
                env[solution->get(var + 1)->getRow()][solution->get(var + 1)->getCol()] = '^';
            }
            if (solution->get(var)->getCol() > solution->get(var + 1)->getCol())
            {
                env[solution->get(var + 1)->getRow()][solution->get(var + 1)->getCol()] = '>';
            }
            if (solution->get(var)->getCol() < solution->get(var + 1)->getCol())
            {
                env[solution->get(var + 1)->getRow()][solution->get(var + 1)->getCol()] = '<';
            }
        }
        var++;
    } while (solution->get(var + 1) != NULL);
    std::cout << std::endl;
    std::cout << "Found path to goal: " << std::endl; // Print out path by iterating through the updated env file
    std::ofstream outfile("solution.txt");
    do
    {
        for (int i = 0; i < ENV_DIM; i++)
        {
            if (x != 20 && i != 20)
            {
                std::cout << env[x][i];
                outfile << env[x][i];
            }
            else
            {
                exit = true;
            }
        }
        x++;
        std::cout << std::endl;
        outfile << "\n";
    } while (!exit);
    outfile.close();
}

void printReachablePositions(Env env, NodeList *reachablePositions)
{
    std::cout << "List of all reachable nodes:" << std::endl;
    for (int i = 0; reachablePositions->get(i) != NULL; i++)
    { // Iterate through the Nodelist* and print the nodes row and column while the node isn't NULL
        std::cout << "Node: " << reachablePositions->get(i)->getRow() << ", " << reachablePositions->get(i)->getCol() << std::endl;
    }
}
