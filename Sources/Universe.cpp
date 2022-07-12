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

int main(){
    std::cout << "Compiled"<<"\n";  
}
