#pragma once
#include <bits/stdc++.h>
#include "Organism.h"
#define N 2                      // Changed it to 2
#define dimension 100            // Changing dimensions to 10k from 1k
#define varieties_in_a_Species 3 // Three different Varieties For now there are three species varying
#define maxVision 15
#define initialPlantCount 200
#define initialInsectCount 200
#define insectIndex 1
#define plantIndex 0
#define maxEnergy 300
#define plantSpawnFreq 5
#define plantSpawnNumber ((initialPlantCount)/(plantSpawnFreq))
#define minimumMatingEnergyPercentage 0.5

using namespace std;
using namespace namespace_organism;
class Aphrodite;

// Contains x,y deviation and dist from origin
struct step
{
    int x;
    int y;
    float dist;
};

enum UpdateUniverse_rt
{
  SUCCESS = 0,
  INVALID_ORGANISM = 1,
  DYING_ORGANISM = -2,
  STOP_PATH = -3,
};

// Necessary Information to declare a Plant Object
struct biodata_Plant
{
    // // struct coordinates2D position; since position decided from the random temporary array
    // // int vision_radius; will be equal to zero
    // // int speed zero
    int max_energy;
    // unsigned short int aadhar_number Adhaar number is assigned while declaring
};

// Necessary Information to declare an Insect Object
struct biodata_Insect
{
    // struct coordinates2D position; since position decided from the random temporary array
    int vision_radius;
    int speed; // struct speed_structure speed_structure;
    int max_energy;
    int maxSexualUrge;
    int desirability; //Random number from 1 to 100
};

class Universe
{
private:

    friend class Aphrodite;

    // //Organism *classes[N]; // classes in terms of species ?? then we have only 2 varying species right right now ??

    int organismCount[N]; 
    // Plant(Producer) then Insect(First Trophic Level) Not required since merely passed as an argument but maybe can store it as an attribute for later use
    
    biodata_Plant variety_Plant[varieties_in_a_Species]; 
    // three unique types of plants-> as in all instances fall in one of these three categories 
    
    biodata_Insect variety_Insect[varieties_in_a_Species]; 
    // three unique combinations for {vision_radius, speed, max_energy and sexual urge} -> all instances of organisms fall in one of these three categories
    
    vector<tuple<int, int>> InsectPosition; //record of all insect positions

    vector<step> moves; //visionarray (-maxR,-maxR) to (maxR,maxR) with distance from origin

    void *environment[dimension][dimension];
    // Pointer to the object at that location, if no object then NULL (change to Organism*)

    int displayEnvironment[dimension * dimension] = {0}; // For a given iteration holds the displayable data, (For now species is number) For now will be a flattened Matrix of the environment
    // vector<int[dimension * dimension]> historyEnvironment; // Hold atleast the layout of the environment at any point in the Iteration
    
    vector<int *> historyEnvironment;
    
    vector<struct biodata_Insect> ledgerInsects; 
    // Whether we should change the struct based on what we want to store in the beside vector is what I am thinking,Useful for graphing Traits and creating Histograms

    vector<coordinates2D> emptycells(int k);
    // returns positions of k empty cells in the environment (expected to return k , but can be <k due to randomness )

    map<Insect* ,Insect*> Organisms_in_love;
    //Tells us whether two organisms are locked in to reproduce or not (entries using pointer to insect object)

public:
    vector<Insect *> insects;

    void run();
    //Essentialy everything that happens in the universe

    vector<coordinates2D> adjacent_posns(coordinates2D pos);
    // Returns the adjacent positions of the given position (all 4)

    Universe(int maxR, int *organismCount, 
            biodata_Plant variety_Plant[varieties_in_a_Species], 
            biodata_Insect variety_Insect[varieties_in_a_Species]);
    // maxR specifies the maximum vision radius
    // organismCount -> Number of induviduals in each species ([0] for food sources, [1] for first trophic level, [2] for second trophic level...(for now just till first trophic level))
    // plantVarieties list of maxenergies of the different plant sources,
    // insectVarieties the three unique combinations for {vision_radius, speed, and max_energy}
    
    void printMoves(ofstream& outfile);
    //prints moves vector

    vector<step> getMoves();
    //returns moves vector

    void createMovesVector(int maxR);
    // creates the Vision Array

    void initializeVarieties(biodata_Plant *plantVarieties, biodata_Insect *insectVarieties); 
    // A function that takes the varieties as input and creates the variety_Plant/Insect list
    
    void initializeEnvironment(int *organismCount, int len);
    // Based on number of organisms create the necessary pointers

    vector<Insect *> getInsects();
    // Returns the list of Insects

    void *getObject(int posX, int posY);
    // Returns the void pointer to the specific location

    UpdateUniverse_rt updateUniverse(int initX, int initY, int finalX, int finalY, ofstream& outfile);
    // Lets us move the initial to the final position, leaving the previous position blank,
    // returns non zero value if an insect was killed, -1 if movement not possible, -2 for death

    void deathOfInsect(int i, int &counter);
    // Deletes that coordinate and pushes all the other tuples back up once
    // Also takes a counter/reference as an argument to update the counter as in an 
    // iteration we run over the InsectPosition list
    
    void killInsect(Insect *insect);
    // Updates envitonment and insects list

    int getNumberOfInsects();
    // Returns the length of the InsectPosition list (ie number of organisms) 
    // This needs to run after every Travel of an organism
    
    tuple<int, int> getAnInsect(int i); 
    // Returns the Position of the ith Insect in the List InsectPosition

    void creatingAndUpdatingDisplayEnvironmentHistory(ofstream& outfile); 
    // Should create a 1D array(For now) all the rows are flattened
    
    void writingToFile(ofstream& outfile);

    bool printCompleteInfo(int iteration);
    // Prints the complete information of the Insects in the Universe

    step scanNearestFoodSourceNew(step current_position, int vision_radius, set<pair<int, int>> &ignore_food); // returns the nearest food source from the current position. If none, returns -1,-1. (Can add in another parameter saying levelOfOrganism in case of multiple levels of predators and prey)
    // Kalva's code for nearest food source

    step scanNearestMate(step current_position,int vision_radius, Insect* protagonist); //returns the coordinate of the first mate within vision radius which WILL mate with this organism (if returns true, organisms definitely mate)

    bool canMeetAndMate(Insect* protagonist, step protagonist_location, step interest_location); //checks whether two organisms have enough energy to reach each other and mate

    vector<step> movesToLocationNew(step current_position, int number_of_steps, int vision_radius);            // returns the next few moves given current position and destination (shortest path, no diagonal movements)
    // Returns the sequence of steps to reach the destination(food source) as of now

    void addInsect(Insect *insect);
    //Inducts the new insect into the universe

    void addPlant(Plant* plant);
    //Inducts the new plant into the universe

    bool locked(coordinates2D pos);
    //returns true if all of its 8 neighbours are not free

    void reSpawnPlant();
    // respawns plants at random locations

    bool willReproduce(Insect *I1,Insect *I2);
};

