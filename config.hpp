#ifndef CONFIG_HPP
#define CONFIG_HPP
#include "nlohmann/json.hpp"
#include "setting.hpp"
#include <string>
#include <vector>
enum PivotStrategy { FIRST, LAST, MIDDLE, RANDOM };
class Config {
private:
  static Setting<std::string> configFile;

public:
  static Setting<int> randomSeed;
  static Setting<bool> inTestMode;
  static Setting<std::string> testFilename;
  static Setting<std::vector<int>> testCasesNodeCounts;
  static Setting<int> testRepetitionCounter;
  static Setting<std::string> testProblem;
  static Setting<bool> printAfterGenerating;
  static Setting<bool> printAfterSolving;
  static Setting<bool> testIfSolved;
  static Setting<bool> testINT;
  static Setting<bool> testFLOAT;
  static Setting<bool> testDOUBLE;
  static Setting<bool> testCHAR;
  static void loadConfigFromFile();
  static void setConfigFile(std::string filename);
};
#endif
