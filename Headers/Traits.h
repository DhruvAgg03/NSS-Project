#pragma once
#define power int
#define velocity int
#include "uservalues.h"

class Aphrodite;

namespace namespace_traits {
class Traits {
private:

  friend class Aphrodite;
  friend class Organism;
  friend class Universe;

  power maxEnergy;
  velocity speed;
  int visionRadius;
  int maxSexualUrge;
  int desirability;

  Traits giveTraits(Traits t1, Traits t2);

public:
  Traits(power maxE, velocity v, int vision);
  Traits();
  Traits(power maxE,velocity v, int vision, int maxSex, int desirability); //For sexual reproduction
  int get_maxenergy() { return maxEnergy; }
  int get_speed() { return speed; }
  int get_visionradius() { return visionRadius; }
  int get_maxSexualUrge() { return maxSexualUrge; }
  int get_desirability() { return desirability; }
  void set_maxenergy(power maxE) { maxEnergy = maxE; }
  void set_speed(velocity v) { speed = v; }
  void set_visionradius(int vision) { visionRadius = vision; }
  void set_maxSexualUrge(int maxSex) { maxSexualUrge = maxSex; }
  void set_desirability(int desirability) { this->desirability = desirability; }
};
} // namespace namespace_traits
