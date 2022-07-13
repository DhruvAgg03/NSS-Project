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
            // need to create an array of organism, need the right scope
            // also need to get the size of the matrix, for now staying 1000x1000 (can malloc also be applied to this environment ??)
            //organism*[1000][1000] environment;
        public:
            //Constructor also creates static list of moves
            // Parameters for constructor ->
            Universe(int maxR);
            void printMoves();
            std::vector<struct step> getMoves();
            //organism* getObject(int posX, int posY); // need to define the scope :)
            //void updateUniverse(int initX,int initY,int finalX, int finalY);

    };

}
