#include "../includes/Organism.h"

using namespace namespace_organism;


Organism::Organism(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int aadhar_number, int speciesID)
{
	this->position = {x, y};
	this->vision_radius = vision_radius;
	this->organism_speed = {speed_list,
							length_of_speed_list,
							0};
	this->max_energy = max_energy;
	this->current_energy = current_energy;
	this->aadhar_number = aadhar_number;
	this->speciesID = speciesID; // Represent which species it belongs to (0-> plant, 1-> Insect for now)
	// update universe method

	printf("Organism %hu born with %d / %d energy at (%d,%d)", aadhar_number, current_energy, max_energy, (this->position).x, (this->position).y);
};

Organism::~Organism()
{
	// update universe method

	printf("Organism %hu died with %d / %d energy at (%d,%d)", aadhar_number, current_energy, max_energy, (this->position).x, (this->position).y);
}

Insect::Insect(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int aadhar_number, int organism_ID1, int speciesID) : Organism(x, y, vision_radius, speed_list, length_of_speed_list, max_energy, current_energy, aadhar_number, speciesID)
{
	this->organism_ID = organism_ID1;
};

Insect::~Insect()
{
	printf("Organism %hu, with ID %d died with %d / %d energy at (%d,%d)", get_aadhar_number(), organism_ID, get_current_energy(), get_max_energy(), get_x(), get_y());
}

int Insect::get_organism_ID()
{
	return organism_ID;
}

Plant::Plant(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int aadhar_number, int speciesID) : Organism(x, y, 0, NULL, 0, max_energy, 0, aadhar_number, speciesID){};

int Organism::get_speciesID()
{
	return this->speciesID;
}