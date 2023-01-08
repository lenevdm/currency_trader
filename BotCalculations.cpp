#include "MerkelMain.h"
#include <iostream>
#include <vector> 
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "BotCalculations.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>

BotCalculations::BotCalculations()
{

}


std::vector<std::string> getUniqueProducts(const std::string& fileName) 
{
  std::vector<std::string> uniqueProducts;
  std::unordered_set<std::string> productSet;

  std::ifstream file(fileName);
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream lineStream(line);
    std::string cell;

    // Parse the line, getting the second column (the product)
    std::getline(lineStream, cell, ',');
    std::getline(lineStream, cell, ',');

    // If the product hasn't been seen before, add it to the set and vector
    if (productSet.count(cell) == 0) {
      productSet.insert(cell);
      uniqueProducts.push_back(cell);
    }
  }

  return uniqueProducts;
}


int BotCalculations::getMinimum()
{
    //return the minimum 
    return 0;
}

int BotCalculations::getMaximum()
{
    //return the max 
    return 0;
}