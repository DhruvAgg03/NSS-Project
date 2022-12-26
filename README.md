
# PC03-NSS

## MOM google DOC
https://docs.google.com/document/d/1egNHOzUpCYlN0ukZGkxLbDn76kEuCFiMl2wOHI8L3Ss/edit

## Future Enhancements
1) In the initial construction of the universe, maybe a randomiser can be used to determine the traits of the organism, that way every time we create an instance, it should allow for a more diverse gene pool.
2) Maybe create water sources, thirst factor.
3) Predators.
4) Add prev_position (memory of organism)
5) Consider having an heap for organisms, plants, predators => and just do look ups on them (kind of like a database)
		
## Current Codeflow:
### HHN
Pushing new functions->oracle,die_roll, move it to a new class-> asexual reproduce (resolve universe organism dependencies)
### Dhruv 
**(Code Maintenance and Simulation)** Output change from cout to an universe log file, group functions in Universe class, Respawning plants , New data -> No. of Organisms vs Time, List of organisms with their corresponding bio_data  (trail_2.csv), remove typedef for structs, make bio_data as `class Traits`
### Kums,Kalva 
`class Sexual_Reproduction`, maybe derive sex and asex from a generic class? Alter path_finding algo, formulate function for reproductive figure ->function of biodata -> used in tie-break resolution.



