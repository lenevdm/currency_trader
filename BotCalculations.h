#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"



class BotCalculations
{
    public:
        BotCalculations();

        std::vector<std::string> getUniqueProducts(const std::string& fileName); 
        
        int getMinimum();
        int getMaximum();

        //getAverage();

        //getPrediction();

    private: 
    

};


