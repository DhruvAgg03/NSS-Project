
#include "../headers/Universe.hpp"
#include <algorithm>
#include <math.h>
#include <iostream>
#include <vector>
using namespace namespace_Universe;

//Compare function used for sorting moves vector
bool compare(const step &a,const step &b)
{
    return a.dist<b.dist;
}

Universe::Universe(int maxR=5,int *organismCount)
{
    //Populates static vector
    this->createMovesVector(maxR);
    // generating a random list of coordinates WIll look into it on 14th
    this->initializeEnvironment(organismCount,N);

}

void Universe::initializeEnvironment(int *organismCount,int len)
{
    std::vector<std::tuple<int,int>> tempPoints;
    for(int i=0;i<dimension;i++)
        for(int j=0;j<dimension;j++)
            tempPoints.push_back(std::make_tuple(i,j));
    std::random_shuffle(tempPoints.begin(),tempPoints.end());
    int counter=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<organismCount[i];j++)
        {
            environment[tempPoints[counter][0]][tempPoints[counter][1]]=classes[i];
            counter++;
        }
    }
    for(int i=counter;i<dimension*dimension;i++)
    {
        environment[tempPoints[counter][0]][tempPoints[counter][1]]=NULL;
    }
}

void Universe::createMovesVector(int maxR)
{
    float temp=maxR*maxR;
    for(int x=-maxR;x<=maxR;x++)
    {
        for(int y=-maxR;y<=maxR;y++)
        {
            if(x*x+y*y<=temp)
            {
                struct step tempstep;
                tempstep.x = x;
                tempstep.y = y;
                tempstep.dist = sqrt(x*x+y*y);
                (this->moves).push_back(tempstep);
            }
        }
    }
    sort(moves.begin(),moves.end(),compare);
    moves.erase(moves.begin()); //removes (0,0,0) from the vector

    std::cout<<"Constructed!!\n";
}

std::vector<struct step> Universe::getMoves()
{
    return this->moves;
}

void Universe::printMoves()
{
    int i;//Counter
    for(i=0; i < (this->moves).size(); i++)
        std::cout<<"("<<(this->moves)[i].dist<<","<<(this->moves[i]).x<<","<<(this->moves)[i].y<<") ";
    std::cout<<"\n i is "<<i<<"\n";
    return;
}


Universe::updateUniverse(int initX,int initY,int finalX, int finalY){
    organism* movingObj = environment[initX][initY];
    environment[finalX][finalY] = movingOgj;
    environment[initX][initY] = void;
}

Universe::getObject(int posX, int posY){
    organism* reqPoint = environment[posX][posY];
    return reqPoint;
}




