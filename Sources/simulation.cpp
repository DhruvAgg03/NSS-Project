
#include "../Headers/Organism.h"
#include "../Headers/Universe.h"
using namespace namespace_Universe;
using namespace namespace_organism;
void Universe::run() {

  // for (int i = 0; i < InsectPosition.size(); i++)
  // {
  //     Insect *insect = (Insect
  //     *)environment[get<0>(InsectPosition[i])][get<1>(InsectPosition[i])];

  //     step initial_posn = {get<0>(InsectPosition[i]),
  //     get<1>(InsectPosition[i]), 0}; #warning "steps are always constant"
  //     vector<step> path = movesToLocationNew(initial_posn, 2,
  //     insect->get_vision_radius());

  // }

  for (int j = 0; j < iterationCount; j++) {
    for (int i = 0; i < InsectPosition.size(); i++) {
      auto [x, y] = getAnInsect(i);
      auto temp = (namespace_organism::Organism *)getObject(x, y);
      auto moves = movesToLocationNew({x, y, 0}, 5, temp->get_vision_radius());
      for (int j = 0; j < moves.size(); j++) {
        auto tempPtr = getObject(moves[j].x, moves[j].y);
        updateUniverse(x, y, moves[j].x, moves[j].y);
        if (tempPtr != NULL) {
          if (((Organism *)tempPtr)->get_speciesID() == 1) {
            cout << "Collision with an insect, insect overridden" << endl;
            break;
          }
          break;
        }
        x = moves[j].x;
        y = moves[j].y;
      }
    }
  }
}