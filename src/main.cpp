#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cmath>
#include <string>

#include "Vertex.hpp"
#include "TOPBacktrack.hpp"

// Gets euclidean distance between two points
double euclideanDistance(double x_1, double x_2, double y_1 , double y_2)
{
    return sqrt(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2));
}

// Adds euclidean distance related to edge into adyasence matrix
void addEdge(std::vector<std::vector<double> > &matrix, std::vector<Vertex*> &list, unsigned int index)
{
    std::vector<Vertex*>::iterator it;
    unsigned int i;
    for(it = list.begin(); it != list.begin() + index; it++)
    {
        i = it - list.begin();
        matrix[index][i] = euclideanDistance((*list[index]).getX(), (*list[i]).getX(), (*list[index]).getY(), (*list[i]).getY());
        matrix[i][index] = euclideanDistance((*list[index]).getX(), (*list[i]).getX(), (*list[index]).getY(), (*list[i]).getY());
    }
}

// Checks if console argument exists
bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char **argv)
{
    // Using heap memory for instances in order to leave stack for recursion
    TOPBacktrack *instance;
    // begin params
    unsigned int nodes, routesAmm;
    double maxT, x, y, score;
    // end params
    std::string foo; // auxiliary variable to store input text not used
    std::vector<Vertex*> *vertexList; // Lists of vertexes, each containing x and y position and score, using heap memory
    std::vector<std::vector<double> > *edgeMatrix; // Adyasence matrix with euclidean distances, using heap memory
    bool printLocals = false, printParams = false; // Argument flags

    if(argc > 1)
    {
        // To print local bests found so far, new bests are better strict
        if(cmdOptionExists(argv, argv+argc, "--locals"))
        {
            printLocals = true;
        }
        // To print instance parameters
        if(cmdOptionExists(argv, argv+argc, "--params"))
        {
            printParams = true;
        }
    }

    // This while supports multiple instance in one input... just in case
    while(std::cin >> foo >> nodes)
    {
        // begin reading params
        std::cin >> foo >> routesAmm;
        std::cin >> foo >> maxT;
        // create params structures needed
        vertexList = new std::vector<Vertex*>(nodes);
        edgeMatrix = new std::vector<std::vector<double> >(nodes);
        for(unsigned int i = 0; i < nodes; i++)
        {
            (*edgeMatrix)[i] = std::vector<double>(nodes, 0);
        }
        for(unsigned int i = 0; i < nodes; i++)
        {
            // assings params to structures
            std::cin >> x >> y >> score;
            (*vertexList)[i] = new Vertex(x, y, score);
            addEdge((*edgeMatrix), (*vertexList), i);
        }
        // creates a new instance to be solved
        instance = new TOPBacktrack((*vertexList), (*edgeMatrix), routesAmm, maxT, nodes);
        // if local bests are to be printed, we set an in instance flag
        if(printLocals) (*instance).printLocals();
        // these variables no longer need to point to heap memory, instance already manages them
        vertexList = nullptr;
        edgeMatrix = nullptr;
        // if instance parameters are to be printed, here is where it does it
        if(printParams) std::cout << nodes << std::endl << routesAmm << std::endl << maxT << std::endl;
        // engange the backtrack!!
        (*instance).bTrack(1);
        // prints final bests which is meant to be the global
        (*instance).printLast();
        // frees memory
        delete instance;
    }
    return 0;
}