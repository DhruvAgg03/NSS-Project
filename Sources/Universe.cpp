#include "../Headers/Universe.h"
extern std::ofstream outfile;
extern std::ofstream simulationFile;
#define MaleRatio 0.5
#define MOVE 0
#define BIRTH 1
#define SPLIT 2
#define DIE 3
#define sexualUrgeIncrease 1
#define DESIRABILITY 60
#define MASSEXURGE 200
// Maxenergy 
#define __PLANT_VARIETY \
  {                     \
    {10}, {20},{30},{40}     \
  }

// vision radius, speed , max energy, maxSexualUrge, desirability
#define __INSECT_VARIETY                                           \
  {                                                                \
        {8, 3, 300,200,20}, {8, 3, 300,100,60}, {9, 3, 300,150,30} \
  }
using namespace std;
// using namespace namespace_Universe;
bool compare(const step &a, const step &b) { return a.dist < b.dist; }
// Compare function used for sorting moves vector comparing two structs

int random_range(int min, int max)
{
  int in_range = rand();
  in_range = min + in_range % (max - min);
  return in_range;
}
// Generates a random number between given range [min, max)

vector<coordinates2D> Universe::adjacent_posns(coordinates2D posn)
{
  int x = posn.x;
  int y = posn.y;

  vector<coordinates2D> possible_positions;
  coordinates2D west, east, north, south;
  if (x != 0 && !this->getObject(x - 1, y))
  {
    west.x = x - 1;
    west.y = y;
    possible_positions.push_back(west);
  }
  if (x != N - 1 && !this->getObject(x + 1, y))
  {
    east.x = x + 1;
    east.y = y;
    possible_positions.push_back(east);
  }
  if (y != N - 1 && !this->getObject(x, y - 1))
  {
    north.x = x;
    north.y = y - 1;
    possible_positions.push_back(north);
  }
  if (y != 0 && !this->getObject(x, y + 1))
  {
    south.x = x;
    south.y = y + 1;
    possible_positions.push_back(south);
  }
  return possible_positions;
}

Universe::Universe(int maxR, int *organismCount, biodata_Plant variety_Plant[4], biodata_Insect variety_Insect[4],vector<vector<int>> variety)
{
  biodata_Plant vp[varieties_in_a_Species] = __PLANT_VARIETY;
  //biodata_Insect vi[varieties_in_a_Species] = __INSECT_VARIETY;
  for (int i = 0; i < varieties_in_a_Species; i++)
  {
    variety_Plant[i] = vp[i];
    //variety_Insect[i] = vi[i];
      variety_Insect[i].vision_radius = variety[i][0];
      variety_Insect[i].speed = variety[i][1];
      variety_Insect[i].max_energy = variety[i][2];
      variety_Insect[i].desirability = DESIRABILITY;
      variety_Insect[i].maxSexualUrge = MASSEXURGE;
    // temp array holding the variety of plants because we are too lazy to
    // change everything
  }
  this->createMovesVector(maxR); // Creates the VisionArray
  this->initializeVarieties(variety_Plant, variety_Insect);
  this->initializeEnvironment(organismCount, N);
}
// Constructor -
// Input maximum Radius and Number of Organisms per species
// function calls onto create movesVector (Cater to maximum radius and speed)
// and initialise Environment (Can we rename it VisionArray ??)

void Universe::createMovesVector(int maxR) // Creates the VisionArray
{
  float temp = maxR * maxR;
  for (int x = -maxR; x <= maxR; x++)
  {
    for (int y = -maxR; y <= maxR; y++)
    {
      if (x * x + y * y <= temp)
      {
        step tempstep;
        tempstep.x = x;
        tempstep.y = y;
        tempstep.dist = sqrt(x * x + y * y);
        (this->moves).push_back(tempstep);
      }
    }
  }
  sort(moves.begin(), moves.end(), compare);
  moves.erase(moves.begin()); // removes (0,0,0) from the vector
  outfile << "Constructed!!\n";
}

void Universe::initializeVarieties(biodata_Plant *plantVarieties,
                                   biodata_Insect *insectVarieties)
{
  for (int i = 0; i < varieties_in_a_Species; i++)
  {
    this->variety_Plant[i] = plantVarieties[i];
    this->variety_Insect[i] = insectVarieties[i];
  }
  // The memory address initially stored in the pointers are the same
  // the values it points are different
}

