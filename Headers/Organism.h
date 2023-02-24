#pragma once
#define INSECT 1
#define PLANT 0
#define movementCost 1
#include "../Headers/Traits.h"
#include <bits/stdc++.h>
using namespace std;
using namespace namespace_traits;
class Aphrodite;
class Universe;
namespace namespace_organism 
{
  struct coordinates2D 
  {
    int x;
    int y;
  };

  struct speed_structure 
  {
    int *speed_list{NULL};
    // list of numbers which on averaging gives speed.
    // Example : [1,1,2,3] => avg speed would be 1.75
    // we can choose how many steps to move per iteration using random or RR
    int len_of_speed_list{0};
    int rr_count{0};
    // round robin count in case we use it
    // rr_count needs to be lower than len_of_speed_list always
  };

  class Organism 
  {
  protected:

    friend class Aphrodite;

    Universe *universe;
    struct coordinates2D position;
    struct speed_structure organism_speed;

    static unsigned short latest_organism_ID;
    int vision_radius;
    int max_energy;
    int current_energy;
    unsigned short int aadhar_number; // Name of organism like John Wick
    int speciesID;  // Represent which species it belongs to (0-> plant, 1-> Insect for now)
    Traits traits;  // class which contains all the traits of the organism (DNA)

  public:
    Organism(int x, int y, int vision_radius, int *speed_list,
            int length_of_speed_list, int max_energy, int current_energy,
            unsigned short int aadhar_number, int speciesID);
    Organism(coordinates2D posn, Traits t,unsigned short int aadhar_number, 
              int speciesID,Universe * universe); //overloaded constructor with Traits object
    ~Organism();
    int get_x() { return position.x; };
    int get_y() { return position.y; };
    coordinates2D get_posn() { return position;} 
    int get_vision_radius() { return vision_radius; };
    Traits get_traits() { return traits; }
    struct speed_structure get_speed_structure() {
      return organism_speed;
    };
    int get_max_energy() { return traits.get_maxenergy(); }
    int get_current_energy() { return current_energy; }
    unsigned short int get_aadhar_number() { return aadhar_number; }
    int get_speciesID() { return speciesID; }
    void addEnergy(int energy);
    void changeX(int newX) { position.x = newX; }
    void changeY(int newY) { position.y = newY; }
    void update(int newX, int newY);
    static unsigned short get_latest_organism_ID(){return latest_organism_ID;}
    void die() 
    {
      delete this; 
    }
    /* organism speed is defined as a structure with 3 fields. 
    Array (why not a vector?) of possible speeds
    the length of array
    the index (round robin count)
    */
    int giveSpeed() { return get_speciesID() == INSECT ? organism_speed.speed_list[organism_speed.rr_count] : 0; }
  };

  class Insect : public Organism {

  private:
    int organism_ID;
    int age{0};
    

  public:
    Insect(int x, int y, int vision_radius, int *speed_list,
          int length_of_speed_list, int max_energy, int current_energy,
          unsigned short int aadhar_number, int organism_ID1, int speciesID);
    Insect(coordinates2D posn, Traits t,unsigned short int aadhar_number, int speciesID,Universe * universe);
    ~Insect();
    int get_organism_ID();
    void update_age(int age){this->age = age;}
    int get_age(){return age;}
    void updateEnergy(power energy){this->current_energy = energy;}
  };
  
  class Plant : public Organism {

  public:
    Plant(int x, int y, int vision_radius, int *speed_list,
          int length_of_speed_list, int max_energy, int current_energy,
          unsigned short int aadhar_number, int speciesID);
    Plant(coordinates2D posn, int energy, unsigned short ano);

  };
} // namespace namespace_organism
