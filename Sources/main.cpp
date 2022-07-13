#include <iostream>
#include "Universe.hpp"

using namespace namespace_Universe;

int main()
{
    std::cout << "Hello world!\n";
    Universe myUni(6);
    myUni.printMoves();
    std::cout<<"\n\n\n";
    std::vector<struct step> trialVec = myUni.getMoves();
    for(int i=0;i<trialVec.size();i++)
        std::cout<<"("<<trialVec[i].dist<<","<<trialVec[i].x<<","<<trialVec[i].y<<") ";
    return 0;
}
