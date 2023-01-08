//The MerkelMain class represents the application itself, 
//and it deals with user input and menu printing. 

#include "MerkelMain.h"
#include <iostream>
#include <vector> 
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "CSVReader.h"
#include "BotCalculations.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <set>

bool show_main_menu = true;
bool check_main_menu = true;

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10.0);

    while(true)
    {
        //Display main menu if Advisorbot is not running
        if(show_main_menu)
        {
            printMenu();
        }
        //Perform main menu input checking if Advisorbot is not running
        if(check_main_menu)
        {
            input = getUserOption();
        }
        
        processUserOption(input);
    }
}

// void MerkelMain::loadOrderBook()
// {
    
//     // orders = CSVReader::readCSV("20200601.csv");

// }


void MerkelMain::printMenu()
{
    std::stringstream menu;
    
    menu << "============================ " << std::endl;
    menu << "1: Print help " << std::endl;
    menu << "2: Print market stats" << std::endl;
    menu << "3: Make an ask " << std::endl;
    menu << "4: Make a bid " << std::endl;
    menu << "5: Print wallet " << std::endl;
    menu << "6: Continue " << std::endl;
    menu << "7: Use Advisorbot" << std::endl;
    menu << "============================ " << std::endl;
    menu << "Current time is: " << currentTime << std::endl;

    std::cout << menu.str();
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void  MerkelMain::printMarketStats()
{
    for(std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(  OrderBookType::ask, 
                                                                    p, 
                                                                    currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;

    }
    
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product, price, amount, eg. ETH/BTC,200,0.5" << std::endl;
    std::string input;
    
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "Bad input! " << input << std::endl;
    }
    else {
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Insuficient funds." << std::endl;
            }
            
        }catch (const std::exception& e)
        {
            std::cout << "MerkelMain::enterAsk Bad input!" << std::endl;
        }
    }

    std::cout << "You typed: " << input << std::endl;

}

void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount: product, price, amount, eg. ETH/BTC,200,0.5" << std::endl;
    std::string input;
    
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Insuficient funds." << std::endl;
            }
            
        }catch (const std::exception& e)
        {
            std::cout << "MerkelMain::enterBid Bad input!" << std::endl;
        }
    }

    std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout << "Sales: " << sales.size() << std::endl;
    for (OrderBookEntry& sale : sales)
    {
        std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
        if(sale.username == "simuser")
        {
            wallet.processSale(sale);
            
        }

    }
    currentTime = orderBook.getNextTime(currentTime);
}
 
int MerkelMain::getUserOption()
{
    
    int userOption = 0;
    std::string line;

    std::cout << "Type in 1-7" << std::endl;
    std::getline(std::cin, line);
    
    try{
        userOption = std::stoi(line);

    }catch(const std::exception& e)
    {
        //
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;

    
}


void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-7 or Advisorbot commands" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printMarketStats();
    }
    if (userOption == 3) 
    {
        enterAsk();
    }
    if (userOption == 4) 
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeframe();
    }
    if (userOption == 7)
    {
        // Enable the Advisorbot menu
        runAdvisorbot();
    }
}

