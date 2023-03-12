#include "../Headers/Universe.h"
#include "../Headers/Parser.h"
#include "../Headers/Lexer.h"
#include <bits/stdc++.h>

#include <iostream>

// #define CONFIG_FILE_NAME "/home/hhn/cs/PC03-NSS/.env"
using namespace std;
using std::cout;

extern std::ofstream outfile;
std::ofstream simulationFile;

int iterNum;
int iterationCount;
int initialPlantCount;
int initialInsectCount;
int REPRODUCETYPE;
int varieties_in_a_Species;
vector<vector<int>> variety;
fstream configFile;
ofstream outfile;

void set_values(Parser *parsy)
{
  auto &valuesMap = (parsy->variableMap);
  iterationCount = stoi(valuesMap["iterationCount "]);
  initialPlantCount = stoi(valuesMap["initialPlantCount "]);
  initialInsectCount = stoi(valuesMap["initialInsectCount "]);
  REPRODUCETYPE = stoi(valuesMap["REPRODUCETYPE "]);
  varieties_in_a_Species = stoi(valuesMap["varieties_in_a_Species "]);
  vector<vector<int>> full_variety;
  full_variety.push_back(parsy->get_int_vector(valuesMap["v1 "]));
  full_variety.push_back(parsy->get_int_vector(valuesMap["v2 "]));
  full_variety.push_back(parsy->get_int_vector(valuesMap["v3 "]));
  full_variety.push_back(parsy->get_int_vector(valuesMap["v4 "]));
  for(int i=0;i<varieties_in_a_Species;i++) variety.push_back(full_variety[i]);
}

int main()
{
  configFile.open("./config.txt",ios::in);
  Lexer lexy(&configFile);
  lexy.readFile();
  Parser parsy(lexy.valuesMap);

  set_values(&parsy);
  cout << iterNum << endl;
  srand(time(0));
  outfile.open("./Output/universelog.txt", ios::out);
  simulationFile.open("./Data/trail_2.csv", ios::out);
  iterNum = 0;
  int organismCount[2] = {initialPlantCount, initialInsectCount};
  biodata_Plant variety_Plant[varieties_in_a_Species];
  biodata_Insect variety_Insect[varieties_in_a_Species];
  Universe myUni(maxVision, organismCount, variety_Plant, variety_Insect,variety);
  myUni.run();
  outfile.close();
  return 0;
}
