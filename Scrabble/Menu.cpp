#include "Menu.h"
#include "LinkedList.h"
#include <ctype.h>
#include <stdio.h>

Menu::Menu()
{
}

Menu::~Menu()
{
}

std::string Menu::enterTile(LinkedList *userhand)
{
    bool quit = false;
    bool restart = false;
    bool coordinatesCorrect = true;
    std::string place;
    char tileLetter = 'x';
    std::string at;
    std::string coordinate;
    std::string move;
    std::string spacelessMove; // Variable to hold the users move with no spaces
    std::string word;
    std::string separator = "-";

    do
    {
        restart = false;       // Reset 'restart' variable
        userMove.clear();      // Clear previous move (if any)
        word.clear();          // Clear previous word variable (if any)
        spacelessMove.clear(); // Clear previous spacelessMove variable (if any)
        std::cout << "> ";
        getline(std::cin, userMove); // Get a line from the user
        std::istringstream stream(userMove);
        while (stream >> word)
        { // Remove the spaces and just keep the characters
            int i = 0;
            char c;
            while (word[i])
            {
                c = word[i];
                spacelessMove += tolower(c);
                i++;
            }
        }

        if (spacelessMove.substr(0, 4) == "save" && spacelessMove.size() > 4)
        { // Add a catch if the user tries to save
            if (spacelessMove.substr(4) == "back")
            {
                std::cout << "Cannot call the save file 'back'" << std::endl;
                restart = true;
            }
            else
            {
                return spacelessMove;
            }
        }
        while ((spacelessMove.length() < 10 || spacelessMove.length() > 11) && restart == false)
        { // Make sure the sentence is in the correct format and prevent indefinite loop
            if (spacelessMove == "placedone")
            { // If user enters 'place Done' the function ends
                return "done";
            }
            else if (spacelessMove == "pass")
            { // If the user enters 'pass' the function ends
                return "pass";
            }
            else if (spacelessMove == "help")
            { // If the user enters 'help' the function outputs the help statements
                return "help";
            }
            else if (spacelessMove.substr(0, 7) == "replace" && spacelessMove.size() > 7)
            { // If the user enters 'replace' and is has a letter after the word
                return spacelessMove;
            }
            else if (std::cin.eof())
            { // Add a check for 'EoF'
                std::cout << "Goodbye" << std::endl;
                exit(1);
            }
            else
            {
                std::cout << "Statement formatting is incorrect" << std::endl; // Else if the user enters a sentence is formatting wrong, restarts the input process
                restart = true;
            }
        }

        if (restart != true)
        { // If restart varriable is true, skip this section
            for (size_t i = 0; i < spacelessMove.length(); i++)
            { // Iterate through the users input at set individual characters to preset variables
                if (i < 5)
                {
                    place += spacelessMove[i];
                }
                else if (i < 6)
                {
                    tileLetter = spacelessMove[i];
                }
                else if (i < 8)
                {
                    at += spacelessMove[i];
                }
                else
                {
                    coordinate += spacelessMove[i];
                }
            }

            if (!coordinate.empty())
            {
                coordinate[0] = std::toupper(coordinate[0]); // Capitalize the first letter
            }

            tileLetter = toupper(tileLetter);
            move = tileLetter + separator + coordinate; // Create variable that shows the tile and the co-ordinate for the placement
            std::cout << "This is the move " << move;

            if (coordinate.length() == 3)
            { // Check if the cordinate value is a double digit and check that it is in the right format
                if (isupper(coordinate.at(0)) != true && isalpha(coordinate.at(0)) != true && isdigit(coordinate.at(1)) != true && isdigit(coordinate.at(2)) != true)
                {
                    coordinatesCorrect = false;
                }
            }
            else
            {
                if (isupper(coordinate.at(0)) != true && isalpha(coordinate.at(0)) != true && isdigit(coordinate.at(1)) != true)
                {
                    coordinatesCorrect = false;
                }
            }
            std::cout << "Place: " << place;
            std::cout << "at: " << at;
            std::cout << "tileLetter: " << tileLetter;
            std::cout << "Coordinates: " << coordinatesCorrect;
            if (place != "place" || at != "at" || isupper(tileLetter) == false || coordinatesCorrect == false)
            { // Checks if the move entered by the user is in the correct format
                std::cout << "Invalid placing format" << std::endl;
                restart = true;
            }
            else
            { // If the move entered by the user is in the correct format, it checks if the Tile selected is in the users hand
                Node *temp = userhand->getNode();
                while (temp != NULL)
                {
                    if (temp->tile->letter == tileLetter)
                    {
                        quit = true;
                        return move; // If tile is found in hand, stop iteration and return that move
                    }
                    temp = temp->next;
                }
                std::cout << "You don't have that tile in your hand" << std::endl; // If the tile selected isn't in the players hand, output the error message to the terminal

                restart = false;
            }
            place.clear();
            at.clear();
            coordinate.clear();
            move.clear();
        }
        else
        {
            restart = false;
        }
    } while (quit != true);
    return move;
}
