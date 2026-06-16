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
  static Setting<std::vector<double>> testCasesDensities;
  static Setting<int> testRepetitionCounter;
  static Setting<std::string> testAlg;
  static Setting<bool> printAfterGenerating;
  static Setting<bool> printAfterSolving;
  static Setting<bool> testIfSolved;
  static void loadConfigFromFile();
  static void setConfigFile(std::string filename);
};
#endif
