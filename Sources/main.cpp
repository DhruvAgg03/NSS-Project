#include "../Headers/Universe.h"
#include "../Headers/Parser.h"
#include "../Headers/Lexer.h"

#include <iostream>

// #define CONFIG_FILE_NAME "/home/hhn/cs/PC03-NSS/.env"
using namespace std;
using std::cout;

extern std::ofstream outfile;
std::ofstream simulationFile;

int iterNum;
fstream configFile;
ofstream outfile;

void set_values(Parser *parsy)
{
  auto &valuesMap = (parsy->variableMap);
  if(valuesMap["iterNum"] != "")
    iterNum = stoi(valuesMap["iterNum"]);
}

int main()
{
  configFile.open(CONFIG_FILE_NAME);
  Lexer lexy(&configFile);
  lexy.readFile();
  Parser parsy(lexy.valuesMap);

  set_values(&parsy);
  cout << iterNum << endl;
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
