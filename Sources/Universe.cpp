#include "../Headers/Universe.h"
extern std::ofstream outfile;

#define __PLANT_VARIETY \
  {                     \
    {10}, {20},         \
    {                   \
      30                \
    }                   \
  }

#define __INSECT_VARIETY      \
  {                           \
    {4, 3, 300}, {6, 3, 300}, \
    {                         \
      7, 3, 300               \
    }                         \
  }

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
  if (x != 0 && this->getObject(x - 1, y) == NULL)
  {
    west.x = x - 1;
    west.y = y;
    possible_positions.push_back(west);
  }
  if (x != N - 1 && this->getObject(x + 1, y) == NULL)
  {
    east.x = x + 1;
    east.y = y;
    possible_positions.push_back(east);
  }
  if (y != N - 1 && this->getObject(x, y - 1) == NULL)
  {
    north.x = x;
    north.y = y - 1;
    possible_positions.push_back(north);
  }
  if (y != 0 && this->getObject(x, y + 1) == NULL)
  {
    south.x = x;
    south.y = y + 1;
    possible_positions.push_back(south);
  }
  return possible_positions;
}

Universe::Universe(int maxR, int *organismCount, biodata_Plant variety_Plant[varieties_in_a_Species], biodata_Insect variety_Insect[varieties_in_a_Species])
{
  biodata_Plant vp[varieties_in_a_Species] = __PLANT_VARIETY;
  biodata_Insect vi[varieties_in_a_Species] = __INSECT_VARIETY;
  for (int i = 0; i < varieties_in_a_Species; i++)
  {
    variety_Plant[i] = vp[i];
    variety_Insect[i] = vi[i];

    // temp array holding the variety of plants because we are too lazy to
    // change everything
  }
  this->createMovesVector(maxR);  // Creates the VisionArray
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

        coordinates2D posn = {std::get<0>(tempPoints[counter]),std::get<1>(tempPoints[counter])};
        int vision_radius = variety_Insect[variety].vision_radius;
        int speed = variety_Insect[variety].speed;
        int max_energy = variety_Insect[variety].max_energy;
        Traits t{max_energy, vision_radius, speed};

        // New Insect constructor
        Insect *temp = new Insect(posn, t, counter, 1,this);

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

void Universe::printMoves(ofstream& outfile)
{
  int i; // Counter
  for (i = 0; i < (this->moves).size(); i++)
    outfile << "(" << (this->moves)[i].dist << "," << (this->moves[i]).x
              << "," << (this->moves)[i].y << ") " << endl;
  outfile << "\n i is " << i << "\n";
  return;
}

int Universe::updateUniverse(int initX, int initY, int finalX, int finalY,ofstream& outfile)
{
  void *movingObj = getObject(initX, initY);
  int returnValue = 0;
  if (movingObj != NULL)
  {
    auto OrganismObj = (Organism *)movingObj;
    if (OrganismObj->get_speciesID() == PLANT)
      return -1;
    else if (OrganismObj->get_speciesID() == INSECT)
    {
      if (OrganismObj->get_current_energy() <= movementCost)
      {
        killInsect((Insect *)OrganismObj);
        environment[initX][initY] = NULL;
        return -2;
      }
      OrganismObj->update(finalX, finalY);
      void *newObj = getObject(finalX, finalY);
      if (newObj != NULL)
      {
        if (((Organism *)newObj)->get_speciesID() == PLANT)
        {
          OrganismObj->addEnergy(((Organism *)newObj)->get_current_energy());
          ((Organism *)newObj)->die();
        }
      }
    }
    else
      outfile << "error parsing" << endl;
  }
  environment[finalX][finalY] = movingObj;
  environment[initX][initY] = NULL;
  return returnValue;
}

vector<Insect *> Universe::getInsects() { return insects; }

void *Universe::getObject(int posX, int posY)
{
  if(posX < 0 || posX >= dimension || posY < 0 || posY >= dimension)return NULL;
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

void Universe::creatingAndUpdatingDisplayEnvironmentHistory(ofstream& outfile)
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
  outfile<<"displayEnvironment created\n";
}

void Universe::writingToFile(ofstream& outfile)
{
  FILE *fptr;
  fptr = fopen("Data.txt", "w");
  if (fptr == NULL)
  {
    outfile<<"Couldn't open file Data.txt!!\n";
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

step Universe::scanNearestFoodSourceNew(step current_position, int vision_radius,set<pair<int, int>>& ignore_food)
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
    if ( environment[x][y] != NULL && ((Organism *)environment[x][y])->get_speciesID() == PLANT )
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
  for (int i = 0; i < number_of_steps; i++)
  {
    step curr = next_moves[i];
    int x = curr.x;
    int y = curr.y;
    step nearest_food =
        scanNearestFoodSourceNew(curr, vision_radius, ignore_food);
    if (nearest_food.x < 0)
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
      }
    }

    else
    {
      int x_disp = nearest_food.x - x;
      int y_disp = nearest_food.y - y;
      if (((abs(x_disp) == 0) && (abs(y_disp) == 1)) ||
          ((abs(x_disp) == 1) && (abs(y_disp) == 0)))
      {
        step next;
        next.x = x + x_disp;
        next.y = y + y_disp;
        next.dist = sqrt(next.x * next.x + next.y * next.y);
        next_moves.push_back(next);
        ////////changed here
        safe_last = i + 1;
        /////////
        if (ignore_food.find({next.x, next.y}) == ignore_food.end())
        {
          ignore_food.insert({next.x, next.y});
        }
        continue;
      }

      Insect *ins;
      int x1, y1;
      if (x_disp == 0)
      {
        y1 = y_disp / abs(y_disp);
        // if(y+y1 >= dimension || y+y1<0 || typeid(environment[x][y+y1]) ==
        // typeid(ins) )
        if ((y + y1 >= dimension) || (y + y1 < 0) ||
            ((environment[x][y + y1] != NULL) &&
             (((Organism *)environment[x][y + y1])
                  ->get_speciesID() == INSECT)))
        {
          if ((y + y1 >= 0) && (y + y1 < dimension))
          {
            step next;
            next.x = x + x_disp;
            next.y = y + y_disp;
            next.dist = sqrt(next.x * next.x + next.y * next.y);
            next_moves.push_back(next);
            continue;
          }
        }
        else
        {
          step next;
          next.x = x + x_disp;
          next.y = y + y_disp;
          next.dist = sqrt(next.x * next.x + next.y * next.y);
          next_moves.push_back(next);
          safe_last = i + 1;
          continue;
        }
      }
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
            step next;
            next.x = x + x_disp;
            next.y = y + y_disp;
            next.dist = sqrt(next.x * next.x + next.y * next.y);
            next_moves.push_back(next);
            continue;
          }
        }
        else
        {
          step next;
          next.x = x + x_disp;
          next.y = y + y_disp;
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
                 ->get_speciesID() == PLANT))) &&
          ((y + y1 >= dimension) || (y + y1 < 0) ||
           ((environment[x][y + y1] != NULL) &&
            (((Organism *)environment[x][y + y1])
                 ->get_speciesID() == PLANT))))
        no_empty_spot = true;

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

  for (int i = next_moves.size() - 1; i > safe_last; i--)
  {
    next_moves.pop_back();
  }
  next_moves.erase(next_moves.begin());
  return next_moves;
}