void Universe::initializeEnvironment(int *organismCount, int len)
{
  vector<tuple<int,int,int>> colorList {{128,0,0},{128,128,0},{0,255,255},{255,0,255}};
  // Generating an array of all the coordinates
  std::vector<std::tuple<int, int>> tempPoints; // temporary Points
  for (int i = 0; i < dimension; i++)
    for (int j = 0; j < dimension; j++)
      tempPoints.push_back(std::make_tuple(i, j));
  std::random_shuffle(tempPoints.begin(), tempPoints.end());

  // Assigning the elements of environment to the necessary instances
  int counter = 0; // Running over the temporary array
  simulationFile<<"Iter_no,x,y,Spec_ID,Adhaar_number,action,r,g,b\n";
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < organismCount[i]; j++)
    {
      if (i == PLANT)
      {
        int variety = random_range(
            0, varieties_in_a_Species); // I am calling it seperately so that
                                        // later on can bring in variation in
                                        // the food source amount
        Plant *temp = new Plant(
            std::get<0>(tempPoints[counter]), std::get<1>(tempPoints[counter]),
            0, NULL, 0, variety_Plant[variety].max_energy,
            variety_Plant[variety].max_energy, counter, 0);
        environment[std::get<0>(tempPoints[counter])]
                   [std::get<1>(tempPoints[counter])] = temp;
      }
      else if (i == INSECT)
      {
        int variety = random_range(0, varieties_in_a_Species);
        tuple<int,int,int> hue = colorList[variety];

        coordinates2D posn = {std::get<0>(tempPoints[counter]), std::get<1>(tempPoints[counter])};
        int vision_radius = variety_Insect[variety].vision_radius;
        int speed = variety_Insect[variety].speed;
        int max_energy = variety_Insect[variety].max_energy;
        int maxSexUrge = variety_Insect[variety].maxSexualUrge;
        int desirability = variety_Insect[variety].desirability;
        Traits t{max_energy, vision_radius, speed,maxSexUrge,desirability};
        float temp1 = (float)rand()/RAND_MAX;;
        int g = ( temp1 > MaleRatio ) ? FEMALE : MALE ;

        // New Insect constructor
        Insect *temp = new Insect(posn, t, counter, 1, this,g,hue);
        // Insect *temp = new Insect(
        //     std::get<0>(tempPoints[counter]), std::get<1>(tempPoints[counter]),
        //     variety_Insect[variety].vision_radius, NULL,
        //     variety_Insect[variety].speed, variety_Insect[variety].max_energy,
        //     variety_Insect[variety].max_energy, counter, counter, 1);

        environment[std::get<0>(tempPoints[counter])]
                   [std::get<1>(tempPoints[counter])] = temp;
        InsectPosition.push_back(
            std::make_tuple(std::get<0>(tempPoints[counter]),
                            std::get<1>(tempPoints[counter])));
        insects.push_back(temp);
      }
      counter++;
    }
  }
  for (int i = counter; i < dimension * dimension; i++)
  {
    environment[std::get<0>(tempPoints[counter])]
               [std::get<1>(tempPoints[counter])] = NULL;
  }
}
// input number of organism (Say the we specify each organism is a list, first
// element being number of food sources, next being number of prey and so on)
// creating all the coordinates for the matrix using TempPoints (call it
// temporary Coordinates (TempCoord) ?) Creating the functions that assigns the
// necessary pointers to class based on data we know

std::vector<struct step> Universe::getMoves() { return this->moves; }

void Universe::printMoves(ofstream &outfile)
{
  int i; // Counter
  for (i = 0; i < (this->moves).size(); i++)
    outfile << "(" << (this->moves)[i].dist << "," << (this->moves[i]).x
            << "," << (this->moves)[i].y << ") " << endl;
  outfile << "\n i is " << i << "\n";
  return;
}

