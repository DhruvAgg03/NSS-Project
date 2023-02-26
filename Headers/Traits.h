#pragma once
#define power int
#define velocity int

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

  Traits giveTraits(Traits t1, Traits t2);

public:
  Traits(power maxE, velocity v, int vision);
  Traits();
  Traits(power maxE,velocity v, int vision, int maxSexualUrge, int desirability); //For sexual reproduction
  int get_maxenergy() { return maxEnergy; }
  int get_speed() { return speed; }
  int get_visionradius() { return visionRadius; }
  void set_maxenergy(power maxE) { maxEnergy = maxE; }
  void set_speed(velocity v) { speed = v; }
  void set_visionradius(int vision) { visionRadius = vision; }
};
} // namespace namespace_traits
