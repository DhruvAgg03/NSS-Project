# PC03-NSS

MOM google DOC : https://docs.google.com/document/d/1egNHOzUpCYlN0ukZGkxLbDn76kEuCFiMl2wOHI8L3Ss/edit

July 9th, 2022
Agenda-
0) classify the work into different subsystems (as of now, vision, motion, and everything else….)
1) determining the roles each member will perform.
2) finalize (or reach a certain conclusion) on the method we approach for each subsystem
3) start coding

Subsystems -
	Universe creation (matrix) -
	Random generation of matrix
	Matrix -> (suggested making the matrix big enough to facilitate continuous motion)
	Max size -> 10000x10000 (20k by 20k)(just for the pointers).
	Cell are -> pointers. 
	Static - Vision array
	Getters - for element(pointers) in each cell 
	Update Universe (method)   

Objects -
food sources,  organisms, (later predator mayb)
	Food source - Iterate it over, (treat it as prey predator)

Organisms - 
	Natural traits - speed, max energy, vision radius 
	Characteristics - (all variables private)
	name(species and variant, and individual),  
	[x,y](position),(getters & setters)
	previous_position
	max_energy 
	present_energy 
	vision radius (Classes - species, subclass -> variants(doubtful since we need continuous variation), subclass further-> individual).
	steps_per_iteration(List of speeds) (next step being weighted average) (Max_Speed Average_speed)()
	Vision -
	Jagged circle
	Vision array, test  
	Food Source
	Execution_of_motion - 
	Allowed directions - 4 cardinal directions, 4 diagonal
	Path finding algorithms (many steps)
	Killing an organism -
	Method -> for killing, ‘die’    
Role bifurcation -
	Organism_Creation - Sumanth, Dhanush, Kumaresan, HHN
	Universe_Creation - Dhruv, DharEcoEnvi