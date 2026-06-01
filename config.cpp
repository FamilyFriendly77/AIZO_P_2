#include "config.hpp"
#include <exception>
#include <fstream>
#include <iostream>
using json = nlohmann::json;

Setting<int> Config::randomSeed = Setting<int>("randomSeed");

Setting<bool> Config::inTestMode = Setting<bool>("testMode");

Setting<std::string> Config::testFilename =
    Setting<std::string>("testFilename", "tests.txt");

Setting<std::vector<int>> Config::testCasesNodeCounts =
    Setting<std::vector<int>>("testCasesNodeCounts ");

Setting<std::string> Config::configFile =
    Setting<std::string>("configFilename");
Setting<int> Config::testRepetitionCounter =
    Setting<int>("testRepetitionCounter");
Setting<bool> Config::printAfterSolving = Setting<bool>("printAfterSolving");

Setting<bool> Config::printAfterGenerating =
    Setting<bool>("printAfterGenerating");
Setting<std::string> Config::testProblem = Setting<std::string>("testProblem");
Setting<bool> Config::testIfSolved = Setting<bool>("testIfSolved");
void Config::setConfigFile(std::string filename) {
  configFile.setSetting(filename);
}
Setting<bool> Config::testINT = Setting<bool>("testINT");
Setting<bool> Config::testFLOAT = Setting<bool>("testFLOAT");
Setting<bool> Config::testDOUBLE = Setting<bool>("testDOUBLE");
Setting<bool> Config::testCHAR = Setting<bool>("testCHAR");

void Config::loadConfigFromFile() {
  std::ifstream f(Config::configFile.getValue());
  // checking if file opens, if not, throw an error because it can't be read
  if (!f.is_open()) {
    throw std::runtime_error(
        "Specified config file does not exits or can't be opened");
  }
  json config;
  try {
    config = json::parse(f);
  } catch (std::exception e) {
    std::cerr << "Something went wrong while parsing config!!!";
    return;
  }
  randomSeed.setSetting(config.value(randomSeed.getLabel(), 123456));
  inTestMode.setSetting(config.value(inTestMode.getLabel(), true));
  testFilename.setSetting(config.value(testFilename.getLabel(), "test.txt"));
  testCasesNodeCounts.setSetting(
      config.value(testCasesNodeCounts.getLabel(), std::vector<int>{}));
  testRepetitionCounter.setSetting(
      config.value(testRepetitionCounter.getLabel(), 100));
  printAfterSolving.setSetting(
      config.value(printAfterSolving.getLabel(), true));
  printAfterGenerating.setSetting(
      config.value(printAfterGenerating.getLabel(), true));
  testIfSolved.setSetting(config.value(testIfSolved.getLabel(), true));
  testINT.setSetting(config.value(testINT.getLabel(), false));
  testFLOAT.setSetting(config.value(testFLOAT.getLabel(), false));
  testDOUBLE.setSetting(config.value(testDOUBLE.getLabel(), false));
  testCHAR.setSetting(config.value(testCHAR.getLabel(), false));
}
