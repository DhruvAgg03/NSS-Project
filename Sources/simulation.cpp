
#include "../headers/Universe.hpp"
#include "../0_headers/Organism.h"
using namespace namespace_Universe;
using namespace namespace_organism;
void Universe::run()
{

    for (int i = 0; i < InsectPosition.size(); i++)
    {
        Insect *insect = (Insect *)environment[get<0>(InsectPosition[i])][get<1>(InsectPosition[i])];

        step initial_posn = {get<0>(InsectPosition[i]), get<1>(InsectPosition[i]), 0};
        #warning "steps are always constant"
        vector<step> path = movesToLocation(initial_posn, 2, insect->get_vision_radius());
        
    }
}