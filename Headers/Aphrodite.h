#pragma once
#include "Traits.h"
#include "Universe.h"
#include "uservalues.h"

class Aphrodite
{
    private:
        Universe* universe;

        //Asexual
        float probFunc(int age,int energy); //function of age and energy, max(f(x)) is 0.8 * 0.96 = 0.76 as of now
        int mutationsynthesizer(int trait,int prob); //Returns a mutated trait (used to mutate traits of daughters)
    public:

        Aphrodite(Universe* universe):universe(universe){}; //Constructor with reference to universe

        //Asexual
        bool godSaidYes(Insect* insect); //Returns true if insect is to be split
        vector<Insect*> split(Insect* insect); //Returns vector of pointers to daughters (kills the parent)
        vector<Traits*> inheritedTraits(Insect* insect); //Returns vector of traits of daughters
        

        //Sexual
        Insect* mating(Insect* insect1,Insect* insect2); //Returns pointer to child
        Traits inheritedTraits(Insect* insect1,Insect* insect2); //Returns traits of child
        
};