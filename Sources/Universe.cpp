#include "../headers/Universe.hpp"
#include <algorithm>
#include <math.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <time.h>
using namespace namespace_Universe;


bool compare(const step &a,const step &b)
{
    return a.dist<b.dist;
}
//Compare function used for sorting moves vector comparing two structs

int random_range(int min, int max){
    int in_range = rand();
    in_range = min + in_range%(max-min);
    return in_range;
}
// Generates a random number between given range [min, max)


Universe::Universe(int maxR=5,int *organismCount, biodata_Plant* plantVarieties, biodata_Insect* insectVarieties)
{
    this->createMovesVector(maxR);
    //Creates the VisionArray
    this->initializeVarieties(plantVarieties, insectVarieties);
    this->initializeEnvironment(organismCount,N);
}
// Constructor -
// Input maximum Radius and Number of Organisms per species
// function calls onto create movesVector (Cater to maximum radius and speed) and initialise Environment (Can we rename it VisionArray ??)

void Universe::createMovesVector(int maxR)
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

    std::cout<<"Constructed!!\n";
}


void Universe::initializeVarieties(biodata_Plant* plantVarieties, biodata_Insect* insectVarieties){
    for(int i=0;i<varieties_in_a_Species;i++){
        this->variety_Plant[i] = plantVarieties[i]; 
        this->variety_Insect[i] = insectVarieties[i];
    }
    // The memory address initially stored in the pointers are the same, the values it points to are different 
}


void Universe::initializeEnvironment(int *organismCount,int len)
{
    // Generating an array of all the coordinates 
    std::vector<std::tuple<int,int>> tempPoints; // temporary Points
    for(int i=0;i<dimension;i++)
        for(int j=0;j<dimension;j++)
            tempPoints.push_back(std::make_tuple(i,j));
    std::random_shuffle(tempPoints.begin(),tempPoints.end());

    // Assigning the elements of environment to the necessary instances 
    int counter=0; //Running over the temporary array becomes the name of the organism
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<organismCount[i];j++)
        {
            if(i==0){
                int variety = random_range(0, varieties_in_a_Species);// I am calling it seperately so that later on can bring in variation in the food source amount (Maybe Continuous Distribution)
                namespace_organism::Plant temp(0, tempPoints[counter][0], tempPoints[counter][1], 0, NULL, variety_Plant[variety].max_energy, variety_Plant[variety].max_energy, counter);
                environment[std::get<0>(tempPoints[counter])][std::get<1>(tempPoints[counter])] = &temp;
            }
            else if(i==1){
                int variety = random_range(0, varieties_in_a_Species);
                namespace_organism::Insect temp(1, tempPoints[counter][0], tempPoints[counter][1], NULL, variety_Insect[variety].speed, variety_Insect[variety].max_energy, variety_Insect[variety].max_energy, counter);
                environment[std::get<0>(tempPoints[counter])][std::get<1>(tempPoints[counter])] = &temp;
                InsectPosition.push_back(std::make_tuple(std::get<0>(tempPoints[counter]), std::get<1>(tempPoints[counter])));
            }
            counter++;
        }
    }
    for(int i=counter;i<dimension*dimension;i++)
    {
        environment[std::get<0>(tempPoints[counter])][std::get<1>(tempPoints[counter])]=NULL;
    }
}
// input number of organism (Say the we specify each organism is a list, first element being number of food sources, next being number of prey and so on)
// creating all the coordinates for the matrix using TempPoints (call it temporary Coordinates (TempCoord) ?)
// Creating the functions that assigns the necessary pointers to class based on data we know



std::vector<struct step> Universe::getMoves()
{
    return this->moves;
}

void Universe::printMoves()
{
    int i;//Counter
    for(i=0; i < (this->moves).size(); i++)
        std::cout<<"("<<(this->moves)[i].dist<<","<<(this->moves[i]).x<<","<<(this->moves)[i].y<<") ";
    std::cout<<"\n i is "<<i<<"\n";
    return;
}

void Universe::updateUniverse(int initX,int initY,int finalX, int finalY){
    void* movingObj = environment[initX][initY];
    environment[finalX][finalY] = movingObj;
    environment[initX][initY] = NULL;
}

void* Universe::getObject(int posX, int posY){
    void* reqPoint = environment[posX][posY];
    return reqPoint;
}



