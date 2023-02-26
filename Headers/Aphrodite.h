#pragma once
#include "Traits.h"
#include "Universe.h"
#include "Organism.h"
#define iterationCount 100  //Have to think of a way to #define it elsewhere
#define plantSpawnInterval iterationCount/plantSpawnFreq

class Aphrodite
{
    private:
        Universe* universe;

        //Asexual
        float probFunc(int age,int energy); //function of age and energy, max(f(x)) is 0.8 * 0.96 = 0.76 as of now
    public:

        Aphrodite(Universe* universe):universe(universe){}; //Constructor with reference to universe

        //Asexual
        bool godSaidYes(Insect* insect); //Returns true if insect is to be split
        vector<Insect*> split(Insect* insect); //Returns vector of pointers to daughters (kills the parent)
        vector<Traits*> inheritedTraits(Insect* insect); //Returns vector of traits of daughters
        
        //Sexual
        bool willReproduce(Insect* I1, Insect* I2);
        
};
