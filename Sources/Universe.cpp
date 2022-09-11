
#include "../headers/Universe.hpp"
#include "../0_headers/Organism.h"

#define __PLANT_VARIETY    \
    {                      \
        {10}, {20}, { 30 } \
    }

#define __INSECT_VARIETY                           \
    {                                              \
        {10, 3, 300}, {20, 2, 200}, { 30, 1, 100 } \
    }
using namespace namespace_Universe;

bool compare(const step &a, const step &b)
{
    return a.dist < b.dist;
}
// Compare function used for sorting moves vector comparing two structs

int random_range(int min, int max)
{
    int in_range = rand();
    in_range = min + in_range % (max - min);
    return in_range;
}
// Generates a random number between given range [min, max)

Universe::Universe(int maxR, int *organismCount,
                   biodata_Plant variety_Plant[varieties_in_a_Species],
                   biodata_Insect variety_Insect[varieties_in_a_Species])
{
    maxR = 5;
    biodata_Plant vp[varieties_in_a_Species] = __PLANT_VARIETY;
    biodata_Insect vi[varieties_in_a_Species] = __INSECT_VARIETY;
    for (int i = 0; i < varieties_in_a_Species; i++)
    {
        variety_Plant[i] = vp[i];
        variety_Insect[i] = vi[i];

        // temp array holding the variety of plants because we are too lazy to change everything
    }

    this->createMovesVector(maxR);
    // Creates the VisionArray
    this->initializeVarieties(variety_Plant, variety_Insect);
    this->initializeEnvironment(organismCount, N);
}
// Constructor -
// Input maximum Radius and Number of Organisms per species
// function calls onto create movesVector (Cater to maximum radius and speed) and initialise Environment (Can we rename it VisionArray ??)

void Universe::createMovesVector(int maxR)
{
    float temp = maxR * maxR;
    for (int x = -maxR; x <= maxR; x++)
    {
        for (int y = -maxR; y <= maxR; y++)
        {
            if (x * x + y * y <= temp)
            {
                struct step tempstep;
                tempstep.x = x;
                tempstep.y = y;
                tempstep.dist = sqrt(x * x + y * y);
                (this->moves).push_back(tempstep);
            }
        }
    }
    sort(moves.begin(), moves.end(), compare);
    moves.erase(moves.begin()); // removes (0,0,0) from the vector

    std::cout << "Constructed!!\n";
}

void Universe::initializeVarieties(biodata_Plant *plantVarieties, biodata_Insect *insectVarieties)
{
    for (int i = 0; i < varieties_in_a_Species; i++)
    {
        this->variety_Plant[i] = plantVarieties[i];
        this->variety_Insect[i] = insectVarieties[i];
    }
    // The memory address initially stored in the pointers
    // are the same the vakues it points are different
}

void Universe::initializeEnvironment(int *organismCount, int len)
{
    // Generating an array of all the coordinates
    std::vector<std::tuple<int, int>> tempPoints; // temporary Points
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            tempPoints.push_back(std::make_tuple(i, j));
    std::random_shuffle(tempPoints.begin(), tempPoints.end());

    // Assigning the elements of environment to the necessary instances
    int counter = 0; // Running over the temporary array
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < organismCount[i]; j++)
        {
            if (i == 0)
            {
                int variety = random_range(0, varieties_in_a_Species); // I am calling it seperately so that later on can bring in variation in the food source amount
                namespace_organism::Plant temp(std::get<0>(tempPoints[counter]),
                                               std::get<1>(tempPoints[counter]), 0, NULL, 0,
                                               variety_Plant[variety].max_energy,
                                               variety_Plant[variety].max_energy, counter, 0);
                environment[std::get<0>(tempPoints[counter])][std::get<1>(tempPoints[counter])] = &temp;
            }
            else if (i == 1)
            {
                int variety = random_range(0, varieties_in_a_Species);
                namespace_organism::Insect temp(std::get<0>(tempPoints[counter]), std::get<1>(tempPoints[counter]), variety_Insect[variety].vision_radius, NULL, variety_Insect[variety].speed, variety_Insect[variety].max_energy, variety_Insect[variety].max_energy, counter, counter, 1);
                environment[std::get<0>(tempPoints[counter])][std::get<1>(tempPoints[counter])] = &temp;
                InsectPosition.push_back(std::make_tuple(std::get<0>(tempPoints[counter]), std::get<1>(tempPoints[counter])));
            }
            counter++;
        }
    }
    for (int i = counter; i < dimension * dimension; i++)
    {
        environment[std::get<0>(tempPoints[counter])][std::get<1>(tempPoints[counter])] = NULL;
    }
}
// input number of organism (Say the we specify each organism is a list, first element being number of food sources, next being number of prey and so on)
// creating all the coordinates for the matrix using TempPoints (call it temporary Coordinates (TempCoord) ?)
// Creating the functions that assigns the necessary pointers to class based on data we know

