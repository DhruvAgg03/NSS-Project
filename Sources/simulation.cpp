#include "../Headers/Organism.h"
#include "../Headers/Universe.h"
#include "../Headers/Aphrodite.h"

// Actions in output file

#define MOVE 0
#define BIRTH 1
#define SPLIT 2
#define DIE 3
#define Asexual 0
#define Sexual 1
#define REPRODUCETYPE Sexual
#define increaseSexualUrge 1

extern std::ofstream outfile;
extern std::ofstream simulationFile;
extern int iterNum;

void Universe::run()
{
  cout << "Pc Ic\n";
  Aphrodite cupid{this};
  ofstream ofile;
  ofile.open("./Output/Output.txt");
  ofile << "Insects,Plants\n";
  for (iterNum = 0; iterNum < iterationCount; iterNum++)
  {
    printCompleteInfo(iterNum + 1);
    ofile << organismCount[1] << "," << organismCount[0] << '\n';
    auto InsectCopy = getInsects();
    for (int i = 0; i < InsectCopy.size(); i++)
    {
      auto currInsect = InsectCopy[i];
      currInsect->update_age(currInsect->get_age() + 1);
      currInsect->updateSexualUrge(currInsect->getSexualUrge() + increaseSexualUrge);
      int x = currInsect->get_x();
      int y = currInsect->get_y();
      auto moves = movesToLocationNew({x, y, 0}, currInsect->giveSpeed(), currInsect->get_vision_radius());
      int moveResult;
      for (int l = 0; l < moves.size(); l++)
      {
        auto nextObj = getObject(moves[l].x, moves[l].y);

        if (REPRODUCETYPE == Sexual && Organisms_in_love.find(currInsect) != Organisms_in_love.end())
        {
          Insect *interest = Organisms_in_love[currInsect];
          int x_interest = interest->get_x();
          int y_interest = interest->get_y();
          if (((abs(x - x_interest) == 1) && (abs(y - y_interest) == 0)) || ((abs(x - x_interest) == 0) && (abs(y - y_interest) == 1)))
          {
            Organisms_in_love.erase(interest);
            Organisms_in_love.erase(currInsect);
            Insect *baby = cupid.mating(currInsect, interest);
            if (baby)
            {
              addInsect(baby);
            }
          }
        }

        moveResult = updateUniverse(x, y, moves[l].x, moves[l].y, outfile);
        if (moveResult != SUCCESS)
          break;
        x = moves[l].x;
        y = moves[l].y;
      }
      simulationFile << iterNum + 1 << "," << currInsect->get_x() << "," << currInsect->get_y() << "," << currInsect->get_speciesID() << "," << currInsect->get_aadhar_number() << "," << MOVE << "\n";
      if (moveResult == DYING_ORGANISM)
      {
        killInsect(currInsect);
      }
      // Asexual Reproduction
      else
      {
        if (REPRODUCETYPE == Asexual && cupid.godSaidYes(currInsect))
        {
          vector<Insect *> daughters = cupid.split(currInsect);
          if (daughters.size() == 2)
          {
            addInsect(daughters[0]);
            addInsect(daughters[1]);
          }
        }
      }
    }
    std::random_shuffle(insects.begin(), insects.end());

    // Plant Spawning
    if (iterNum % plantSpawnInterval == 0)
    {
      reSpawnPlant();
    }
  }
  ofile.close();
  simulationFile.close();
}
