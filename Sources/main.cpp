#include "../headers/Universe.hpp"
#include <iostream>

using namespace namespace_Universe;
using namespace namespace_organism;
using namespace std;
int main() {
  srand(time(0));
  int iter = 30;
  std::cout << "Hello world!\n";
  int organismCount[2] = {0, 3};
  biodata_Plant variety_Plant[varieties_in_a_Species];
  biodata_Insect variety_Insect[varieties_in_a_Species];
  Universe myUni(10, organismCount, variety_Plant, variety_Insect);
  // Universe(int maxR, int *organismCount, biodata_Plant *plantVarieties,
  // biodata_Insect *insectVarieties); maxR specifies the maximum vision radius
  // organismCount -> Number of induviduals in each species ([0] for food
  // sources, [1] for first trophic level, [2] for second trophic level...(for
  // now just till first trophic level)) plantVarieties list of maxenergies of
  // the different plant sources, insectVarieties the three unique combinations
  // for {vision_radius, speed, and max_energy}
  // myUni.printMoves();
  std::cout << "\n\n\n";

  cout << "Insects are:\n\n";
  int n = myUni.getNumberOfInsects();
  cout << n << endl;

  for (int j = 0; j < iter; j++) // j is iteration number
  {
    auto InsectCopy = myUni.getInsects();
    for (int i = 0; i < InsectCopy.size(); i++) {
      auto temp = InsectCopy[i];
      int x = temp->get_x();
      int y = temp->get_y();
      cout << "x: " << x << " y: " << y << endl;
      // let newX,newY be obtained using scanNearestFoodSource

      auto moves = myUni.movesToLocationNew({x,y,0}, 7, temp->get_vision_radius());
      cout<<"Organism "<<i<<endl;
      
        for (int l = 0; l < moves.size(); l++) {
          auto tempPtr = myUni.getObject(moves[l].x,moves[l].y);
          if(tempPtr!=NULL)
          {
            if(((Organism*)tempPtr)->get_speciesID()==1) cout<<"Insect detected"<<endl;
            else if(((Organism*)tempPtr)->get_speciesID()==0)
            {
              myUni.updateUniverse(x, y, moves[l].x, moves[l].y);
            }
            break;
          }
          int status = myUni.updateUniverse(x, y, moves[l].x, moves[l].y);
          x = moves[l].x;
          y = moves[l].y;
          if(status!=0) break;
        } 
        cout<<"Organism energy is "<<temp->get_current_energy()<<endl;
    }
    // for (int i = 0; i < myUni.getNumberOfInsects(); i++) {
    //   auto [x, y] = myUni.getAnInsect(i);
    //   auto temp = (namespace_organism::Organism *)myUni.getObject(x, y);
    //   if (temp == NULL) {
    //     cout << "NULL ptr!" << endl;
    //     break;
    //   }
    //   cout << x << " " << y << " " << temp->get_vision_radius() << " "
    //        << temp->get_current_energy() << " " << temp->get_max_energy()
    //        << endl;

    //   auto speed = temp->get_speed_structure();
    //   cout << speed.len_of_speed_list << endl;
    //   /*
    //   for(int k=0;k<speed.len_of_speed_list;k++)
    //     {
    //       cout<<"k is "<<k<<endl;
    //       cout<<speed.speed_list[k]<<" ";
    //     }
    //   cout<<endl;*/
    //   //speedlist is null, have to give values
    // }
      cout << "end of iteration i = " << j << endl;
    }
  //myUni.run();
    return 0;
    
}
