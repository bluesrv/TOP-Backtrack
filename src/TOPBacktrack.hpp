#pragma once

#include <vector>
#include <cmath>

#include "Vertex.hpp"

/*
    Instance class, it stores the variables to be used to access them in any method.

    variables and constants
    x and z are fixed size matrixes, access to a certain edge usability and arrival time is done in constant time
    y is a fixed sized list, to know if an i vertex is being used, access is constant
    edgeMatrix and vertexLists are params passed from main
    restults is an auxiliary matrix for printing purposes only, since it's needed to print the whole route, it stores it here
    routesAmm is the parameter, while m is the current ammount of routes for a point in execution
    maxT is the max time parameter, currScore is the accumulated score of solution in execution and sBest is the value of the current best solution
    addSubt indicates if more subroutes are to be added, pLocals indicates if local bests are to be printed
    bestRoute, stores the current instance of best in heap memory

    methods
    Constructor gets params from main and initiates variables
    Destructor frees memory
    bTrack is the main backtrack algorithm, description in document
    addEdge checks if edge is usable, if it is, it adds it. Returns if adding was successful or not
    checkLast checks if the edges for last nodes of routes and end node is doable as it adds them, if one of them fails it returns false
    undo removes an edge assigned by addEdge
    undoAllLast removes all edges that go to end node
    printLast is a method that prints the last results of instance, which is meant to be the global best
    printLocals sets the flag for printing the local bests found
*/

class TOPBacktrack
{
    private:

    std::vector<std::vector<bool>> *x;
    std::vector<bool> *y;
    std::vector<std::vector<double>> *z, *edgeMatrix;
    std::vector<std::vector<unsigned int>> *results;
    std::vector<Vertex*> *vertexList;
    unsigned int routesAmm, m = 0;
    double maxT, currScore = 0, sBest = 0;
    bool addSubt = true, pLocals = false;
    Route *bestRoute;

    bool addEdge(unsigned int i, unsigned int j);
    bool checkLast();
    void printResult();
    void undo(unsigned int i, unsigned int j);
    void undoAllLast();

    public:

    TOPBacktrack(std::vector<Vertex*> &vList, std::vector<std::vector<double>> &eMatrix, unsigned int m, double tMax, unsigned int size);
    ~TOPBacktrack();
    void bTrack(unsigned int stepI);
    void printLast();
    void printLocals();
};