UpdateUniverse_rt Universe::updateUniverse(int initX, int initY, int finalX, int finalY, ofstream &outfile)
{
  if(finalX<0 || finalY<0 || finalX>=dimension || finalY>=dimension)
    return STOP_PATH;
  Insect *org = (Insect *)getObject(initX, initY);
  if (org == NULL || org->get_speciesID() != INSECT)
    return INVALID_ORGANISM;
  Organism *finalPosn = (Organism *)getObject(finalX, finalY);

  if (org->get_current_energy() <= movementCost)
  {
    insects.erase(find(insects.begin(),insects.end(),environment[initX][initY]));
    environment[initX][initY] = NULL;
    return DYING_ORGANISM;
  }

  if (finalPosn != NULL && finalPosn->get_speciesID() == INSECT)
    return STOP_PATH;

  org->update(finalX, finalY);

  if (finalPosn!=NULL && finalPosn->get_speciesID()==PLANT)
  {
    org->addEnergy(finalPosn->get_current_energy());
    finalPosn->die();
  }
  if(finalX!=initX || finalY!=initY)
  {
    environment[finalX][finalY] = org;
    environment[initX][initY] = NULL;
  }
  return SUCCESS;
}

vector<Insect *> Universe::getInsects() { return insects; }

void *Universe::getObject(int posX, int posY)
{
  if (posX < 0 || posX >= dimension || posY < 0 || posY >= dimension)
    return NULL;
  void *reqPoint = environment[posX][posY];
  return reqPoint;
}

int Universe::getNumberOfInsects() { return insects.size(); }

std::tuple<int, int> Universe::getAnInsect(int i)
{
  std::tuple<int, int> temp;
  get<0>(temp) = insects[i]->get_x();
  get<1>(temp) = insects[i]->get_y();
  return temp;
}

void Universe::killInsect(Insect *insect)
{
  environment[insect->get_x()][insect->get_y()] = NULL;
  organismCount[insectIndex]--;
  Insect *copy = insect;
  insects.erase(std::remove(insects.begin(), insects.end(), copy), insects.end());
  insect->die();
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

void Universe::creatingAndUpdatingDisplayEnvironmentHistory(ofstream &outfile)
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
        int temp_speciesID =
            ((Plant *)environment[i][j])->get_speciesID();
        switch (temp_speciesID)
        {
        case PLANT: // Plant
          displayEnvironment[dimension * i + j] = 0;
          break;
        case INSECT: // Insect
          displayEnvironment[dimension * i + j] = 1;
          break;
        default:
          break;
        }
      }
    }
  }
  outfile << "displayEnvironment created\n";
}

