#include "../Headers/Traits.h"
using namespace namespace_traits;

Traits Traits::giveTraits(Traits t1, Traits t2) {
  float f = 0.5; // Changeable
  Traits *t3 = new Traits();
  t3->maxEnergy = f * (t1.maxEnergy) + (1 - f) * t2.maxEnergy;
  t3->speed = f * t1.speed + (1 - f) * t2.speed;
  t3->visionRadius = f * t1.visionRadius + (1 - f) * t2.visionRadius;
  return *t3;
}

Traits::Traits(power maxE, velocity v, int vision) {
  this->maxEnergy = maxE;
  this->speed = v;
  this->visionRadius = vision;
}

Traits::Traits() { maxEnergy = 10; }
