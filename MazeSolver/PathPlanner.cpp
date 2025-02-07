
#include "PathPlanner.h"

#include <iostream>
#include <memory>

PathPlanner::PathPlanner(Env env, int rows, int cols)
{
    do
    {
        for (int i = 0; i < ENV_DIM; i++)
        {
            if (x != 20 && i != 20)
            {
                envCopy[x][i] = env[x][i];
            }
            else
            {
                exit = true;
            }
        }
        x++;
    } while (!exit);
}

PathPlanner::~PathPlanner()
{
    delete closed;
    delete a;
    delete copyPtr;
}

NodeList *PathPlanner::extractList()
{
    return closed;
}

NodePtr PathPlanner::findS(Env env)
{
    bool sFound = false;
    int x = 0;
    NodePtr nodeOfS = nullptr; // Initialize to avoid undefined behavior

    do
    {
        for (int i = 0; i < ENV_DIM; i++)
        {
            if (env[x][i] == 'S')
            {
                sFound = true;
                nodeOfS = new Node(x, i, 0); // Allocate on heap
                std::cout << "The starting location is " << nodeOfS->getRow() << "," << nodeOfS->getCol() << std::endl;
                return nodeOfS; // Return valid pointer
            }
        }
        x++;
    } while (!sFound);

    return nullptr; // Return nullptr if 'S' is not found
}

void PathPlanner::initialPosition(int row, int col)
{
    this->row = row;
    this->col = col;
}

NodeList *PathPlanner::getReachableNodes()
{
    bool exit = false;
    NodePtr nodeFirst = new Node(this->row, this->col, 0); // Initial node location
    Node node = Node(row, col, 0);

    open->addBack(nodeFirst);
    NodePtr p = open->get(0); // Set p to starting node
    do
    {
        for (int i = 0; open->get(i) != NULL; i++)
        {
            if (p == closed->get(i))
            {
                if (open->get(i + 1) != NULL)
                {
                    p = open->get(i + 1);
                }
                else
                {
                    exit = true;
                }
            }
        }
        if (envCopy[p->getRow() - 1][p->getCol()] != SYMBOL_WALL && p->getRow() - 1 >= 0)
        { // Check the space above current location
            if (envCopy[p->getRow() - 1][p->getCol()] == SYMBOL_GOAL)
            {
                gCol = p->getCol();
                gRow = p->getRow() - 1;
            }
            NodePtr nodePtr = new Node(p->getRow() - 1, p->getCol(), p->getDistanceToS() + 1);
            if (!open->containsNode(nodePtr))
            {
                open->addBack(nodePtr);
            }
            NodeList a = *open;
            delete nodePtr;
            open = &a;
        }
        if (envCopy[p->getRow()][p->getCol() + 1] != SYMBOL_WALL && p->getCol() + 1 < 20)
        { // Check the space to the right current location
            if (envCopy[p->getRow()][p->getCol() + 1] == SYMBOL_GOAL)
            {
                gCol = p->getCol() + 1;
                gRow = p->getRow();
            }
            NodePtr nodePtr = new Node(p->getRow(), p->getCol() + 1, p->getDistanceToS() + 1);
            if (!open->containsNode(nodePtr))
            {
                open->addBack(nodePtr);
            }
            NodeList a = *open;
            delete nodePtr;
            open = &a;
        }
        if (envCopy[p->getRow() + 1][p->getCol()] != SYMBOL_WALL && p->getRow() + 1 < 20)
        { // Check the space below current location
            if (envCopy[p->getRow() + 1][p->getCol()] == SYMBOL_GOAL)
            {
                gCol = p->getCol();
                gRow = p->getRow() + 1;
            }
            NodePtr nodePtr = new Node(p->getRow() + 1, p->getCol(), p->getDistanceToS() + 1);
            if (!open->containsNode(nodePtr))
            {
                open->addBack(nodePtr);
            }
            NodeList a = *open;
            delete nodePtr;
            open = &a;
        }
        if (envCopy[p->getRow()][p->getCol() - 1] != SYMBOL_WALL && p->getCol() - 1 >= 0)
        { // Check the space to the left current location
            if (envCopy[p->getRow()][p->getCol() - 1] == SYMBOL_GOAL)
            {
                gCol = p->getCol() - 1;
                gRow = p->getRow();
            }
            NodePtr nodePtr = new Node(p->getRow(), p->getCol() - 1, p->getDistanceToS() + 1);
            if (!open->containsNode(nodePtr))
            {
                open->addBack(nodePtr);
            }
            NodeList a = *open;
            delete nodePtr;
            open = &a;
        }

        if (!closed->containsNode(p))
        {
            closed->addBack(p);
        }
    } while (!exit);
    return closed;
}

