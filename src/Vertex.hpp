#pragma once

#include <vector>

/*
    Auxiliary class to store all that belongs to a vertex
*/

class Vertex
{
    private:
    double x_pos, y_pos, score;
    public:
    Vertex(double x, double y, double in_score);
    double getX();
    double getY();
    double getScore();
};

/*
    Class that represents a solution, it has a matrix with the routes, and a lists with the times that correspondand indexes of routes takes
    Also it keeps their score
*/

class Route
{
    private:
    double score;
    std::vector<double> times; // constant use of stack memory, it is reasigned with copies so reutilized
    std::vector<std::vector<unsigned int>> subRoutes; // idem
    public:
    Route(unsigned int m);
    void setScore(double s);
    void setTime(unsigned int index, double value);
    void setSub(std::vector<std::vector<unsigned int>> &data);
    std::vector<double> getTimes();
    double getScore();
    std::vector<std::vector<unsigned int>> getSubs();
};