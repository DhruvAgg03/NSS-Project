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