std::vector<struct step> Universe::getMoves()
{
    return this->moves;
}

void Universe::printMoves()
{
    int i; // Counter
    for (i = 0; i < (this->moves).size(); i++)
        std::cout << "(" << (this->moves)[i].dist << "," << (this->moves[i]).x << "," << (this->moves)[i].y << ") " << endl;
    std::cout << "\n i is " << i << "\n";
    return;
}

void Universe::updateUniverse(int initX, int initY, int finalX, int finalY)
{
    void *movingObj = environment[initX][initY];
    environment[finalX][finalY] = movingObj;
    environment[initX][initY] = NULL;
}

void *Universe::getObject(int posX, int posY)
{
    void *reqPoint = environment[posX][posY];
    return reqPoint;
}

int Universe::getNumberOfInsects()
{
    return InsectPosition.size();
}

std::tuple<int, int> Universe::getAnInsect(int i)
{
    std::tuple<int, int> temp = InsectPosition[i];
    return temp;
}

void Universe::deathOfInsect(int i, int &counter)
{
    for (int j = i; j < (InsectPosition.size() - 1); j++)
    {
        InsectPosition[j] = InsectPosition[j + 1];
    }
    InsectPosition.pop_back();
    counter--;
}

void Universe::creatingAndUpdatingDisplayEnvironmentHistory()
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            if (environment[i][j] == NULL)
            {
                displayEnvironment[dimension * i + j] = -1; // Empty
            }
            else
            {
                int temp_speciesID = ((namespace_organism::Plant *)environment[i][j])->get_speciesID();
                switch (temp_speciesID)
                {
                case 0: // Plant
                    displayEnvironment[dimension * i + j] = 0;
                    break;
                case 1: // Insect
                    displayEnvironment[dimension * i + j] = 1;
                    break;
                default:
                    break;
                }
            }
        }
    }
    printf("displayEnvironment created\n");
    // historyEnvironment.push_back(displayEnvironment);
    printf("historyEnvironment updated\n");
}

void Universe::writingToFile()
{
    FILE *fptr;
    fptr = fopen("Data.txt", "w");
    if (fptr == NULL)
    {
        printf("Error !!");
    }
    else
    {
        for (int j = 0; j < historyEnvironment.size(); j++)
        {
            for (int i = 0; i < dimension * dimension; i++)
            {
                fprintf(fptr, "%d,", historyEnvironment[j][i]);
            }
            fprintf(fptr, "\n");
        }
        fclose(fptr);
    }
}


step Universe::scanNearestFoodSource(step current_position, int vision_radius)
{
    std::vector<struct step> moves_array = getMoves();
    int nearest_dist_index = -1;

    for(int i=0;i<moves_array.size();i++)
    {
        if(vision_radius < moves_array[i].dist)
        {
            struct step temp;
            temp.x = -1; temp.y = -1; temp.dist = -1;
            return temp;
        }

        int x = current_position.x + moves_array[i].x;
        int y = current_position.y + moves_array[i].y;
        if(x>=dimension || x < 0 || y>=dimension || y<0)
            continue;
        //What are we placing for plant and insect? 1 for plant?
        namespace_organism::Plant *p;
        if(environment[x][y] == p)
        {
            nearest_dist_index = i;
            break;
        }
    }

    float nearest_dist = moves_array[nearest_dist_index].dist;
    while(nearest_dist_index>0 && nearest_dist == moves_array[nearest_dist_index].dist)
        nearest_dist_index--;
    
    vector<step> possible_destinations;
    while(moves_array[nearest_dist_index].dist == nearest_dist)
    {
        int x = current_position.x + moves_array[nearest_dist_index].x;
        int y = current_position.y + moves_array[nearest_dist_index].y;

        if(x>=dimension || x < 0 || y>=dimension || y<0)
        {
            nearest_dist_index++;
            continue;
        }

        //What are we placing for plant and insect? 1 for plant?
        namespace_organism::Plant *p;
        if(environment[x][y] == p)
        {
            struct step s;
            s.x = x;
            s.y = y;
            s.dist = sqrt(x*x + y*y);
            possible_destinations.push_back(s);
        }
        nearest_dist_index++;
    }

    int random_index = rand()%(possible_destinations.size());
    return possible_destinations[random_index];
}

