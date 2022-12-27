#include "../Headers/Universe.h"
#include <iostream>

using namespace std;
using std::cout;
int main()
{
  srand(time(0));
  int organismCount[2] = {PlantCount, InsectCount};
  biodata_Plant variety_Plant[varieties_in_a_Species];
  biodata_Insect variety_Insect[varieties_in_a_Species];
  ofstream outfile;
  outfile.open("./Output/universelog.txt", ios::out);
  Universe myUni(maxVision, organismCount, variety_Plant, variety_Insect);
  // Universe(int maxR, int *organismCount, biodata_Plant *plantVarieties,
  // biodata_Insect *insectVarieties); maxVision specifies the maximum vision radius
  // organismCount -> Number of induviduals in each species ([0] for food
  // sources, [1] for first trophic level, [2] for second trophic level...(for
  // now just till first trophic level)) plantVarieties list of maxenergies of
  // the different plant sources, insectVarieties the three unique combinations
  // for {vision_radius, speed, and max_energy}
  myUni.run();
  outfile.close();
  return 0;
}