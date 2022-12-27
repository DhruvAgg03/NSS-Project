#include "../Headers/Universe.h"
using namespace std;

pair<power, power> Organism::getChildEnergy()
{
	power parent_energy = this->get_current_energy();
	return {parent_energy / 2, parent_energy / 2};
}

double Organism::reproduce_roll_ceil()
{
	return 0.5;
	// can tweak the ceil based on number of iterations and energy
}

pair<bool, coordinates2D> Organism::reproduce_oracle(vector<coordinates2D> &poss_posns)
{
	// adjacent positions which are in bounds and empty
	coordinates2D child_position;
	if (poss_posns.size() == 0)
		return {false, child_position};
	random_shuffle(poss_posns.begin(), poss_posns.end());
	child_position = poss_posns[0];
	srand(time(NULL));
	double roll = rand();
	roll = roll / RAND_MAX;
	double roll_ceil = reproduce_roll_ceil();
	// higher roll_ceil -> higher probabiltiy of binary fission
	if (roll < roll_ceil)
		return {true, child_position};
	return {false, child_position};
}

Organism::Organism(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int aadhar_number, int speciesID)
{
	this->position = {x, y};
	this->vision_radius = vision_radius;
	this->organism_speed = {speed_list, length_of_speed_list, 0};
	this->max_energy = max_energy;
	this->current_energy = current_energy;
	this->aadhar_number = aadhar_number;
	this->speciesID = speciesID; // Represent which species it belongs to (0-> plant, 1-> Insect for now)
	// update universe method
	ofstream outfile;
	outfile.open("./Output/universelog.txt", ios::app);
	outfile<<"Organism "<<aadhar_number <<" born with "<< current_energy<< '/'<< max_energy<< " energy at ("<< (this->position).x <<','<<(this->position).y<<")\n";
	outfile.close();
};

Organism::~Organism()
{
	ofstream outfile;
	outfile.open("./Output/universelog.txt", ios::app);
	outfile<<"Organism "<< aadhar_number<<" died with "<< current_energy<< '/'<< max_energy<< " energy at ("<< (this->position).x <<','<<(this->position).y<<")\n";
	outfile.close();
}

void Organism::addEnergy(int energy)
{
	if (energy > 0)
		current_energy = current_energy + energy > max_energy ? max_energy : current_energy + energy;
	else
		current_energy = current_energy + energy > 0 ? current_energy + energy : 0;
}

void Organism::update(int newX, int newY)
{
	int energyChange = 0;
	energyChange -= newX > position.x ? newX - position.x : position.x - newX;
	energyChange -= newY > position.y ? newY - position.y : position.y - newY;
	addEnergy(energyChange * movementCost);
	changeX(newX);
	changeY(newY);
}

Insect::Insect(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int aadhar_number, int organism_ID1, int speciesID) : Organism(x, y, vision_radius, speed_list, length_of_speed_list, max_energy, current_energy, aadhar_number, speciesID)
{
	this->organism_ID = organism_ID1;
};

Insect::~Insect()
{
	ofstream outfile;
	outfile.open("./Output/universelog.txt", ios::app);
	outfile<<"Organism "<<get_aadhar_number()<<" with ID "<< organism_ID<<" died with " <<get_current_energy()<<'/'<<get_max_energy()<<" energy at ("<<get_x()<<','<<get_y()<< ")\n";
	outfile.close();
}

int Insect::get_organism_ID()
{
	return organism_ID;
}

Plant::Plant(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int aadhar_number, int speciesID) : Organism(x, y, 0, NULL, 0, max_energy, current_energy, aadhar_number, speciesID){};
