#include "../0_headers/Organism.h"

using namespace namespace_organism;

Organism::Organism(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int name_of_individual)
{
	this->position = {x, y};
	this->vision_radius = vision_radius;
	this->organism_speed = {speed_list,
							length_of_speed_list,
							0};
	this->max_energy = max_energy;
	this->current_energy = current_energy;
	this->name_of_individual = name_of_individual;

	// update universe method

	printf("Organism %hu born with %d / %d energy at (%d,%d)", name_of_individual, current_energy, max_energy, (this->position).x, (this->position).y);
};

Organism::~Organism()
{
	// update universe method

	printf("Organism %hu died with %d / %d energy at (%d,%d)", name_of_individual, current_energy, max_energy, (this->position).x, (this->position).y);
}

Insect::Insect(int x,int y,int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int name_of_individual,int organism_ID1): Organism(x,y,vision_radius,speed_list,length_of_speed_list,max_energy,current_energy,name_of_individual)
{
	this->organism_ID = organism_ID1;
};

Insect::~Insect()
{
	printf("Organism %hu, with ID %d died with %d / %d energy at (%d,%d)", get_name_of_individual(), organism_ID, get_current_energy(), get_max_energy(), get_x(), get_y());
}

int Insect:: get_organism_ID()
{
	return organism_ID;
}

Plant::Plant(int x,int y,int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int name_of_individual): Organism(x,y,0,NULL,0,max_energy,0,name_of_individual)
{};

