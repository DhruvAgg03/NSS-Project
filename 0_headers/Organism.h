#pragma once

#include <stdio.h>
namespace namespace_organism
{
	struct cordinates2D
	{
		int x;
		int y;
	};

	struct speed_structure
	{
		int *speed_list;
		// list of numbers which on averaging gives speed.
		// Example : [1,1,2,3] => avg speed would be 1.75
		// we can choose how many steps to move per iteration using random or RR
		int len_of_speed_list;
		int rr_count;
		// round robin count in case we use it
		// rr_count needs to be lower than len_of_speed_list always
	};

	class Organism
	{

	private:
		// add reference to unvierse
		struct cordinates2D position;
		struct speed_structure organism_speed;

		int vision_radius;
		int max_energy;
		int current_energy;
		unsigned short int name_of_individual; // name of organism like John Doe

	public:
		Organism(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int name_of_individual);
		~Organism();
		int get_x();								   // kumeresan
		int get_y();								   // kumeresan
		int get_vision_radius();					   // kumeresan
		struct speed_structure &get_speed_structure(); // kumeresan
		int get_max_energy();						   // kumeresan
		int get_current_energy();					   // kumeresan
		unsigned short int get_name_of_individual();   // kumeresan
	};
}
