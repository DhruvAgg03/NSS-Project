#include <iostream>
#include "../headers/Universe.hpp"

using namespace namespace_Universe;

int main()
{
    std::cout << "Hello world!\n";
    int organismCount[2] = {1, 2};
    biodata_Plant variety_Plant[varieties_in_a_Species];
    biodata_Insect variety_Insect[varieties_in_a_Species];
    Universe myUni(5, organismCount, variety_Plant, variety_Insect);
    // Universe(int maxR, int *organismCount, biodata_Plant *plantVarieties, biodata_Insect *insectVarieties);
    // maxR specifies the maximum vision radius
    // organismCount -> Number of induviduals in each species ([0] for food sources, [1] for first trophic level, [2] for second trophic level...(for now just till first trophic level))
    // plantVarieties list of maxenergies of the different plant sources,
    // insectVarieties the three unique combinations for {vision_radius, speed, and max_energy}
    myUni.printMoves();
    std::cout << "\n\n\n";
    std::vector<struct step> trialVec = myUni.getMoves();
    for (int i = 0; i < trialVec.size(); i++)
        std::cout << "(" << trialVec[i].dist << "," << trialVec[i].x << "," << trialVec[i].y << ") " << endl;
    return 0;
}
