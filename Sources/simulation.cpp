
#include "../Headers/Organism.h"
#include "../Headers/Universe.h"
// using namespace namespace_Universe;
// using namespace namespace_organism;
void Universe::run()
{

  for (int j = 0; j < iterationCount; j++)
  {
    auto InsectCopy = getInsects();
    printCompleteInfo(j + 1);

    for (int i = 0; i < InsectCopy.size(); i++)
    {
      auto currInsect = InsectCopy[i];
      currInsect->update_age(currInsect->get_age() + 1);
      int x = currInsect->get_x();
      int y = currInsect->get_y();
      auto moves = movesToLocationNew({x, y, 0}, currInsect->giveSpeed(), currInsect->get_vision_radius());

      for (int l = 0; l < moves.size(); l++)
      {
        auto nextObj = getObject(moves[l].x, moves[l].y);
        if (nextObj != NULL)
        {
          if (((Organism *)nextObj)->get_speciesID() == 1)
            cout << "Insect Detected" << endl;
          else if (((Organism *)nextObj)->get_speciesID() == 0)
            updateUniverse(x, y, moves[l].x, moves[l].y);

          break;
        }
        if (updateUniverse(x, y, moves[l].x, moves[l].y) != 0)
          break;
        x = moves[l].x;
        y = moves[l].y;
      }
      cordinates2D posn;
      posn.x = currInsect->get_x();
      posn.y = currInsect->get_y();
      vector<cordinates2D> poss_posns = adjcent_posns(posn);
      pair<bool, cordinates2D> reproduce_roll = currInsect->reproduce_oracle(poss_posns);
      if (reproduce_roll.first == true)
      {
        pair<power, power> parent_child_energy = currInsect->getChildEnergy();
        // TODO
        // first-> parent, second->child
        // Organism * child = new Organism()
        // insert child into the vector of organisms
        currInsect->updateEnergy(parent_child_energy.first);
      }
    }
    random_shuffle(insects.begin(), insects.end());
  }
}