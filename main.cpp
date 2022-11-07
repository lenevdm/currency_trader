#include <iostream>

void printMenu()
{
    // 1 Print help
    std::cout << "1. Print help " << std::endl;
    // 2 Print exchange stats
    std::cout << "2. Print exchange stats " << std::endl;
    // 3 Make an offer
    std::cout << "3. Make an offer " << std::endl;
    // 4 Make a bid
    std::cout << "4. Make a bid " << std::endl;
    // 5 Print wallet
    std::cout << "5. Print wallet " << std::endl;
    // 6 Continue
    std::cout << "6. Continue " << std::endl;

    
    std::cout << "===================" << std::endl;
    std::cout << "Type in 1-6." << std::endl;
    
}

// Menu functions
void printHelp()
{
    std::cout << "Your aim is to make money, analyze the market and make bids and offers." << std::endl;
}

void printMarketStats()
{
    std::cout << "Market looks good." << std::endl;
}

void enterOffer()
{
    std::cout << "Make an offer - enter the amount." << std::endl;
}

void enterBid()
{
    std::cout << "Make a bid - enter the amount." << std::endl;
}

void printWallet()
{
    std::cout << "Your wallet is empty." << std::endl;
}

void gotoNextTimeFrame()
{
    std::cout << "Going to next timeframe." << std::endl;
}

int getUserOption()
{
    int userOption;
    std::cin >> userOption;
    std::cout << "You chose: " <<  userOption << std::endl;
    return userOption;
}

void processUserOption(int userOption)
{
    if (userOption == 0) // Bad input
    {
        std::cout << "Invalid choice. Choose 1-6." << std::endl;
    }
    if (userOption == 1) // 1 Print help
    {
        printHelp();
    }
    if (userOption == 2) // 2 Print exchange stats
    {
        printMarketStats();
    }
    if (userOption == 3) // 3 Make an offer
    {
        enterOffer();
    }
    if (userOption == 4) // 4 Make a bid
    {
        enterBid();
    }
    if (userOption == 5) // 5 Print wallet
    {
        printWallet();
    }
    if (userOption == 6) // 6 Continue
    {
        gotoNextTimeFrame();
    }
}

int main()
{
    while(true)
    {
        printMenu();

        int userOption = getUserOption();

        processUserOption(userOption);
    }
    
    return 0;
    

}