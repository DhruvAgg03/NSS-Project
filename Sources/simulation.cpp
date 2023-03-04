#include "../Headers/Organism.h"
#include "../Headers/Universe.h"
#include "../Headers/Aphrodite.h"

//Actions in output file
#define MOVE 0
#define BIRTH 1
#define DEATH 2
extern std::ofstream outfile;

void Universe::run()
{
  cout<<"Pc Ic\n";
  Aphrodite cupid{this};
  ofstream ofile;
  ofile.open("./Output/Output.txt");
  ofstream myfile;
  myfile.open("Data/trail_2.csv", ios::trunc);
  myfile<<"Iter_no,x,y,Spec_ID,Adhaar_number,action\n";
  ofile << "Insects,Plants\n";
  for (int j = 0; j < iterationCount; j++)
  {
    printCompleteInfo(j + 1);
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

        //outfile << "Insect Detected" << endl;
        if (updateUniverse(x, y, moves[l].x, moves[l].y, outfile) != SUCCESS)
          break;
        // }
        x = moves[l].x;
        y = moves[l].y;
      }
      myfile<<j<<","<<currInsect->get_x()<<","<<currInsect->get_y()<<","<<currInsect->get_speciesID()<<","<<currInsect->get_aadhar_number()<<","<<MOVE<<"\n";
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
        int tempX = currInsect->get_x();
        int tempY = currInsect->get_y();
        int tempSpeciesID = currInsect->get_speciesID();
        int tempAdhaar = currInsect->get_aadhar_number();
      // HHN's Code:
        vector<Insect *> daughters = cupid.split(currInsect);
        if (daughters.size() == 2)
        {
          myfile<<j<<","<<tempX<<","<<tempY<<","<<tempSpeciesID<<","<<tempAdhaar<<","<<DEATH<<"\n";
          myfile<<j<<","<<daughters[0]->get_x()<<","<<daughters[0]->get_y()<<","<<daughters[0]->get_speciesID()<<","<<daughters[0]->get_aadhar_number()<<","<<BIRTH<<"\n";
          myfile<<j<<","<<daughters[1]->get_x()<<","<<daughters[1]->get_y()<<","<<daughters[1]->get_speciesID()<<","<<daughters[1]->get_aadhar_number()<<","<<BIRTH<<"\n";
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
  myfile.close();
}