int MerkelMain::runAdvisorbot()
{
    
    //Prevent the main menu from being printed when using the bot
    show_main_menu = false;
    //Prevent the main menu checking from happening
    check_main_menu = false;

    std::string currentTime;
    currentTime = orderBook.getEarliestTime();

    std::cout << "==========Advisorbot========== " << std::endl;
    std::cout << "advisorbot> Please enter a command, or type help" << std::endl;
    std::string input;
    std::cin >> input;
    

    if (input == "help") 
    {
        std::cout << "advisorbot> help_<cmd>    | Displays help for a specific command." << std::endl;
        std::cout << "advisorbot> prod          | Displays a list of all available products on the currency exchange." << std::endl;
        std::cout << "advisorbot> min           | Finds the minimum bid or ask for the product in the current time step." << std::endl;
        std::cout << "advisorbot> max           | Finds the maximum bid or ask for the product in the current time step." << std::endl;
        std::cout << "advisorbot> avg           | Computes the average ask or bid for the selected product over the selected number of timesteps." << std::endl;
        std::cout << "advisorbot> predict       | Predicts the minimum or maximum ask or bid for the sent product for the next time step." << std::endl;
        std::cout << "advisorbot> time          | States the current time step in the dataset of the currency exchange." << std::endl;
        std::cout << "advisorbot> step          | Move to the next time step of the dataset." << std::endl;
        std::cout << "advisorbot> exit          | Go back to the Merkelrex main menu." << std::endl;
    } 
    else if (input == "help_prod") 
    {
        std::cout << "advisorbot> format: prod" << std::endl;
        std::cout << "advisorbot> example command: prod" << std::endl;
        std::cout << "advisorbot> example result: ETH/BTC, DOGE/BTC" << std::endl;
    } 
    else if (input == "help_min") 
    {
        std::cout << "advisorbot> format: min product ask/bid" << std::endl;
        std::cout << "advisorbot> example command: min_bid" << std::endl;
        std::cout << "advisorbot> example result: Product: BTC/USDT Min bid: 9590" << std::endl;
    } 
    else if (input == "help_max") 
    {
        std::cout << "advisorbot> format: max_<ask/bid>" << std::endl;
        std::cout << "advisorbot> example command: max_ask" << std::endl;
        std::cout << "advisorbot> example result: Product: BTC/USDT Max ask: 9590" << std::endl;
    } 
    else if (input == "help_avg") 
    {
        std::cout << "advisorbot> format: avg product ask/bid timesteps" << std::endl;
        std::cout << "advisorbot> example command: avg ETH/TBC ask 10" << std::endl;
        std::cout << "advisorbot> example result: The average ETH/BTC ask price over the last 10 timesteps was 1.0" << std::endl;
    } 
    else if (input == "help_predict") 
    {
        std::cout << "advisorbot> format: predict max/min product ask/bid" << std::endl;
        std::cout << "advisorbot> example command: predict max ETH/BTC bid" << std::endl;
        std::cout << "advisorbot> example result: The predicted maximum ETH/BTC bid price for the next step is 1.2" << std::endl;
    } 
    else if (input == "help_time") 
    {
        std::cout << "advisorbot> format: time" << std::endl;
        std::cout << "advisorbot> example command: time" << std::endl;
        std::cout << "advisorbot> example result: 2020/03/17 17:01:24" << std::endl;
    } 
    else if (input == "help_step") 
    {
        std::cout << "advisorbot> format: step" << std::endl;
        std::cout << "advisorbot> example command: step" << std::endl;
        std::cout << "advisorbot> example result: Now at 2020/03/17 17:01:30" << std::endl;
    } 
    else if (input == "prod") 
    {
        std::cout << "advisorbot> The available producst are: " << std::endl;
        for(std::string const& p : orderBook.getKnownProducts())
        {
            std::cout << "advisorbot> " << p << std::endl;
        }
    } 
    else if (input == "min_ask") 
    {
        for(std::string const& p : orderBook.getKnownProducts())
        {
            std::cout << "Product: " << p << std::endl;
            std::vector<OrderBookEntry> entries = orderBook.getOrders(  OrderBookType::ask, 
                                                                        p, 
                                                                        currentTime);
            std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;

        }
    } 
    else if (input == "min_bid") 
    {
        for(std::string const& p : orderBook.getKnownProducts())
        {
            std::cout << "Product: " << p << std::endl;
            std::vector<OrderBookEntry> entries = orderBook.getOrders(  OrderBookType::bid, 
                                                                        p, 
                                                                        currentTime);
            std::cout << "Min bid: " << OrderBook::getLowPrice(entries) << std::endl;

        }
    } 
    else if (input == "max_bid") 
    {
        for(std::string const& p : orderBook.getKnownProducts())
        {
            std::cout << "Product: " << p << std::endl;
            std::vector<OrderBookEntry> entries = orderBook.getOrders(  OrderBookType::bid, 
                                                                        p, 
                                                                        currentTime);
            std::cout << "Max bid: " << OrderBook::getHighPrice(entries) << std::endl;

        }
    } 
    else if (input == "max_ask") 
    {
        for(std::string const& p : orderBook.getKnownProducts())
        {
            std::cout << "Product: " << p << std::endl;
            std::vector<OrderBookEntry> entries = orderBook.getOrders(  OrderBookType::ask, 
                                                                        p, 
                                                                        currentTime);
            std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;

        }
    }
    else if (input == "avg") 
    {
        std::cout << "advisorbot> I don't know how to do that yet. Check back later :)" << std::endl;
    } 
    else if (input == "predict") 
    {
        std::cout << "advisorbot> I don't know how to do that yet. Check back later :)" << std::endl;
    } 
    else if (input == "time") 
    {
        std::cout << "advisorbot> " << currentTime << std::endl;
    } 
    else if (input == "step") 
    {
        gotoNextTimeframe();
        std::cout << "advisorbot> New time is " << currentTime << std::endl;
    } 
    else if (input == "exit") 
    {
        std::cout << "advisorbot> Goodbye! " << currentTime << std::endl;
        //Show the main menu again
        show_main_menu = true;
        //Enable main menu checking
        check_main_menu = true;
        //Break out of the runAdvisorbot function.
        return 0;
    } 
    else 
    {
        //Basic error handling.
        std::cout << "advisorbot> That's an invalid command. Please try again :)" << std::endl;
    }

  return 0;
}