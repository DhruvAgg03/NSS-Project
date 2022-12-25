
# PC03-NSS

## MOM google DOC
https://docs.google.com/document/d/1egNHOzUpCYlN0ukZGkxLbDn76kEuCFiMl2wOHI8L3Ss/edit

## Future Enhancements
1) In the initial construction of the unvirse, maybe a randomiser can be used to determine the traits of the organism, that way every time we create an instance, it should allow for a more diverse gene pool.
2) Maybe create water sources, thirst factor.
3) Predators.
4) Add prev_position
5) Improvising pathfinding:
	All organisms can't move simultaneously, they have to move independently of each other.

	1) Each organism will have pointer to the Universe class
	2) dhruv's array will the parmater of universe class (get it from a getter)
	3) iterate through elements and check if there is a food particle, for now we will try to move towards it
	4) randomly choose the number of steps
	5) How do we choose what our final position will be?
		- Do we just jump to final position (most promising)
		- Do we go one step at a time => in that case what if we have another organism in out path
		- Consider having an heap for organisms, plants, predators => and just do look ups on them (kind of like a database)
		
## Current Codeflow:
### HHN
Pushing new functions->oracle,die_roll, move it to a new class-> asexual reproduce (resolve universe organism dependencies)
### Dhruv 
**(Code Maintenance and Simulation)** Output change from cout to an universe log file, group functions in Universe class, Respawning plants , New data -> No. of Organisms vs Time, List of organisms with their corresponding bio_data  (trail_2.csv)
### Kums,Kalva 
`class Sexual_Reproduction`, maybe derive sex and asex from a generic class? Alter path_finding algo, formulate function for reproductive figure ->function of biodata -> used in tie-break resolution.



