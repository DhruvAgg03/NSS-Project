#include "../Headers/Universe.h"
#include "../Headers/Parser.h"
#include "../Headers/Lexer.h"

#include <iostream>
using namespace std;
using std::cout;

extern std::ofstream outfile;
extern std::ofstream simulationFile;

int iterNum;
fstream configFile;
ofstream outfile;

int main()
{
  Lexer lexy(&configFile);
  lexy.readFile();
  

  srand(time(0));
  outfile.open("./Output/universelog.txt", ios::out);
  simulationFile.open("Data/trail_2.csv", ios::out);
  iterNum = 0;
  int organismCount[2] = {initialPlantCount, initialInsectCount};
  biodata_Plant variety_Plant[varieties_in_a_Species];
  biodata_Insect variety_Insect[varieties_in_a_Species];
  Universe myUni(maxVision, organismCount, variety_Plant, variety_Insect);
  myUni.run();
  outfile.close();
  return 0;
}
