
#include "../Headers/Organism.h"
#include "../Headers/Universe.h"
using namespace namespace_Universe;
using namespace namespace_organism;
void Universe::run() {

  for(int j=0;j<iterationCount;j++)
  {
    auto InsectCopy = getInsects();
    printCompleteInfo(j+1);

    for(int i=0;i<InsectCopy.size();i++)
    {
      auto currInsect = InsectCopy[i];
      int x = currInsect->get_x();
      int y = currInsect->get_y();
      auto moves = movesToLocationNew({x,y,0},currInsect->giveSpeed(),currInsect->get_vision_radius());

      for(int l=0;l<moves.size();l++)
      {
        auto nextObj = getObject(moves[l].x,moves[l].y);
        if(nextObj!=NULL)
        {
          if(((Organism*)nextObj)->get_speciesID()==1) cout<<"Insect Detected"<<endl;
          else if(((Organism*)nextObj)->get_speciesID()==0) updateUniverse(x,y,moves[l].x,moves[l].y);

          break;
        }
        if(updateUniverse(x,y,moves[l].x,moves[l].y)!=0) break;
        x = moves[l].x;
        y = moves[l].y;
      }
    }
    random_shuffle(insects.begin(),insects.end());
  }
}