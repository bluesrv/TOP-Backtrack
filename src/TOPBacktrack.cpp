#include <vector>
#include <cmath>
#include <iterator>
#include <iostream>

#include "Vertex.hpp"
#include "TOPBacktrack.hpp"

/*
    Implementation of methods described in TOPBacktrack.hpp
*/

TOPBacktrack::TOPBacktrack(std::vector<Vertex*> &vList, std::vector<std::vector<double> > &eMatrix, unsigned int m, double tMax, unsigned int size)
{
    vertexList = &vList;
    edgeMatrix = &eMatrix;
    routesAmm = m;
    maxT = tMax;
    
    results =  new std::vector<std::vector<unsigned int> >();
    bestRoute = new Route(m);


    y = new std::vector<bool>(size, false);
    (*y)[0] = true;
    (*y)[size - 1] = true; 
    x = new std::vector<std::vector<bool> >(size);
    z = new std::vector<std::vector<double> >(size);
    for(unsigned int i = 0; i < size; i++)
    {
        (*x)[i] = std::vector<bool>(size, false);
        (*z)[i] = std::vector<double>(size, 0);
    }
}

TOPBacktrack::~TOPBacktrack()
{
    delete edgeMatrix;
    delete vertexList;
    delete y;
    delete x;
    delete z;
    delete results;
    delete bestRoute;
}


bool TOPBacktrack::addEdge(unsigned int i, unsigned int j)
{
    if((*x)[i][j]) return false;
    bool restr1 = (*edgeMatrix)[i][j] <= maxT;
    if(j == 0 && addSubt && restr1)
    {
        (*x)[i][j] = true;
        (*x)[j][i] = true;
        (*z)[i][j] = (*edgeMatrix)[i][j];
        (*z)[j][i] = (*edgeMatrix)[i][j];
        (*y)[i] = true;
        m++;
        if(m == routesAmm) addSubt = false;
        (*results).push_back(std::vector<unsigned int>());
        ((*results)[(*results).size() - 1]).push_back(0);
        ((*results)[(*results).size() - 1]).push_back(i);
        currScore += (*(*vertexList)[i]).getScore();
        return true;
    }
    else if (j == 0)
    {
        return false;
    }
    bool restr2 = false;
    double arrTime = 0;
    for(unsigned int aux = 0; aux < (*z)[j].size(); aux++)
    {
        if((*z)[j][aux] != 0)
        {   
            arrTime = (*z)[j][aux] + (*edgeMatrix)[i][j];
            restr2 = arrTime <= maxT;
        }
    }
    if(restr2 && !(*y)[i])
    {
        (*x)[i][j] = true;
        (*z)[i][j] = arrTime;
        (*x)[j][i] = true;
        (*z)[j][i] = arrTime;
        (*y)[i] = true;
        for(unsigned int aux = 0; aux < (*results).size(); aux++)
        {
            if(j == (*results)[aux].back())
            {
                (*results)[aux].push_back(i);
                currScore += (*(*vertexList)[i]).getScore();
            }
        }
        return true;
    }
    return false;
}


bool TOPBacktrack::checkLast()
{
    if((*results).size() > routesAmm) return false;
    bool returnBool = true;
    unsigned int j_1, j_2;
    double arrTime;
    for(unsigned int i = 0; i < m; i++)
    {
        j_1 = (*results)[i].back();
        j_2 = (*results)[i][(*results)[i].size() - 2];
        arrTime = (*z)[j_1][j_2] + (*edgeMatrix)[(*y).size() - 1][j_1]; 
        returnBool = returnBool && arrTime <= maxT;
        (*z)[(*y).size() - 1][j_1] = arrTime;
        (*x)[(*y).size() - 1][j_1] = true;
        (*z)[j_1][(*y).size() - 1] = arrTime;
        (*x)[j_1][(*y).size() - 1] = true;
    };
    return returnBool;
}


void TOPBacktrack::printResult()
{
    bool flag = false;
    if(currScore > sBest)
    {
        unsigned int index;
        for(unsigned int i = 0; i < m; i++)
        {
            index = (*results)[i].back();
            (*bestRoute).setTime(i, (*z)[(*y).size() - 1][index]);
        }
        (*bestRoute).setSub((*results));
        (*bestRoute).setScore(currScore);
        sBest = currScore;
        flag = true;
    }
    if(flag && pLocals)
    {
        std::cout << currScore << std::endl;
        for(unsigned int i = 0; i < m; i++)
        {
            for(unsigned int j = 0; j < (*results)[i].size(); j++)
            {
                if(j == 0) std::cout << (*z)[(*y).size() - 1][(*results)[i].back()] << " ";
                std::cout << " " << (*results)[i][j] + 1;
            }
            std::cout << " " << (*y).size() << std::endl;
        }
    }
}

void TOPBacktrack::undo(unsigned int i, unsigned int j)
{
    (*x)[i][j] = false;
    (*z)[i][j] = 0;
    (*x)[j][i] = false;
    (*z)[j][i] = 0;
    (*y)[i] = false;
    currScore -= (*(*vertexList)[i]).getScore();
    for(unsigned int aux = 0; aux < m; aux++)
    {
        if((*results)[aux].back() == i)
        {
            if(j == 0)
             {
                 m--;
                 addSubt = true;
                 (*results).erase((*results).begin() + aux);
                 return;
             }
             (*results)[aux].pop_back();
        }
    }
    
}

void TOPBacktrack::printLocals()
{
    pLocals = true;
}

void TOPBacktrack::undoAllLast()
{
    unsigned int j;
    for(unsigned int i = 0; i < m; i++)
    {
        j = (*results)[i].back();
        (*z)[(*y).size() - 1][j] = 0;
        (*x)[(*y).size() - 1][j] = false;
        (*z)[j][(*y).size() - 1] = 0;
        (*x)[j][(*y).size() - 1] = false;
    }
}

void TOPBacktrack::printLast()
{
    std::cout << (*bestRoute).getScore() << std::endl;
    std::vector<std::vector<unsigned int> > lastresults = (*bestRoute).getSubs();
    std::vector<double> lasttimes = (*bestRoute).getTimes();
    for(unsigned int i = 0; i < lastresults.size(); i++)
    {
        for(unsigned int j = 0; j < lastresults[i].size(); j++)
        {
            if(j == 0) std::cout << lasttimes[i] << " ";
            std::cout << " " << lastresults[i][j] + 1;
        }
        std::cout << " " << (*y).size() << std::endl;
    }
}

void TOPBacktrack::bTrack(unsigned int stepI)
{
    if(stepI == (*y).size() - 1)
    {
        if(checkLast())
        {
            printResult();
        }
        undoAllLast();
        return;
    }
    else if(addSubt && (stepI != 0 || stepI != (*y).size() - 1) && !(*y)[stepI])
    {
        if(addEdge(stepI,0))
        {
            bTrack(stepI + 1);
            undo(stepI,0);
        }
    }
    if(!(*y)[stepI])
    {
        unsigned int j;
        for(unsigned int i = 0; i < (*results).size(); i++)
        {
            j = (*results)[i].back();
            if(addEdge(stepI, j))
            {
                bTrack(stepI + 1);
                undo(stepI,j);
            }
        }
        bTrack(stepI + 1);
    }
}