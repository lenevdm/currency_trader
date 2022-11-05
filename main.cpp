#include <iostream>

int main()
{
    while(true)
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

        int userOption;
        std::cin >> userOption;
        std::cout << "You chose: " <<  userOption << std::endl;

        if (userOption == 0) // Bad input
        {
            std::cout << "Invalid choice. Choose 1-6." << std::endl;
        }
        if (userOption == 1) // 1 Print help
        {
            std::cout << "Your aim is to make money, analyze the market and make bids and offers." << std::endl;
        }
        if (userOption == 2) // 2 Print exchange stats
        {
            std::cout << "Market looks good." << std::endl;
        }
        if (userOption == 3) // 3 Make an offer
        {
            std::cout << "Make an offer - enter the amount." << std::endl;
        }
        if (userOption == 4) // 4 Make a bid
        {
            std::cout << "Make a bid - enter the amount." << std::endl;
        }
        if (userOption == 5) // 5 Print wallet
        {
            std::cout << "Your wallet is empty." << std::endl;
        }
        if (userOption == 6) // 6 Continue
        {
            std::cout << "Going to next timeframe." << std::endl;
        }
    }
    

    return 0;
    
    
}