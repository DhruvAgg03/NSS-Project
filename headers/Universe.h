#include<stdio.h>
#include<vector>

namespace namespace_Universe
{
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
