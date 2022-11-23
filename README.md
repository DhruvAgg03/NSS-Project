
# PC03-NSS

Few Ideas
1) In the constructor of each object maybe a randomiser can be used to determine the traits of the organism, that way every time we create an instance, it should allow for a more diverse gene pool (but maybe later) 


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
=======
# PC03-Natural Selection Simulation

## Subsystems

+ **Universe Creation (Matrix):**
    1. Random generation of matrix
    1. Matrix -> (suggested making the matrix big enough to facilitate continuous motion)
        * **Max size** -> 10000x10000 (20k x 20k)(just for the pointers)
        * **Cell** -> are pointers
        * **Static** -> Vision array
    1. Getters - for element (pointers) in each cell 
    1. Update Universe (method) 

+ **Objects:**
    1. Food sources,  Organisms, (later predator mayb)
    1. Food source - Iterate it over, (treat it as prey predator)
    
+ **Organisms:**
    1. Natural traits - speed, max energy, vision radius 
    1. Characteristics - (all variables private)
    name(species and variant, and individual),  
        * `[x,y]` (position), (getters & setters)
        * `previous_position`
        * `max_energy` 
        * `present_energy` 
        * `vision_radius` (Classes -> species; Subclass -> variants(doubtful since we need                  continuous variation); Subclass further -> individual)
        * `steps_per_iteration` (List of speeds)
        * `max_speed, average_speed` (next step being weighted average) 
    1. Vision -
        * Jagged circle
        * Vision array, test  
        * Food Source
    1. Execution of motion - 
        * Allowed directions - 4 cardinal directions, 4 diagonal
        * Path finding algorithms (many steps)
    1. Killing an organism -
        * Method for killing -> `die`    
## Roles

+ Organism: Sumu, HHN, Dhanush, Kumaresan 
+ Universe: Dhruv, Dharani

# Winter Break

+ **AlgoPhase** - (Dhruv, Kumaresan, Kalva and HHN)
	+ Immediate Timeline (next 1 week)(-HHN) - 
		Data Generation - Compile Code and get output (Kalva, Dhruv, Kumaresan)

	Short Extended Timeline - (Next 3 Weeks)(Mid December)(-HHN) -
	+ Tasks - 
		Optimize the Present ….
		Ideate the Next Model - 
	+ Priority - 
		Inheritance (Sexual Reproduction, Asexual Easier before to Implement)
		Trophic Levels (Producer, Prey, Predator)	

	End of December -
		Continuity of the Positions -> (Risky)... (Tradeoff with Visualisation)...,
		Continuity of traits 
		Additional Traits - (Thirst, Size, Tradeoffs Between the Traits)

+ **VisPhase(Visualisation Phase)** - (Dharani)
	+ Jan First Week - 
		Data Output - 
		100 Simulations
	+ Visualisation - Matrix Representation of Environment (Selective Visualisation)
	+ Time Series Data - Overall Population, Breakdown Based on Variants (Later on Continuous Histogram, and Ditribution) 

Plot Generation - (Python)
Time Series Data 
Cross Sectional Data (through time)

Animation - (Unity), (Avatar Creation), (Movement)

add prev_position
pathfinding

All organisms can't move simoltaneosly, they have to move independently of each other.

1) Each organism will have pointer to the Universe class
2) dhruv's array will the parmater of universe class (get it from a getter)
3) iterate through elements and check if there is a food particle, for now we will try to move towards it
4) randomly choose the number of steps
5) How do we choose what our final position will be?
	- Do we just jump to final position (most promising)
	- Do we go one step at a time => in that case what if we have another organism in out path
	- Consider having an heap for organisms, plants, predators => and just do look ups on them (kind of like a database)

	// try db with 10 M rows and look up speed

	// try db with 10 M rows and look up speed


