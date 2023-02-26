#include "../Headers/Organism.h"
#include "../Headers/Traits.h"
#include "../Headers/Universe.h"

using namespace namespace_traits;
using namespace namespace_organism;
extern std::ofstream outfile;

unsigned short int Organism::latest_organism_ID{1};

Organism::Organism(int x, int y, int vision_radius, int *speed_list,
                   int length_of_speed_list, int max_energy, int current_energy,
                   unsigned short int aadhar_number, int speciesID) {
  this->position = {x, y};
  this->vision_radius = vision_radius;
  this->organism_speed = {speed_list, length_of_speed_list, 0};
  this->max_energy = max_energy;
  this->current_energy = current_energy;
  this->aadhar_number = aadhar_number;
  this->latest_organism_ID = aadhar_number;
  this->sexualUrge = 0;
  this->speciesID = speciesID; // Represent which species it belongs to (0->
                               // plant, 1-> Insect for now)
  // update universe method
  this->traits = Traits(max_energy, 3, vision_radius);
  vector<string> vs{"Plant ","Insect "};
  outfile<<vs[speciesID]<<" "<<aadhar_number<<" born with "<<current_energy<<"/"<<max_energy<<" energy at ("<<(this->position).x<<","<<(this->position).y<<")\n";
};

Organism::Organism(coordinates2D posn, Traits t,unsigned short int aadhar_number, 
                  int speciesID, Universe * universe, bool g)
  : position{posn}, traits{t}, aadhar_number{aadhar_number}, speciesID{speciesID} , universe{universe}
{
  this->gender = g;
  int * _speedList = new int[1];
  _speedList[0] = t.get_speed();
  this->organism_speed = {_speedList, 1, 0};
  current_energy = traits.get_maxenergy();
  max_energy = traits.get_maxenergy();
  vision_radius = traits.get_visionradius();
  this->latest_organism_ID = aadhar_number;
  vector<string> vs{"Plant ","Insect "};
  outfile<<vs[speciesID]<<aadhar_number<<" born with "<<current_energy<<"/"<<max_energy<<" energy at ("<<(this->position).x<<","<<(this->position).y<<")\n";
}

Organism::~Organism() {
  // update universe method
  vector<string> vs{"Plant ","Insect "};
  outfile<<vs[speciesID]<<aadhar_number<<" died with "<<current_energy<<"/"<<max_energy<<" energy at ("<<(this->position).x<<","<<(this->position).y<<")\n";
}

void Organism::addEnergy(int energy) {
  if (energy > 0)
    current_energy = current_energy + energy > max_energy
                         ? max_energy
                         : current_energy + energy;
  else
    current_energy = current_energy + energy > 0 ? current_energy + energy : 0;
}

void Organism::update(int newX, int newY) {
  int energyChange = 0;
  energyChange -= newX > position.x ? newX - position.x : position.x - newX;
  energyChange -= newY > position.y ? newY - position.y : position.y - newY;
  addEnergy(energyChange * movementCost);
  changeX(newX);
  changeY(newY);
}

Insect::Insect(int x, int y, int vision_radius, int *speed_list,
               int length_of_speed_list, int max_energy, int current_energy,
               unsigned short int aadhar_number, int organism_ID1,
               int speciesID)
    : Organism(x, y, vision_radius, speed_list, length_of_speed_list,
               max_energy, current_energy, aadhar_number, speciesID) {
  this->organism_ID = organism_ID1;
};

//Current Constructor Used
Insect::Insect(coordinates2D posn, Traits t,unsigned short int aadhar_number, int speciesID, Universe * universe)
: Organism(posn, t, aadhar_number, speciesID, universe)
{
  this->organism_ID = aadhar_number;
}

Insect::~Insect() {

  outfile<<"Organism "<<aadhar_number<<" with ID "<<organism_ID<<" died with "<<current_energy<<"/"<<max_energy<<" energy at ("<<(this->position).x<<","<<(this->position).y<<")\n";
}

int Insect::get_organism_ID() { return organism_ID; }

Plant::Plant(int x, int y, int vision_radius, int *speed_list,
             int length_of_speed_list, int max_energy, int current_energy,
             unsigned short int aadhar_number, int speciesID)
    : Organism(x, y, 0, NULL, 0, max_energy, current_energy, aadhar_number,
               speciesID){};

Plant::Plant(coordinates2D posn, int energy, unsigned short ano)
  :Organism(posn.x,posn.y,0,NULL,0,energy,energy,ano,0){};