void Universe::writingToFile(ofstream &outfile)
{
  FILE *fptr;
  fptr = fopen("Data.txt", "w");
  if (fptr == NULL)
  {
    outfile << "Couldn't open file Data.txt!!\n";
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

//function to check if protagonist and interest are close enough to be able to reach each other and have energy left to reproduce
bool Universe::canMeetAndMate(Insect* protagonist,step protagonist_location, step interest_location)
{
  if(((Organism *)environment[interest_location.x][interest_location.y])->get_speciesID() != INSECT)
    return false;
  
  Insect* interest = ((Insect *)environment[interest_location.x][interest_location.y]);
  int distance = abs(protagonist_location.x - interest_location.x) + abs(protagonist_location.y - interest_location.y);

  //can only reproduce if energy after reaching mate is >= minimumMatingEnergyPercentage of max energy
  if(protagonist->get_current_energy() >= (distance + (protagonist->get_max_energy())*minimumMatingEnergyPercentage))
  {
    if(interest->get_current_energy() >= (distance + (interest->get_max_energy())*minimumMatingEnergyPercentage))
    {
      return true;
    }
  }
  return false;
}

//function which returns location of a free, reachable mate to protagonist
step Universe::scanNearestMate(step current_position, int vision_radius, Insect* protagonist)
{
  int ID_protagonist = protagonist->get_aadhar_number();
  if(Organisms_in_love.find(protagonist) != Organisms_in_love.end())
  {
      step temp;
      temp.x = -1;
      temp.y = -1;
      temp.dist = -1;
      return temp;
  }

  vector<step> moves_array = getMoves();
  int nearest_dist_index = -1;

  //covering all closest cells starting from location of protagonist
  for(int i=0;i<moves_array.size();i++)
  {
    if(vision_radius < moves_array[i].dist)
    {
      step temp;
      temp.x = -1;
      temp.y = -1;
      temp.dist = -1;
      return temp;
    }
    int x = current_position.x + moves_array[i].x;
    int y = current_position.y + moves_array[i].y;
    if (x >= dimension || x < 0 || y >= dimension || y < 0)
      continue; 
    
    if (environment[x][y] != NULL && ((Organism *)environment[x][y])->get_speciesID() == INSECT)
    {
      step potential_mate_location;
      potential_mate_location.x = x;
      potential_mate_location.y = y;
      Insect* interest = ((Insect *)environment[x][y]);
      int love_interest = ((Organism *)environment[x][y])->get_aadhar_number();

      //checking if the insect found is already locked in to mate with some other organism
      if(Organisms_in_love.find(interest) != Organisms_in_love.end())
        continue;
      
      //checking for opposite genders
      bool gender1 = protagonist->get_gender();
      bool gender2 = ((Insect *)environment[potential_mate_location.x][potential_mate_location.y])->get_gender();
      if(gender1 == gender2)
        continue;


    
      if(willReproduce(protagonist, interest))
      {
        if(canMeetAndMate(protagonist, current_position, potential_mate_location))
        {
          //nearest_dist_index = i;
          Organisms_in_love.insert({protagonist,interest});
          Organisms_in_love.insert({interest,protagonist});
          return potential_mate_location;
        }
      }
    }
  }

  step temp;
  temp.x = -1;
  temp.y = -1;
  temp.dist = -1;
  return temp;
}

step Universe::scanNearestFoodSourceNew(step current_position, int vision_radius, set<pair<int, int>> &ignore_food)
{
  vector<step> moves_array = getMoves();
  int nearest_dist_index = -1;

  for (int i = 0; i < moves_array.size(); i++)
  {
    if (vision_radius < moves_array[i].dist)
    {
      step temp;
      temp.x = -1;
      temp.y = -1;
      temp.dist = -1;
      return temp;
    }
    int x = current_position.x + moves_array[i].x;
    int y = current_position.y + moves_array[i].y;
    if (x >= dimension || x < 0 || y >= dimension || y < 0)
      continue;
    // What are we placing for plant and insect? 1 for plant?
    Plant *p;
    if (environment[x][y] != NULL && ((Organism *)environment[x][y])->get_speciesID() == PLANT)
    {
      // IGNORING FOOD
      if (ignore_food.find({x, y}) != ignore_food.end())
        continue;

      nearest_dist_index = i;
      break;
    }
  }
  float nearest_dist = moves_array[nearest_dist_index].dist;
  while (nearest_dist_index > 0 &&
         nearest_dist == moves_array[nearest_dist_index - 1].dist)
    nearest_dist_index--;
  vector<step> possible_destinations;

  int tempct = 0;

  while (nearest_dist_index < moves_array.size() &&
         moves_array[nearest_dist_index].dist == nearest_dist)
  {
    tempct++;
    int x = current_position.x + moves_array[nearest_dist_index].x;
    int y = current_position.y + moves_array[nearest_dist_index].y;

    if (x >= dimension || x < 0 || y >= dimension || y < 0)
    {
      nearest_dist_index++;
      continue;
    }

    // What are we placing for plant and insect? 1 for plant?
    Plant *p;
    // if (typeid(environment[x][y]) == typeid(p))
    if (environment[x][y] != NULL &&
        ((Organism *)environment[x][y])->get_speciesID() ==
            PLANT)
    {

      // IGNORING FOOD
      if (ignore_food.find({x, y}) != ignore_food.end())
      {
        nearest_dist_index++;
        continue;
      }

      struct step s;
      s.x = x;
      s.y = y;
      s.dist = sqrt(x * x + y * y);
      possible_destinations.push_back(s);
    }
    nearest_dist_index++;
  }
  int random_index = rand() % (possible_destinations.size());
  return possible_destinations[random_index];
}

vector<step> Universe::movesToLocationNew(step current_position, int number_of_steps, int vision_radius)
{
  int safe_last = 0;
  vector<step> next_moves;
  set<pair<int, int>> ignore_food;
  next_moves.push_back(current_position);
  Insect* protagonist = ((Insect *)environment[current_position.x][current_position.y]);
  step lockedin_mate; //can only reproduce with one other organism per movement
  bool already_reproduced = false;
  lockedin_mate.x = -1;
  lockedin_mate.y = -1;
  lockedin_mate.dist = -1;
  for (int i = 0; i < number_of_steps; i++)
  {
    step curr = next_moves[i];
    int x = curr.x;
    int y = curr.y;
    step nearest_food =
        scanNearestFoodSourceNew(curr, vision_radius, ignore_food);

    step nearest_mate;

    //Protagonist already locked in from previous iteration
    if(Organisms_in_love.find(protagonist) != Organisms_in_love.end())
    {
      nearest_mate.x = Organisms_in_love[protagonist]->get_x();
      nearest_mate.y = Organisms_in_love[protagonist]->get_y();
    }
    //Protagonist definitely does not have enough energy to reproduce
    else if(protagonist->get_current_energy() < (minimumMatingEnergyPercentage*(protagonist->get_max_energy())))
    {
      nearest_mate.x = -1;
      nearest_mate.y = -1;
      nearest_mate.dist = -1;
    }
    //Protagonist may have enough energy to reproduce and is free
    else
      nearest_mate = scanNearestMate(curr,vision_radius,protagonist);

    //hasn't reproduced this iteration yet
    if(lockedin_mate.x == -1 && (!already_reproduced))
    {
      lockedin_mate = nearest_mate;
    }

    //Random move when no food in sight or mate locked in 
    if (nearest_food.x < 0 && lockedin_mate.x < 0)
    {
      int flag = 1;
      bool no_empty_spot = false;

      Insect *insect;
      if (((x + 1 >= dimension) ||
           ((environment[x + 1][y] != NULL) &&
            (((Organism *)environment[x + 1][y])
                 ->get_speciesID() == INSECT))) &&
          ((x - 1 < 0) ||
           ((environment[x - 1][y] != NULL) &&
            (((Organism *)environment[x - 1][y])
                 ->get_speciesID() == INSECT))) &&
          ((y + 1 >= dimension) ||
           ((environment[x][y + 1] != NULL) &&
            (((Organism *)environment[x][y + 1])
                 ->get_speciesID() == INSECT))) &&
          ((y - 1 < 0) ||
           ((environment[x][y - 1] != NULL) &&
            (((Organism *)environment[x][y - 1])
                 ->get_speciesID() == INSECT))))
        no_empty_spot = true;
      if(no_empty_spot) break;
      while (flag == 1)
      {
        int x_disp = rand() % 2;
        if (x_disp == 0)
          x_disp--;
        int y_disp = rand() % 2;
        if (y_disp == 0)
          y_disp--;
        int axis = rand() % 2;
        if (axis == 0)
          x_disp = 0;
        else
          y_disp = 0;
        // if(no_empty_spot || (x + x_disp >= 0 && x + x_disp < dimension && y +
        // y_disp >=0 && y + y_disp < dimension &&
        // (environment[x+x_disp][y+y_disp] == NULL ||
        // typeid(environment[x+x_disp][y+y_disp]) != typeid(insect)))
        if (no_empty_spot ||
            (((x + x_disp) >= 0) && ((x + x_disp) < dimension) &&
             ((y + y_disp) >= 0) && ((y + y_disp) < dimension) &&
             ((environment[x + x_disp][y + y_disp] == NULL) ||
              (((Organism *)
                    environment[x + x_disp][y + y_disp])
                   ->get_speciesID()) == PLANT)))
        {
          flag = 0;
          step next;
          next.x = x + x_disp;
          next.y = y + y_disp;
          next.dist = sqrt(next.x * next.x + next.y * next.y);
          next_moves.push_back(next);
          if (!no_empty_spot)
            safe_last = i + 1;
        }
        else
        {
          // final posn has insect, stops moving in that case
          flag = 0;
          step next;
          next.x = x;
          next.y = y;
          next.dist = sqrt(next.x * next.x + next.y * next.y);
          next_moves.push_back(next);
          if (!no_empty_spot)
            safe_last = i + 1;
        }
      }
    }

    else
    {
      int x_disp;
      int y_disp;
      //Lockedin mate exists, will try to go there
      if(lockedin_mate.x >=0)
      {
        x_disp = lockedin_mate.x - x;
        y_disp = lockedin_mate.y - y;
      }
      //Food exists nearby, will go there
      else
      {
        x_disp = nearest_food.x - x;
        y_disp = nearest_food.y - y;
      }

      //One step away from final destination
      if (((abs(x_disp) == 0) && (abs(y_disp) == 1)) ||
          ((abs(x_disp) == 1) && (abs(y_disp) == 0)))
      {
        step next;
        //Will stay in same spot for a move, and reproduce
        if(lockedin_mate.x >=0)
        {
          //Organism* interest = (Organism*)environment[lockedin_mate.x][lockedin_mate.y];
          //Organisms_in_love.erase(protagonist->get_aadhar_number());    
          //****Cant remove from map here, MUST be removed from map while simulation
          //Organisms_in_love.erase(interest->get_aadhar_number());
          next.x = x;
          next.y = y;
          next.dist = sqrt(next.x * next.x + next.y * next.y);
          next_moves.push_back(next);
          safe_last = i+1;
          already_reproduced = true;
          lockedin_mate.x = -1;
          lockedin_mate.y = -1;
          lockedin_mate.dist = -1;
          break;
        }
        else
        {
          next.x = x + x_disp;
          next.y = y + y_disp;
          next.dist = sqrt(next.x*next.x + next.y*next.y);
          next_moves.push_back(next);
          ////////changed here
          safe_last = i+1;
          /////////
          if (ignore_food.find({next.x, next.y}) == ignore_food.end() && ((next.x =! x) || (next.y!=y) ))
          {
          ignore_food.insert({next.x, next.y});
          }
        }
        continue;
      }

      Insect *ins;
      int x1, y1;
      //will move one step closer in y direction
      if (x_disp == 0)
      {
        y1 = y_disp / abs(y_disp);
        if ((y + y1 >= dimension) || (y + y1 < 0) ||
            ((environment[x][y + y1] != NULL) &&
             (((Organism *)environment[x][y + y1])
                  ->get_speciesID() == INSECT)))
        {
          if ((y + y1 >= 0) && (y + y1 < dimension))
          {
            break;
            step next;
            //next.x = x + x_disp;
            //next.y = y + y_disp;
            next.x=x+x_disp;
            next.y=y+y1;
            next.dist = sqrt(next.x * next.x + next.y * next.y);
            next_moves.push_back(next);
            continue;
          }
        }
        else
        {
          step next;
          //next.x = x + x_disp;
          //next.y = y + y_disp;
          next.x = x+x_disp;
          next.y=y+y1;
          next.dist = sqrt(next.x * next.x + next.y * next.y);
          next_moves.push_back(next);
          safe_last = i + 1;
          continue;
        }
      }
      //will move one step closer in x direction
      if (y_disp == 0)
      {
        x1 = x_disp / abs(x_disp);
        if ((x + x1 >= dimension) || (x + x1 < 0) ||
            ((environment[x + x1][y] != NULL) &&
             (((Organism *)environment[x + x1][y])
                  ->get_speciesID() == INSECT)))
        {
          if ((x + x1 >= 0) && (x + x1 < dimension))
          {
            break;
            step next;
            //next.x = x + x_disp;
            //next.y = y + y_disp;
            next.x=x+x1;
            next.y=y+y_disp;
            next.dist = sqrt(next.x * next.x + next.y * next.y);
            next_moves.push_back(next);
            continue;
          }
        }
        else
        {
          step next;
          //next.x = x + x_disp;
          //next.y = y + y_disp;
          next.x=x+x1;
          next.y=y+y_disp;
          next.dist = sqrt(next.x * next.x + next.y * next.y);
          next_moves.push_back(next);
          safe_last = i + 1;
          continue;
        }
      }

      x1 = x_disp / abs(x_disp);
      y1 = y_disp / abs(y_disp);

      bool no_empty_spot = false;
      if (((x + x1 >= dimension) || (x + x1 < 0) ||
           ((environment[x + x1][y] != NULL) &&
            (((Organism *)environment[x + x1][y])
                 ->get_speciesID() == INSECT))) &&
          ((y + y1 >= dimension) || (y + y1 < 0) ||
           ((environment[x][y + y1] != NULL) &&
            (((Organism *)environment[x][y + y1])
                 ->get_speciesID() == INSECT))))
        no_empty_spot = true;
      if(no_empty_spot) break;
      //will move one step closer in a random direction (x or y)
      while (true)
      {
        int direction = rand() % 2;
        if (direction == 0)
        {
          if (no_empty_spot ||
              ((x + x1 < dimension) && (x + x1 >= 0) &&
               ((environment[x + x1][y] == NULL) ||
                (((Organism *)environment[x + x1][y])
                     ->get_speciesID() != INSECT))))
          {
            step next;
            next.x = x + x1;
            next.y = y;
            next.dist = sqrt(next.x * next.x + next.y * next.y);
            next_moves.push_back(next);
            if (!no_empty_spot)
              safe_last = i + 1;
            break;
          }
        }
        else
        {
          if (no_empty_spot ||
              ((y + y1 < dimension) && (y + y1 >= 0) &&
               ((environment[x][y + y1] == NULL) ||
                (((Organism *)environment[x][y + y1])
                     ->get_speciesID() != INSECT))))
          {
            step next;
            next.x = x;
            next.y = y + y1;
            next.dist = sqrt(next.x * next.x + next.y * next.y);
            next_moves.push_back(next);
            if (!no_empty_spot)
              safe_last = i + 1;
            break;
          }
        }
      }
    }
  }
/*
  for (int i = next_moves.size() - 1; i > safe_last; i--)
  {
    next_moves.pop_back();
  }*/
  next_moves.erase(next_moves.begin());
  return next_moves;
}

bool Universe::printCompleteInfo(int iteration)
{
  ofstream myfile;
  outfile<<"*************************************************\nIteration: "<<iteration<<'\n';
  int pc = 0, ic = 0;
  if (iteration == 1)
  {
    myfile.open("Data/trail_1.csv", ios::out);
    myfile << "Iter_no,x,y,Spec_ID,Adhaar_number,SpeedLength,VisionRadius,MaxEnergy,CurrentEnergy\n";
  }
  else
    myfile.open("Data/trail_1.csv", ios::app);

  for (int i = 0; i < dimension; i++)
  {
    for (int j = 0; j < dimension; j++)
    {
      auto cell = getObject(i, j);
      if (cell)
      {
        auto org = static_cast<Organism *>(cell);
        if (org->get_speciesID() == plantIndex)
          pc++;
        else
          ic++;
        myfile << iteration << "," << i << "," << j << "," << org->get_speciesID() << "," << org->get_aadhar_number() << "," << org->giveSpeed() << "," << org->get_vision_radius() << "," << org->get_max_energy() << "," << org->get_current_energy() << "\n";
      }
      // else
      // myfile << iteration << "," << i << "," << j << ",-1,0,0,0,0,0\n";
    }
  }
  cout <<iteration<<" "<< pc << " " << ic << '\n';
  myfile.close();
  return true;
}

void Universe::addInsect(Insect *insect)
{
  environment[insect->get_x()][insect->get_y()] = insect;
  organismCount[insectIndex]++;
  insects.push_back(insect);
}

void Universe::addPlant(Plant *plant)
{
  environment[plant->get_x()][plant->get_y()] = plant;
  organismCount[plantIndex]++;
}

bool Universe::locked(coordinates2D pos)
{
  vector<pair<int, int>> neigh{{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}};
  for (auto ele : neigh)
  {
    auto delx = ele.first;
    auto dely = ele.second;
    if (!getObject(pos.x + delx, pos.y + dely))
      return false;
  }
  return true;
}

void Universe::reSpawnPlant()
{
 vector<coordinates2D> newcells = emptycells(((initialPlantCount)/(plantSpawnFreq)));
  outfile << "New plants spawned: " << newcells.size() << '\n';
  vector<biodata_Plant> plantvariety = __PLANT_VARIETY;
  for (auto ele : newcells)
  {
    Plant *newplant = new Plant(ele, plantvariety[rand() % varieties_in_a_Species].max_energy,
                                static_cast<unsigned>(Organism::get_latest_organism_ID() + 1));
    // energy of new plant is taken from hardcoded varities
    addPlant(newplant);
  }
}

vector<coordinates2D> Universe::emptycells(int k)
{
  int max_threshold = max(500, k * 5);
  vector<coordinates2D> emptycells;
  while (emptycells.size() < k && max_threshold--)
  {
    int x = rand() % dimension;
    int y = rand() % dimension;
    if (!getObject(x, y))
    {
      emptycells.push_back({x, y});
    }
  }
  return emptycells;
}

bool Universe::willReproduce(Insect* I1,Insect* I2)
{
    if(I1->get_gender() == I2->get_gender())
      return false;
    //Assuming both insects are of different gender
    int dist = 0;
    dist+= std::abs((I1->get_posn()).x - (I2->get_posn()).x);
    dist+= std::abs((I2->get_posn()).y - (I2->get_posn()).y);
    float r1 = ((float)(I1->get_current_energy()))/(I1->get_max_energy());
    float r2 = ((float)(I2->get_current_energy()))/(I2->get_max_energy());
    float sexProduct = (I1->getSexualUrge())*(I2->getSexualUrge());
    float NotNormalised = (sexProduct*r1*r2)/dist;
    float probab = NotNormalised/4000;
    return probab > ((float)rand()/RAND_MAX);
    //return true;
}
