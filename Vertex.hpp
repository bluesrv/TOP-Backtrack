#pragma once

#include <vector>

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

class Route
{
    private:
    double score;
    std::vector<double> times;
    std::vector<std::vector<unsigned int>> subRoutes;
    public:
    Route(unsigned int m);
    void setScore(double s);
    void setTime(unsigned int index, double value);
    void setSub(std::vector<std::vector<unsigned int>> &data);
    std::vector<double> getTimes();
    double getScore();
    std::vector<std::vector<unsigned int>> getSubs();
};