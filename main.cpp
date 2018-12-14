#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cmath>
#include <string>

#include "Vertex.hpp"
#include "TOPBacktrack.hpp"

double euclideanDistance(double x_1, double x_2, double y_1 , double y_2)
{
    return sqrt(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2));
}


void addEdge(std::vector<std::vector<double>> &matrix, std::vector<Vertex*> &list, unsigned int index)
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

int main(int argc, char **argv)
{
    TOPBacktrack *instance;
    unsigned int nodes, routesAmm;
    double maxT, x, y, score;
    std::string foo;
    std::vector<Vertex*> *vertexList;
    std::vector<std::vector<double>> *edgeMatrix;

    while(std::cin >> foo >> nodes)
    {
        std::cin >> foo >> routesAmm;
        std::cin >> foo >> maxT;
        vertexList = new std::vector<Vertex*>(nodes);
        edgeMatrix = new std::vector<std::vector<double>>(nodes);
        for(unsigned int i = 0; i < nodes; i++)
        {
            (*edgeMatrix)[i] = std::vector<double>(nodes, 0);
        }
        for(unsigned int i = 0; i < nodes; i++)
        {
            std::cin >> x >> y >> score;
            (*vertexList)[i] = new Vertex(x, y, score);
            addEdge((*edgeMatrix), (*vertexList), i);
        }
        instance = new TOPBacktrack((*vertexList), (*edgeMatrix), routesAmm, maxT, nodes);
        vertexList = nullptr;
        edgeMatrix = nullptr;
        std::cout << nodes << std::endl << routesAmm << std::endl << maxT << std::endl;
        (*instance).bTrack(1);
        (*instance).printLast();
        delete instance;
    }
    return 0;
}