void Universe::printCompleteInfo(int iteration)
{
  ofstream myfile;
  if (iteration == 1)
  {
    myfile.open("./Data/trail_1.csv", ios::out);
    myfile << "Iter_no,x,y,Spec_ID,Adhaar_number,SpeedLength,VisionRadius,MaxEnergy,CurrentEnergy\n";
  }
  else
    myfile.open("./Data/trail_1.csv", ios::app);

  for (int i = 0; i < dimension; i++)
  {
    for (int j = 0; j < dimension; j++)
    {
      auto cell = getObject(i, j);
      if (cell)
      {
        auto org = static_cast<Organism *>(cell);
        myfile << iteration << "," << i << "," << j << "," << org->get_speciesID() << "," << org->get_aadhar_number() << "," << org->giveSpeed() << "," << org->get_vision_radius() << "," << org->get_max_energy() << "," << org->get_current_energy() << "\n";
      }
      else
        myfile << iteration << "," << i << "," << j << ",-1,0,0,0,0,0\n";
    }
  }
  myfile.close();
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
  vector<pair<int,int>> neigh{{-1,1},{0,1},{1,1},{-1,0},{1,0},{-1,-1},{0,-1},{1,-1}};
  for(auto ele:neigh)
  {
    auto delx=ele.first;
    auto dely=ele.second;
    if(!getObject(pos.x+delx,pos.y+dely)) return false;
  }
  return true;
}

void Universe::reSpawnPlant()
{
  auto newcells = emptycells(plantSpawnNumber);
  outfile<<"New plants spawned: "<<newcells.size()<<'\n';
  vector<biodata_Plant> plantvariety =  __PLANT_VARIETY;
  for(auto ele: newcells)
  {
    auto newplant = new Plant(ele, plantvariety[rand()%varieties_in_a_Species].max_energy,
                        static_cast<unsigned short>(Organism::get_latest_organism_ID()+1)); 
                        //energy of new plant is taken from hardcoded varities
    addPlant(newplant);
  }
}

vector<coordinates2D> Universe::emptycells(int k)
{
  int max_threshold = max(500, k * 5);
  vector<coordinates2D> emptycells;
  while(emptycells.size()<k && max_threshold--)
  {
    auto x = rand()%dimension;
    auto y = rand()%dimension;
    if(!getObject(x,y))
    {
      emptycells.push_back({x,y});
    }
  }
  return emptycells;
}