NodeList *PathPlanner::getPath()
{
    int gNode = 0;
    nextNode = 0;
    bool next = false;

    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        if ((closed->get(i)->getRow() == gRow) && ((closed->get(i))->getCol() == gCol))
        { // Finds goal Node to begin the search back to the start
            gNode = i;
            break;
        }
    }
    nodePtr = new Node((closed->get(gNode))->getRow(), closed->get(gNode)->getCol(), closed->get(gNode)->getDistanceToS()); // Initial setting of node pointer
    copyPtr->addBack(nodePtr);
    do
    {
        nodePtr = new Node((closed->get(gNode))->getRow() - 1, closed->get(gNode)->getCol(), 0); // Sets the node above the one being checked to the current node pointer
        if (next != true)
        {
            if (closed->containsNode(nodePtr) && !copyPtr->containsNode(nodePtr))
            { // Checking if above node is in the closed list
                for (int i = 0; closed->get(i) != NULL; i++)
                { // While the closed list isn't NULL
                    if ((closed->get(i)->getRow() == nodePtr->getRow()) && (closed->get(i)->getCol() == nodePtr->getCol()))
                    {                 // Find if the node we are checking is in the closed list
                        nextNode = i; // Sets next node to check
                        if (closed->get(nextNode)->getDistanceToS() == closed->get(gNode)->getDistanceToS() - 1)
                        {                                                        // Checks if the next location is one less than the starting node
                            copyPtr->addBack(closed->get(nextNode));             // Adds the node from the closed list to a new list - only nodes that form the path will be added
                            sDistance = closed->get(nextNode)->getDistanceToS(); // Sets the new distance to the beginning
                            delete nodePtr;
                            gNode = nextNode; // Changes the previous node checked to the current node, which will be checked next
                            next = true;      // Updates boolean so that the other ordinal nodes aren't checked
                            break;            // Breaks loop
                        }
                    }
                }
            }
        }
        else
        {
            delete nodePtr;
        }

        nodePtr = new Node((closed->get(gNode))->getRow(), closed->get(gNode)->getCol() + 1, 0); // Sets the node to the right of the one being checked to the current node pointer
        if (next != true)
        {
            if (closed->containsNode(nodePtr) && !copyPtr->containsNode(nodePtr))
            {
                for (int i = 0; closed->get(i) != NULL; i++)
                {
                    if ((closed->get(i)->getRow() == nodePtr->getRow()) && (closed->get(i)->getCol() == nodePtr->getCol()))
                    {
                        nextNode = i;
                        if (closed->get(nextNode)->getDistanceToS() == closed->get(gNode)->getDistanceToS() - 1)
                        {
                            copyPtr->addBack(closed->get(nextNode));
                            sDistance = closed->get(nextNode)->getDistanceToS();
                            delete nodePtr;
                            gNode = nextNode;
                            next = true;
                            break;
                        }
                    }
                }
            }
        }

        nodePtr = new Node((closed->get(gNode))->getRow() + 1, closed->get(gNode)->getCol(), 0); // Sets the node below the one being checked to the current node pointer
        if (next != true)
        {
            if (closed->containsNode(nodePtr) && !copyPtr->containsNode(nodePtr))
            {
                for (int i = 0; closed->get(i) != NULL; i++)
                {
                    if ((closed->get(i)->getRow() == nodePtr->getRow()) && (closed->get(i)->getCol() == nodePtr->getCol()))
                    {
                        nextNode = i;
                        if (closed->get(nextNode)->getDistanceToS() == closed->get(gNode)->getDistanceToS() - 1)
                        {
                            copyPtr->addBack(closed->get(nextNode));
                            sDistance = closed->get(nextNode)->getDistanceToS();
                            delete nodePtr;
                            gNode = nextNode;
                            next = true;
                            break;
                        }
                    }
                }
            }
        }
        nodePtr = new Node((closed->get(gNode))->getRow(), closed->get(gNode)->getCol() - 1, 0); // Sets the node to the left of the one being checked to the current node pointer
        if (next != true)
        {
            if (closed->containsNode(nodePtr) && !copyPtr->containsNode(nodePtr))
            {
                for (int i = 0; closed->get(i) != NULL; i++)
                {
                    if ((closed->get(i)->getRow() == nodePtr->getRow()) && (closed->get(i)->getCol() == nodePtr->getCol()))
                    {
                        nextNode = i;
                        if (closed->get(nextNode)->getDistanceToS() == closed->get(gNode)->getDistanceToS() - 1)
                        {
                            copyPtr->addBack(closed->get(nextNode));
                            sDistance = closed->get(nextNode)->getDistanceToS();
                            delete nodePtr;
                            gNode = nextNode;
                            next = true;
                            break;
                        }
                    }
                }
            }
        }
        next = false;
    } while (sDistance != 0); // Once the distance has reached 0 the path is complete and it should exit the loop
    return copyPtr;
}
