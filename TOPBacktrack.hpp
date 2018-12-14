#pragma once

#include <vector>
#include <cmath>

#include "Vertex.hpp"

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
    bool addSubt = true;
    Route *bestRoute;
    public:
    TOPBacktrack(std::vector<Vertex*> &vList, std::vector<std::vector<double>> &eMatrix, unsigned int m, double tMax, unsigned int size);
    ~TOPBacktrack();
    void bTrack(unsigned int stepI);
    bool addEdge(unsigned int i, unsigned int j);
    bool checkLast();
    void printResult();
    void undo(unsigned int i, unsigned int j);
    void undoAllLast();
    void printLast();
};