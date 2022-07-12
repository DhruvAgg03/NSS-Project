#include "../headers/Universe.hpp"
#include <algorithm>
#include <math.h>
#include <iostream>
#include <vector>
using namespace namespace_Universe;


bool compare(const step &a,const step &b)
{
    return a.dist<b.dist;
}

Universe::Universe(int maxR=5)
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

    // generating a random list of coordinates WIll look into it on 14th


}

/* Universe::getMoves()
{
    std::vector<struct step> allmoves;
    for(int i = 0; i<(this->moves).size(); i++){
        struct step tempstep;
        tempstep.x = (this->moves)[i].x;
        tempstep.y = (this->moves)[i].y;
        tempstep.dist = (this->moves)[i].dist;
        allmoves.push_back(tempstep);
    }
    return allmoves;
}*/

Universe::printMoves()
{
    int i;//Counter
    for(i=0; i < (this->moves).size(); i++)
        std::cout<<"("<<(this->moves)[i].dist<<","<<(this->moves[i]).x<<","<<(this->moves)[i].y<<") ";
    std::cout<<"\n i is "<<i<<"\n";
    return 0;
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

int main(){
    std::cout << "Compiled"<<"\n";  
}
