#pragma once
#include<stdio.h>
#include<vector>
#define N 2  //Changed it to 2
#define dimension 10000 // Changing dimensions to 10k from 1k
#define varieties_in_a_Species 3 // Three different Varieties For now there are three species varying 
 

namespace namespace_Universe
{
    //Contains x,y deviation and dist from origin
    typedef struct step
    {
        int x;
        int y;
        float dist;
    }step;

    // Necessary Information to declare a Plant Object
    typedef struct biodata_Plant
    {
        // struct namespace_organism::coordinates2D position; since position decided from the random temporary array
        //int vision_radius; will be equal to zero
        //int speed zero
        int max_energy;
        // unsigned short int name_of_individual Adhaar number is assigned while declaring
    }biodata_Plant;

    // Necessary Information to declare an Insect Object
    typedef struct biodata_Insect
    {
        // struct namespace_organism::coordinates2D position; since position decided from the random temporary array
        int vision_radius;
        int speed; // struct speed_structure speed_structure;
        int max_energy;
    }biodata_Insect;

    class Universe
    {
        private:
            namespace_organism::organism* classes[N]; //classes in terms of species ?? then we have only 2 varying species right rihght now ??
            int organismCount[N]; // Plant(Producer) then Insect(First Trophic Level)
            biodata_Plant variety_Plant[varieties_in_a_Species] = {{0}};
            biodata_Insect variety_Insect[varieties_in_a_Species]={{0}};
            std::vector<std::tuple<int, int>> InsectPosition;
            std::vector<step>moves;
            void* environment[dimension][dimension];

        public:
            Universe(int maxR,int* organismCount, biodata_Plant* plantVarieties, biodata_Insect* insectVarieties);
            // maxR specifies the maximum vision radius
            // organismCount -> Number of induviduals in each species ([0] for food sources, [1] for first trophic level, [2] for second trophic level...(for now just till first trophic level))
            // plantVarieties list of maxenergies of the different plant sources, 
            // insectVarieties the three unique combinations for {vision_radius, speed, and max_energy}

            void printMoves();
            std::vector<step> getMoves();
            
            void* getObject(int posX, int posY);  // Returns the void pointer to the specific location
            void updateUniverse(int initX,int initY,int finalX, int finalY); // Lets us move the initial to the final position, leaving the previous position blank

            void createMovesVector(int maxR); //creates the Vision Array

            // A function that takes the varieties as input and creates the variety_Plant/Insect list
            void initializeVarieties(biodata_Plant* plantVarieties,biodata_Insect* insectVarieties); // Creates the necessary varieties 
            void initializeEnvironment(int *organismCount,int len); // Based on number of organisms create the necessary pointers

    };

}
