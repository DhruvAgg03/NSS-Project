#pragma once
#define power int
#define velocity int

namespace namespace_traits {
class Traits {
private:
  power maxEnergy;
  velocity speed;
  int visionRadius;

  Traits giveTraits(Traits t1, Traits t2);

public:
  Traits(power maxE, velocity v, int vision);
  Traits();
};
} // namespace namespace_traits
