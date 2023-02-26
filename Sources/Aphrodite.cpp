#include "../Headers/Aphrodite.h"
#define variation 0.1

using namespace std;
extern std::ofstream outfile;

bool Aphrodite::godSaidYes(Insect* insect)
{
    float pr = probFunc(insect->get_age(),insect->get_current_energy());
    float roll_die = (float)rand()/(float)RAND_MAX; 
    return (pr && roll_die>pr && !universe->locked(insect->get_posn()));
    // return 1;
}

vector<Insect*> Aphrodite::split(Insect* insect)
{
    outfile << "Insect " << insect->get_aadhar_number() <<" is splitting\n";
    coordinates2D posn1 = insect->get_posn();
    vector<coordinates2D> adj_posns = universe->adjacent_posns(posn1);
    int len = adj_posns.size();
    if(len == 0)
        return {};
    coordinates2D posn2 = adj_posns[rand()%len];
    vector<Traits*> v = inheritedTraits(insect);
    Traits* t1 = v[0];
    Traits* t2 = v[1];
    unsigned short a1 = Organism::get_latest_organism_ID()+1;
    Insect* d1 = new Insect(posn1,*t1,a1,insectIndex,universe);
    unsigned short a2 = Organism::get_latest_organism_ID()+1;
    Insect* d2 = new Insect(posn2,*t2,a2,insectIndex,universe);
    universe->killInsect(insect);
    return {d1,d2};
}

float Aphrodite::probFunc(int age,int energy) //Amenable to modification
{
    return (max(1.6/(iterationCount)*age,0.8)*0.96/(maxEnergy)*energy*(energy>100));
}

vector<Traits*> Aphrodite::inheritedTraits(Insect* insect)
{
    auto t1 = new Traits;
    auto t2 = new Traits;

    int loSPeed = insect->get_traits().get_speed()*(1-variation);
    int hiSpeed = insect->get_traits().get_speed()*(1+variation);

    int loVision = insect->get_traits().get_visionradius()*(1-variation);
    int hiVision = insect->get_traits().get_visionradius()*(1+variation);

    int loEnergy = insect->get_current_energy()*0.5*(1-variation);
    int hiEnergy = insect->get_current_energy()*0.5*(1+variation);

    if(hiSpeed-loSPeed == 0)
     hiSpeed++;
    
    t1->set_speed(loSPeed + rand()%(hiSpeed-loSPeed));
    t1->set_visionradius(loVision + rand()%(hiVision-loVision + 1));
    t1->set_maxenergy(loEnergy + rand()%(hiEnergy-loEnergy + 1));

    t2->set_speed(loSPeed + rand()%(hiSpeed-loSPeed));
    t2->set_visionradius(loVision + rand()%(hiVision-loVision + 1));
    t2->set_maxenergy(insect->get_current_energy() - t1->get_maxenergy() + 1);

    return {t1,t2};
}


bool Aphrodite::willReproduce(Insect* I1,Insect* I2)
{
    //Assuming both insects are of different gender
    int dist = 0;
    dist+=std::abs((I1->position).x - (I2->position).x);
    dist++std::abs((I2->position).y - (I2->position).y);
    float r1 = ((float)(I1->currentEnergy))/(I1->maxEnergy);
    float r2 = ((float)(I2->currentEnergy))/(I2->maxEnergy);
    float sexProduct = (I1->sexualUrge)*(I2->sexualUrge);
    float NotNormalised = (sexProduct*r1*r2)/dist;
    float probab = NotNormalise/40000;
    return probab > (rand()%1);
}
