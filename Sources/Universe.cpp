#include"Universe.h"
#include<algorithm.h>
#include<math.h>
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
                this->moves.push_back({x,y,sqrt(x*x+y*y)});
            }
        }
    }
    sort(moves.begin(),moves.end(),compare);
    moves.erase(moves.begin()) //removes (0,0,0) from the vector
}

Universe::getMoves()
{
    return this->moves;
}

Universe::printMoves()
{
    int i;//Counter
    for(i=0; i < (this->moves).size(); i++)
        cout<<"("<<(this->moves)[i].dist<<","<<(this->moves[i]).x<<","<<(this->moves)[i].y<<") ";
    cout<<"\n i is "<<i<<endl;
}