vector<step> Universe::movesToLocation(step current_position, int number_of_steps,int vision_radius)
{
    vector<step> next_moves;
    int x = current_position.x;
    int y = current_position.y;

    namespace_organism::Insect *insect;
    if( (x+1 >=dimension || environment[x+1][y]== insect) && (x-1 < 0 || environment[x-1][y]!=insect) && (y+1 >=dimension || environment[x][y+1]!=insect) && (y-1<0 || environment[x][y-1]!=insect))
        return next_moves;
    
    next_moves.push_back(current_position);

    for(int i=0;i<number_of_steps;i++)
    {
        step curr = next_moves[i];
        int x = curr.x;
        int y = curr.y;
        step nearest_food = scanNearestFoodSource(curr,vision_radius);
        if(nearest_food.x < 0)
        {
            int flag = 1;
            while(flag==1)
            {
                int x_disp = rand()%2;
                if(x_disp == 0) x_disp--;
                int y_disp = rand()%2;
                if(y_disp == 0) y_disp--;

                if(x+x_disp>=0 && x+x_disp<dimension && y+y_disp>=0 && y+y_disp<dimension && environment[x+x_disp][y+y_disp]==NULL)
                {
                    flag = 0;
                    step next;
                    next.x = x+x_disp;
                    next.y = y+y_disp;
                    next.dist = sqrt(next.x*next.x + next.y*next.y);
                    next_moves.push_back(next);
                }
            }
        }
        else
        {
            int x_disp = nearest_food.x - x;
            int y_disp = nearest_food.y - y;
            if((abs(x_disp)==0 && abs(y_disp)==1) || (abs(x_disp)==1 && abs(y_disp)==0))
            {
                step next;
                next.x = x+x_disp;
                next.y = y+y_disp;
                next.dist = sqrt(next.x*next.x + next.y*next.y);
                next_moves.push_back(next);
                next_moves.erase(next_moves.begin());
                return next_moves;
            }
        
            //aosihniosbaifubiuabw
            namespace_organism::Insect *ins;
            int x1,y1;
            if(x_disp==0)
            {
                y1 = y_disp/abs(y_disp);
                if(y+y1>=dimension ||y+y1<0 || environment[x][y+y1]!=NULL)
                {
                    next_moves.erase(next_moves.begin());
                    return next_moves;
                }
                else
                {
                    step next;
                    next.x = x+x_disp;
                    next.y = y+y_disp;
                    next.dist = sqrt(next.x*next.x + next.y*next.y);
                    next_moves.push_back(next);
                    continue;
                }
            }
            if(y_disp==0)
            {
                x1 = x_disp/abs(x_disp);
                if(x+x1>=dimension || x+x1<0 || environment[x+x1][y]!=NULL)
                {
                    next_moves.erase(next_moves.begin());
                    return next_moves;
                }
                else
                {
                    step next;
                    next.x = x+x_disp;
                    next.y = y+y_disp;
                    next.dist = sqrt(next.x*next.x + next.y*next.y);
                    next_moves.push_back(next);
                    continue;
                }
            }
            x1 = x_disp/abs(x_disp);
            y1 = y_disp/abs(y_disp);

            if( (x+x1>=dimension || x+x1<0 || environment[x+x1][y]!=NULL) && (y+y1>=dimension || y+y1<0 || environment[x][y+y1]!=NULL))
            {
                next_moves.erase(next_moves.begin());
                return next_moves;
            }
            while(true)
            {
                int direction = rand()%2;

                if(direction==0)
                {
                    if(x+x1<dimension && x+x1>=0 && environment[x+x1][y]==NULL)
                    {
                        step next;
                        next.x = x+x1;
                        next.y = y;
                        next.dist = sqrt(next.x*next.x + next.y*next.y);
                        next_moves.push_back(next);
                        break;
                    }
                }
                else
                {
                    if(y+y1<dimension && y+y1>=0 && environment[x][y+y1]==NULL)
                    {
                        step next;
                        next.x = x;
                        next.y = y+y1;
                        next.dist = sqrt(next.x*next.x + next.y*next.y);
                        next_moves.push_back(next);
                        break;
                    }
                }
            }
        }
    }

    next_moves.erase(next_moves.begin());
    return next_moves;
}
