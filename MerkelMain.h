//The MerkelMain class represents the application itself, 
//and it deals with user input and menu printing. 

#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "CSVReader.h"


class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();  

    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);

        int runAdvisorbot();
        

        std::string currentTime;

        OrderBook orderBook{"20200601.csv"};

        Wallet wallet;

};