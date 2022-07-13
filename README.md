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
