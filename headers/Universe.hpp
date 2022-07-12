#pragma once
#include<stdio.h>
#include<vector>

namespace namespace_Universe
{
    //Contains x,y deviation and dist from origin
    typedef struct step
    {
        int x;
        int y;
        float dist;
    };

    class Universe
    {
        private:
            std::vector<struct step>moves;
        public:
            //Constructor also creates static list of moves
            Universe(int maxR);
            void printMoves();
            std::vector<struct step> getMoves();

    };

}
