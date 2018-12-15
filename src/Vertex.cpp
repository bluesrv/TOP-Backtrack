#include "Vertex.hpp"
#include <vector>

/*
    Basic implementation of auxiliary classes with their getters and setters
*/

Vertex::Vertex(double x, double y, double in_score)
{
    x_pos = x;
    y_pos = y;
    score = in_score;
}
double Vertex::getX()
{
    return x_pos;
}
double Vertex::getY()
{
    return y_pos;
}
double Vertex::getScore()
{
    return score;
}

Route::Route(unsigned int m)
{
    times = std::vector<double>(m);
}

void Route::setScore(double s)
{
    score = s;
}

void Route::setTime(unsigned int index, double value)
{
    times[index] = value;
}

void Route::setSub(std::vector<std::vector<unsigned int>> &data)
{
    subRoutes = data;
}

double Route::getScore()
{
    return score;
}

std::vector<double> Route::getTimes()
{
    return times;
}

std::vector<std::vector<unsigned int>> Route::getSubs()
{
    return subRoutes;
}