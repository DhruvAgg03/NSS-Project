// classes
// What are attributes for organism

// can create information in the universe as organism 
//how would we specify each 

void Universe::initializeEnvironmentWithMultipleSpecies(std::vector<int> Organism_number_data, )

// Creation of classes
// Parameters for constructing an organism
// id number (unique for any living induvidual independent of the type of species)
// type (-1 -> null, 0-> food source, 1-> prey, 2-> predator) (but the info will only have types from 0 to how many ever)
// visibility (units of sight (0 for food source and rest all can vary))
// speed (0 for food source and rest all can vary)


// want to rename classes as organisms (or induviduals)
typedef struct Organism_bio_data{
    long int id; // can be just the index in the class Info_Organism
    int type;
    int visibility;
    float speed;
}Organism_bio_data;
// a data structure that holds the necessary information to instantiate an organism object

void classes_creation(std::vector<Organism_bio_data> Info_Organism, std::vector<organism> &Objects_of_class){
    for(int i = 0; i < Info_Organism.size(); i++){
        Objects_of_class.pushback(organism(Info_Organism[i].id, Info_Organism[i].type, Info_Organism[i].visibility, Info_Organism[i].speed))
    }
}
// a function that creates the list of all the organism objects to later create pointers

void initialiseEnvironment_2(std::vector<organism> Objects_of_class, organism*[N][N] &environment){
    // creation of a random list of coordinates -> Dhruv's Code
    // dont have time to code what i have in mind :(( 
    // after say the list of random tuples are generated in TempPoints()
    // we run over the first Info_Organism.size() elenmenst and instantiate make them point to 
    for(int i = 0; i<N*N; i++){
        if(i<Objects_of_class.size()){
            *environment[TempPoints[i][0]][TempPoints[i][1]] = Objects_of_class[i]
        }else{
            *environment[TempPoints[i][0]][TempPoints[i][1]] = organism(i, -1, 0, 0);
        }
    }
}

// Propositions -> Initial ENergy as a trait
// for organism team -> energy can be a trait that is transfeered from eaten organism to the consumer

