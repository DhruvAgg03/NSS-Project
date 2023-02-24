#include "../Headers/Organism.h"
#include "../Headers/Universe.h"
#include "../Headers/Aphrodite.h"

extern std::ofstream outfile;

void Universe::run()
{
  Aphrodite cupid{this};
  ofstream ofile;
  ofile.open("./Output/Output.txt");
  ofile << "Insects,Plants\n";
  for (int j = 0; j < iterationCount; j++ && printCompleteInfo(j + 1))
  {

    ofile << organismCount[1] << "," << organismCount[0] << '\n';
    auto InsectCopy = getInsects();
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
        // if (nextObj != NULL )
        // {
        // bool isInsect = ((Organism *)nextObj)->get_speciesID() == INSECT;

        outfile << "Insect Detected" << endl;
        if (updateUniverse(x, y, moves[l].x, moves[l].y, outfile) != SUCCESS)
          break;
        // }
        x = moves[l].x;
        y = moves[l].y;
      }

      // HHN's Code:
      // coordinates2D posn;
      // posn.x = currInsect->get_x();
      // posn.y = currInsect->get_y();
      // vector<coordinates2D> poss_posns = adjacent_posns(posn);
      // pair<bool, coordinates2D> reproduce_roll = currInsect->reproduce_oracle(poss_posns);
      // if (reproduce_roll.first == true)
      // {
      //   pair<power, power> parent_child_energy = currInsect->getChildEnergy();
      //   // TODO
      //   // first-> parent, second->child
      //   // Organism * child = new Organism()
      //   // insert child into the vector of organisms
      //    currInsect->updateEnergy(parent_child_energy.first);
      // }

      // Asexual Reproduction
      if (cupid.godSaidYes(currInsect))
      {
        vector<Insect *> daughters = cupid.split(currInsect);
        if (daughters.size() == 2)
        {
          addInsect(daughters[0]);
          addInsect(daughters[1]);
        }
      }
    }
    std::random_shuffle(insects.begin(), insects.end());

    // Plant Spawning
    if (j % plantSpawnInterval == 0)
    {
      reSpawnPlant();
    }
  }
  ofile.close();
}
