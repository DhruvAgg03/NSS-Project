#include "../Headers/Aphrodite.h"
#define variation 0.1
#define variation2 0.2

#define minvision 3
#define maxvision 8
#define minspeed 1
#define maxspeed 5
#define minenergy 150
#define maxenergy 350

#define mutationprob 0.1

using namespace std;
extern std::ofstream outfile;

bool operator!=(coordinates2D a, coordinates2D b) 
{
  return a.x != b.x || a.y != b.y;
}

bool operator==(coordinates2D a, coordinates2D b) 
{
  return a.x == b.x && a.y == b.y;
}

bool Aphrodite::godSaidYes(Insect* insect)
{
    float pr = probFunc(insect->get_age(),insect->get_current_energy());
    float roll_die = (float)rand()/(float)RAND_MAX; 
    return (pr && roll_die<=pr && !universe->locked(insect->get_posn()));
    //return 1;
}

vector<Insect*> Aphrodite::split(Insect* insect)
{
    coordinates2D posn1 = insect->get_posn();
    vector<coordinates2D> adj_posns = universe->adjacent_posns(posn1);
    int len = adj_posns.size();
    if(len == 0)
        return {};
    outfile << "Insect " << insect->get_aadhar_number() <<" is splitting\n";
    coordinates2D posn2 = adj_posns[rand()%len];
    vector<Traits*> v = inheritedTraits(insect);
    Traits* t1 = v[0];
    Traits* t2 = v[1];
    unsigned short a1 = Organism::get_latest_organism_ID()+1;
    Insect* d1 = new Insect(posn1,*t1,a1,insectIndex,universe,MALE);
    unsigned short a2 = Organism::get_latest_organism_ID()+1;
    Insect* d2 = new Insect(posn2,*t2,a2,insectIndex,universe,MALE);
    universe->killInsect(insect);
    return {d1,d2};
}

// Basically this captures whether the organism is willing to split or not
float Aphrodite::probFunc(int age,int energy) // Parameters should be changed to macros
{
    float wt_age = 1.6;
    float wt_energy = 0.96;
    float p_age = wt_age/(iterationCount)*age;
    float p_energy = wt_energy/(maxEnergy)*energy;
    float min_p_age = 0.8;
    float normalize = wt_age*wt_energy;
    
    return (p_age*p_energy/normalize);
    
    //return (max(p_age,min_p_age)*p_energy/normalize);
    //(max(1.6/(iterationCount)*age,0.8)*0.96/(maxEnergy)*energy*(energy>25));
}


vector<Traits*> Aphrodite::inheritedTraits(Insect* insect) // Returns traits of daughters: vision, speed are mutated by 1 with less prob and energy is split with a slight varaiation
{
    auto t1 = new Traits;
    auto t2 = new Traits;

    int insEnergy = insect->get_current_energy();
    int insSpeed   = insect->get_traits().get_speed();
    int insVision  = insect->get_traits().get_visionradius();

    int loEnergy = insEnergy*0.5*(1-variation);
    int hiEnergy = insEnergy*0.5*(1+variation);

   
    int speed1 =  mutationsynthesizer(insSpeed,mutationprob);
    int speed2 =  mutationsynthesizer(insSpeed,mutationprob);
    int vision1 = mutationsynthesizer(insVision,mutationprob);
    int vision2 = mutationsynthesizer(insVision,mutationprob);
    int energy1 = loEnergy + rand()%(hiEnergy-loEnergy + 1);
   

    if(speed1<minspeed)speed1 = minspeed;
    else if(speed1>maxspeed)speed1 = maxspeed;
    if(speed2<minspeed)speed2 = minspeed;
    else if(speed2>maxspeed)speed2 = maxspeed;
    if(vision1<minvision)vision1 = minvision;
    else if(vision1>maxvision)vision1 = maxvision;
    if(vision2<minvision)vision2 = minvision;
    else if(vision2>maxvision)vision2 = maxvision;
    if(energy1<minenergy)energy1 = minenergy;
    else if(energy1>maxenergy)energy1 = maxenergy;
    int energy2 = insEnergy - energy1 ;

    t1->set_speed(speed1);
    t1->set_visionradius(vision1);
    t1->set_maxenergy(loEnergy + rand()%(hiEnergy-loEnergy + 1));

    t2->set_speed(speed2);
    t2->set_visionradius(vision2);
    t2->set_maxenergy(insect->get_current_energy() - t1->get_maxenergy() + 1);

    return {t1,t2};
}

Insect* Aphrodite::mating(Insect* insect1,Insect* insect2)
{
    coordinates2D posn1 = insect1->get_posn();
    coordinates2D posn2 = insect2->get_posn();
    vector<coordinates2D> adj_posns1 = universe->adjacent_posns(posn1);
    vector<coordinates2D> adj_posns2 = universe->adjacent_posns(posn2);
    vector<coordinates2D> adj_posns;
    for(auto posn:adj_posns1) if(posn!=posn1 && posn!=posn2)adj_posns.push_back(posn);
    for(auto posn:adj_posns2) if(posn!=posn1 && posn!=posn2)adj_posns.push_back(posn);
    int len = adj_posns.size();
    if(len == 0)
        return nullptr;
    outfile << "Insect " << insect1->get_aadhar_number() <<" and Insect " << insect2->get_aadhar_number() <<" are mating\n";
    coordinates2D posn = adj_posns[rand()%len];
    Traits v = inheritedTraits(insect1,insect2);
    unsigned short a = Organism::get_latest_organism_ID()+1;
    int g = rand()%2;
    Insect* offspring = new Insect(posn,v,a,insectIndex,universe,g);
    return offspring;
}

Traits Aphrodite::inheritedTraits(Insect* insect1,Insect* insect2)
{
    auto t = new Traits;
    int s1 = insect1->get_traits().get_speed();
    int s2 = insect2->get_traits().get_speed();
    int v1 = insect1->get_traits().get_visionradius();
    int v2 = insect2->get_traits().get_visionradius();
    int e1 = insect1->get_traits().get_maxenergy();
    int e2 = insect2->get_traits().get_maxenergy();

    //computes the average and rounds up/down if float with 50% probability
    int so = (s1+s2)/2 + (rand()%2)*((s1+s2)%2); 
    int vo = (v1+v2)/2 + (rand()%2)*((v1+v2)%2);
    int eo = (e1+e2)/2 + (rand()%2)*((e1+e2)%2);

    //To account for some mutation
    so=mutationsynthesizer(so,mutationprob);
    vo=mutationsynthesizer(vo,mutationprob);
    eo=mutationsynthesizer(eo,mutationprob);

    //To ensure that the traits are within the limits
    if(so<minspeed)so = minspeed;
    else if(so>maxspeed)so = maxspeed;
    if(vo<minvision)vo = minvision;
    else if(vo>maxvision)vo = maxvision;
    if(eo<minenergy)eo = minenergy;
    else if(eo>maxenergy)eo = maxenergy; 

    //Assigning the traits to the offspring
    t->set_speed(so);
    t->set_visionradius(vo);
    t->set_maxenergy(eo);
    return *t;
}

int Aphrodite::mutationsynthesizer(int trait, int prob) //returns -1,0 or 1 depending on mutationprob, high prob of returning 0
{
    float roll_die = (float)rand()/RAND_MAX;
    if(roll_die<prob) return trait-1;
    else if(roll_die>1-prob) return trait+1;
    else return trait;
}


